This file document the annotation of loopback interface source code.

File path: `./drivers/net/loopback.c`

- Register loopback interface into the kernel initiation process

``` C
device_initcall(blackhole_netdev_init);
```

- What does `blackhole_netdev_init` do?


``` C
/* Setup and register the blackhole_netdev. */
static int __init blackhole_netdev_init(void)
{
        // allocate a net_device data structure
        blackhole_netdev = alloc_netdev(0, "blackhole_dev", NET_NAME_UNKNOWN,
                                        blackhole_netdev_setup);
        if (!blackhole_netdev)
                return -ENOMEM;

        rtnl_lock();
        dev_init_scheduler(blackhole_netdev);
        dev_activate(blackhole_netdev);
        rtnl_unlock();

        blackhole_netdev->flags |= IFF_UP | IFF_RUNNING;
        dev_net_set(blackhole_netdev, &init_net);

        return 0;
}

```

