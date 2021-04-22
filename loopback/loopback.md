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
        gen_lo_setup(dev, (64 * 1024), &loopback_ethtool_ops, &eth_header_ops,
                     &loopback_ops, loopback_dev_free);
}


static void gen_lo_setup(struct net_device *dev,
                         unsigned int mtu,
                         const struct ethtool_ops *eth_ops,
                         const struct header_ops *hdr_ops,
                         const struct net_device_ops *dev_ops,
                         void (*dev_destructor)(struct net_device *dev))
{       
        dev->mtu                = mtu;
        dev->hard_header_len    = ETH_HLEN;     /* 14   */
        dev->min_header_len     = ETH_HLEN;     /* 14   */
        dev->addr_len           = ETH_ALEN;     /* 6    */
        dev->type               = ARPHRD_LOOPBACK;      /* 0x0001*/
        dev->flags              = IFF_LOOPBACK;
        dev->priv_flags         |= IFF_LIVE_ADDR_CHANGE | IFF_NO_QUEUE;
        netif_keep_dst(dev);    
        dev->hw_features        = NETIF_F_GSO_SOFTWARE;
        dev->features           = NETIF_F_SG | NETIF_F_FRAGLIST
                | NETIF_F_GSO_SOFTWARE
                | NETIF_F_HW_CSUM
                | NETIF_F_RXCSUM
                | NETIF_F_SCTP_CRC
                | NETIF_F_HIGHDMA
                | NETIF_F_LLTX
                | NETIF_F_NETNS_LOCAL
                | NETIF_F_VLAN_CHALLENGED
                | NETIF_F_LOOPBACK;
        dev->ethtool_ops        = eth_ops;
        dev->header_ops         = hdr_ops;
        dev->netdev_ops         = dev_ops;
        dev->needs_free_netdev  = true;
        dev->priv_destructor    = dev_destructor;
}
```














































