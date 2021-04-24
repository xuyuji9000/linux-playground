This file documents the source code annotation of loopback network device.

- Where is loopback registered?

``` C

// ./drivers/net/loopback.c

/* Registered in net/core/dev.c */
struct pernet_operations __net_initdata loopback_net_ops = { 
        .init = loopback_net_init,
};
```

``` C
// net/core/dev.c

// This function is responsible for network device subsystem initialization
static int __init net_dev_init(void)
{

        // ..
        /* The loopback device is special if any other network devices
         * is present in a network namespace the loopback device must
         * be present. Since we now dynamically allocate and free the
         * loopback device ensure this invariant is maintained by
         * keeping the loopback device as the first device on the
         * list of network devices.  Ensuring the loopback devices
         * is the first device that appears and the last network device
         * that disappears.
         */
        if (register_pernet_device(&loopback_net_ops))
                goto out;
        // ..
}
```

- What does `loopback_net_init` do?

``` C
// ./drivers/net/loopback.c

/* Setup and register the loopback device. */
static __net_init int loopback_net_init(struct net *net)
{
        // ...
        // alloc_netdev 
        //     allocate a new net_device structure

        // - 0:    private data size is 0
        // - "lo": is the name used for network interface
        // - NET_NAME_UNKNOWN: means the interface name can not be modified from user space
        // - loopback_setup: This function does the work of setup
        dev = alloc_netdev(0, "lo", NET_NAME_UNKNOWN, loopback_setup);
        // ...
}
```

- What does `loopback_setup` do?

``` C
// ./drivers/net/loopback.c

/* The loopback device is special. There is only one instance
 * per network namespace.
 */
static void loopback_setup(struct net_device *dev)
{
        // loopback_ethtool_ops:  implement ethtool_ops API
        // eth_header_ops: This is for packet header processing
        // loopback_ops: What does this do?
        gen_lo_setup(dev, (64 * 1024), &loopback_ethtool_ops, &eth_header_ops,
                     &loopback_ops, loopback_dev_free);
}

/*
 * int (*ndo_init)(struct net_device *dev);
 *     This function is called once when a network device is registered.
 *     The network device can use this for any late stage initialization
 *     or semantic validation. It can fail with an error code which will
 *     be propagated back to register_netdev.

 * netdev_tx_t (*ndo_start_xmit)(struct sk_buff *skb,
 *                               struct net_device *dev);
 *      Called when a packet needs to be transmitted.
 *      Returns NETDEV_TX_OK.  Can return NETDEV_TX_BUSY, but you should stop
 *      the queue before that can happen; it's for obsolete devices and weird
 *      corner cases, but the stack really does a non-trivial amount
 *      of useless work if you return NETDEV_TX_BUSY.
 *      Required; cannot be NULL. 

 * void (*ndo_get_stats64)(struct net_device *dev,
 *                         struct rtnl_link_stats64 *storage);
 * struct net_device_stats* (*ndo_get_stats)(struct net_device *dev);
 *      Called when a user wants to get the network device usage
 *      statistics. Drivers must do one of the following:
 *      1. Define @ndo_get_stats64 to fill in a zero-initialised
 *         rtnl_link_stats64 structure passed by the caller.
 *      2. Define @ndo_get_stats to update a net_device_stats structure
 *         (which should normally be dev->stats) and return a pointer to
 *         it. The structure may be changed asynchronously only if each
 *         field is written atomically.
 *      3. Update dev->stats asynchronously and atomically, and define
 *         neither operation.

 * int (*ndo_set_mac_address)(struct net_device *dev, void *addr);
 *      This function  is called when the Media Access Control address
 *      needs to be changed. If this interface is not defined, the
 *      MAC address can not be changed.

 */
static const struct net_device_ops loopback_ops = {
        .ndo_init        = loopback_dev_init,
        .ndo_start_xmit  = loopback_xmit,
        .ndo_get_stats64 = loopback_get_stats64,
        .ndo_set_mac_address = eth_mac_addr,
};   
```


- What does `loopback_dev_free` do?

``` C
// ./drivers/net/loopback.c

// Release resources, loopback device used
static void loopback_dev_free(struct net_device *dev)
{
        // Clear the loopback device pointer from the struct net instance 
        dev_net(dev)->loopback_dev = NULL;
        
        // Free, because inside loopback_dev_init allocated lstats
        free_percpu(dev->lstats);
}


```


``` C
// ./drivers/net/loopback.c

static int loopback_dev_init(struct net_device *dev)
{
        // What does netdev_alloc_pcpu_stats do?
        dev->lstats = netdev_alloc_pcpu_stats(struct pcpu_lstats);
        if (!dev->lstats)
                return -ENOMEM;
        return 0;
}


```

- How is the per-cpu variable allocated?

- How does `netdev_alloc_pcpu_stats` works?

``` C
// include/linux/netdevice.h

#define netdev_alloc_pcpu_stats(type)                                   \
        __netdev_alloc_pcpu_stats(type, GFP_KERNEL)

#define __netdev_alloc_pcpu_stats(type, gfp)                            \
({                                                                      \
        typeof(type) __percpu *pcpu_stats = alloc_percpu_gfp(type, gfp);\
        if (pcpu_stats) {                                               \
                int __cpu;                                              \
                for_each_possible_cpu(__cpu) {                          \
                        typeof(type) *stat;                             \
                        stat = per_cpu_ptr(pcpu_stats, __cpu);          \
                        u64_stats_init(&stat->syncp);                   \
                }                                                       \
        }                                                               \
        pcpu_stats;                                                     \
})

```

``` C
// include/linux/percpu.h

#define alloc_percpu_gfp(type, gfp)                                     \
        (typeof(type) __percpu *)__alloc_percpu_gfp(sizeof(type),       \
                                                __alignof__(type), gfp)
```

- How to loop through CPU?

``` C
// include/linux/cpumask.h

#define for_each_possible_cpu(cpu) for_each_cpu((cpu), cpu_possible_mask)


/**
 * for_each_cpu - iterate over every cpu in a mask
 * @cpu: the (optionally unsigned) integer iterator
 * @mask: the cpumask pointer
 *
 * After the loop, cpu is >= nr_cpu_ids.
 */
#define for_each_cpu(cpu, mask)                         \
        for ((cpu) = -1;                                \
                (cpu) = cpumask_next((cpu), (mask)),    \
                (cpu) < nr_cpu_ids;)

```

``` C
// ./kernel/smp.c

// nr_cpu_ids is defined here

/* this is hard limit */
static int __init nrcpus(char *str)
{
        int nr_cpus;

        if (get_option(&str, &nr_cpus) && nr_cpus > 0 && nr_cpus < nr_cpu_ids)
                nr_cpu_ids = nr_cpus;

        return 0;
}
```

- How does loopback read cpu status?

``` C
// ./drivers/net/loopback.c

// with `dev_lstats_read` function

void dev_lstats_read(struct net_device *dev, u64 *packets, u64 *bytes)
{
        int i;

        *packets = 0;
        *bytes = 0;

        for_each_possible_cpu(i) {
                const struct pcpu_lstats *lb_stats;
                u64 tbytes, tpackets;
                unsigned int start;

                // - how the `dev->lstats` is initiated
                // - `per_cpu_ptr` function can also be a point for exploration
                //   But will skip for now, this function is a level deepr 
                //   And serves as a helper function
                lb_stats = per_cpu_ptr(dev->lstats, i); 
                do {
                        start = u64_stats_fetch_begin_irq(&lb_stats->syncp);
                        tpackets = u64_stats_read(&lb_stats->packets);
                        tbytes = u64_stats_read(&lb_stats->bytes);
                } while (u64_stats_fetch_retry_irq(&lb_stats->syncp, start));
                *bytes   += tbytes;
                *packets += tpackets;
        }   
}
EXPORT_SYMBOL(dev_lstats_read);

```


``` C
// include/linux/netdevice.h

// What is `pcpu_lstats` data structure?

struct pcpu_lstats {
        u64_stats_t packets;
        u64_stats_t bytes;
        struct u64_stats_sync syncp;
} __aligned(2 * sizeof(u64));


```


































