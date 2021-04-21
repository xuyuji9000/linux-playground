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

