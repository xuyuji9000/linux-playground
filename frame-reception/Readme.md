This folder is used to document the learning of frame reception in kernel source code.


- loopback network device receive frame.


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
}

subsys_initcall(net_dev_init);
```
