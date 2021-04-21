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

- What does `dev_init_scheduler` do?

``` C
void dev_init_scheduler(struct net_device *dev)
{
        dev->qdisc = &noop_qdisc;
        netdev_for_each_tx_queue(dev, dev_init_scheduler_queue, &noop_qdisc);
        if (dev_ingress_queue(dev))
                dev_init_scheduler_queue(dev, dev_ingress_queue(dev), &noop_qdisc);

        timer_setup(&dev->watchdog_timer, dev_watchdog, 0);
}
```


- What does `netdev_for_each_tx_queue` do?

``` C
// net/sched/sch_generic.c
// Apply function f to each transmission queue
static inline void netdev_for_each_tx_queue(struct net_device *dev,
                                            void (*f)(struct net_device *,
                                                      struct netdev_queue *,
                                                      void *),
                                            void *arg)
{               
        unsigned int i;

        for (i = 0; i < dev->num_tx_queues; i++)
                // What's this _tx field used for ?
                f(dev, &dev->_tx[i], arg);
}

```













































