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


- What does `alloc_netdev` do?

``` C
// include/linux/netdevice.h
#define alloc_netdev(sizeof_priv, name, name_assign_type, setup) \
        alloc_netdev_mqs(sizeof_priv, name, name_assign_type, setup, 1, 1)
```

``` C
// net/core/dev.c
struct net_device *alloc_netdev_mqs(int sizeof_priv, const char *name,
                unsigned char name_assign_type,
                void (*setup)(struct net_device *),
                unsigned int txqs, unsigned int rxqs) 
{
}
```


- What does `dev_init_scheduler` do?

``` C
void dev_init_scheduler(struct net_device *dev)
{
        dev->qdisc = &noop_qdisc;
        // apply dev_init_scheduler_queue to every netdev_queue
        netdev_for_each_tx_queue(dev, dev_init_scheduler_queue, &noop_qdisc);
        if (dev_ingress_queue(dev))
                dev_init_scheduler_queue(dev, dev_ingress_queue(dev), &noop_qdisc);

        // What does this line do?
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

- What does `dev_init_scheduler_queue` do?


``` C
// initiate netdev_queue with _qdisc
static void dev_init_scheduler_queue(struct net_device *dev,
                                     struct netdev_queue *dev_queue,
                                     void *_qdisc)
{
        struct Qdisc *qdisc = _qdisc;

        rcu_assign_pointer(dev_queue->qdisc, qdisc);
        dev_queue->qdisc_sleeping = qdisc;
}
```












































