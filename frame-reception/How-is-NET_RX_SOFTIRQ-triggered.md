
- How-is-NET_RX_SOFTIRQ-triggered.md


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





