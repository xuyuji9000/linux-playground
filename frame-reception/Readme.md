This folder is used to document the learning of frame reception in kernel source code.


- Preserve the frame inside a queue


``` C
// ./drivers/net/loopback.c

/* The higher levels take care of making this non-reentrant (it's
 * called with bh's disabled).
 */
static netdev_tx_t loopback_xmit(struct sk_buff *skb,
                                 struct net_device *dev)
{
        int len;

        skb_tx_timestamp(skb);

        /* do not fool net_timestamp_check() with various clock bases */
        skb->tstamp = 0;

        skb_orphan(skb);

        /* Before queueing this packet to netif_rx(),
         * make sure dst is refcounted.
         */
        skb_dst_force(skb);

        skb->protocol = eth_type_trans(skb, dev);

        len = skb->len;
        if (likely(netif_rx(skb) == NET_RX_SUCCESS))
                dev_lstats_add(dev, len);

        return NETDEV_TX_OK;
}
```

``` C
// net/core/dev.c


/**
 *      netif_rx        -       post buffer to the network code
 *      @skb: buffer to post
 *
 *      This function receives a packet from a device driver and queues it for
 *      the upper (protocol) levels to process.  It always succeeds. The buffer
 *      may be dropped during processing for congestion control or by the
 *      protocol layers.
 *
 *      return values:
 *      NET_RX_SUCCESS  (no congestion)
 *      NET_RX_DROP     (packet was dropped)
 *
 */

int netif_rx(struct sk_buff *skb)
{
        int ret;

        trace_netif_rx_entry(skb);

        ret = netif_rx_internal(skb);
        trace_netif_rx_exit(ret);

        return ret;
}
EXPORT_SYMBOL(netif_rx);

```

``` C
// net/core/dev.c

static int netif_rx_internal(struct sk_buff *skb)
{
    // ...
                ret = enqueue_to_backlog(skb, cpu, &rflow->last_qtail);

    // ... 
}
```


``` C
// net/core/dev.c

/*
 * enqueue_to_backlog is called to queue an skb to a per CPU backlog
 * queue (may be a remote CPU queue).
 */
static int enqueue_to_backlog(struct sk_buff *skb, int cpu,
                              unsigned int *qtail)
{
    // ...
                        __skb_queue_tail(&sd->input_pkt_queue, skb);
                        
    // ...
}

```

``` C
// net/core/dev.c

static int process_backlog(struct napi_struct *napi, int quota)
{       
    // ...
                if (skb_queue_empty(&sd->input_pkt_queue)) {
                        /*
                         * Inline a custom version of __napi_complete().
                         * only current cpu owns and manipulates this napi,
                         * and NAPI_STATE_SCHED is the only possible flag set
                         * on backlog.
                         * We can use a plain write instead of clear_bit(),
                         * and we dont need an smp_mb() memory barrier.
                         */
                        napi->state = 0;
                        again = false;
                } else {
                        skb_queue_splice_tail_init(&sd->input_pkt_queue,
                                                   &sd->process_queue);
                }
    // ...
}
```

- Register the `NET_RX_SOFTIRQ` as the bottom half of the interrupt

``` C
// net/core/dev.c

/*
 *      Initialize the DEV module. At boot time this walks the device list and
 *      unhooks any devices that fail to initialise (normally hardware not
 *      present) and leaves us with a valid list of present and active devices.
 *
 */

/*
 *       This is called single threaded during boot, so no need
 *       to take the rtnl semaphore.
 */
static int __init net_dev_init(void)
{
    // ...
    sd->backlog.poll = process_backlog;
    // ...
    open_softirq(NET_RX_SOFTIRQ, net_rx_action);
    // ...
}

subsys_initcall(net_dev_init);
```

- How is `NET_RX_SOFTIRQ` triggered?


``` C
// kernel/softirq.c

// Under the context of `CONFIG_PREEMPT_RT` not set

asmlinkage __visible void do_softirq(void)
{
    // ...
    if (pending && !ksoftirqd_running(pending))
                do_softirq_own_stack();
    // ...
}
```


``` C
// kernel/softirq.c

void __local_bh_enable_ip(unsigned long ip, unsigned int cnt)
{ 
        if (unlikely(!in_interrupt() && local_softirq_pending())) {
                /*
                 * Run softirq if any pending. And do it in its own stack
                 * as we may be calling this deep in a task call stack already.
                 */
                do_softirq();
        }
}
```

``` C
// include/linux/bottom_half.h


static inline void local_bh_enable(void)
{
        __local_bh_enable_ip(_THIS_IP_, SOFTIRQ_DISABLE_OFFSET);
}

```

``` C
// net/core/dev.c

void napi_busy_loop(unsigned int napi_id,
                    bool (*loop_end)(void *, unsigned long),
                    void *loop_end_arg, bool prefer_busy_poll, u16 budget)
{
    // ...
    count:          
                if (work > 0)
                        __NET_ADD_STATS(dev_net(napi->dev),
                                        LINUX_MIB_BUSYPOLLRXPACKETS, work);
                local_bh_enable();
    // ...
}

EXPORT_SYMBOL(napi_busy_loop);

```

``` C
// include/net/busy_poll.h


static inline void sk_busy_loop(struct sock *sk, int nonblock)
{
#ifdef CONFIG_NET_RX_BUSY_POLL
        unsigned int napi_id = READ_ONCE(sk->sk_napi_id);

        if (napi_id >= MIN_NAPI_ID)
                napi_busy_loop(napi_id, nonblock ? NULL : sk_busy_loop_end, sk,
                               READ_ONCE(sk->sk_prefer_busy_poll),
                               READ_ONCE(sk->sk_busy_poll_budget) ?: BUSY_POLL_BUDGET);
#endif
}
```

``` C
// net/socket.c

/* No kernel lock held - perfect */
static __poll_t sock_poll(struct file *file, poll_table *wait)
{
    // ...
                /* poll once if requested by the syscall */
                if (events & POLL_BUSY_LOOP)
                        sk_busy_loop(sock->sk, 1);

    // ...
}
```

``` C
// net/socket.c

static const struct file_operations socket_file_ops = {
    // ...
    .poll =         sock_poll,
    // ...
}
```

``` C
// net/socket.c

struct file *sock_alloc_file(struct socket *sock, int flags, const char *dname)
{
    // ...
        file = alloc_file_pseudo(SOCK_INODE(sock), sock_mnt, dname,
                                O_RDWR | (flags & O_NONBLOCK),
                                &socket_file_ops);
    // ...
        
}
EXPORT_SYMBOL(sock_alloc_file);
```

``` C
// net/socket.c

static int sock_map_fd(struct socket *sock, int flags)
{
        

    // ...
        newfile = sock_alloc_file(sock, flags, NULL);
        
    // ...
}
```

``` C
// net/socket.c

int __sys_socket(int family, int type, int protocol)
{
        // ...

        return sock_map_fd(sock, flags & (O_CLOEXEC | O_NONBLOCK));
}
```





