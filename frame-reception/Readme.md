This folder is used to document the learning of frame reception in kernel source code.

- [preserve-the-frame-inside-a-queue](./preserve-the-frame-inside-a-queue.md)


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

- [How-is-NET_RX_SOFTIRQ-triggered](How-is-NET_RX_SOFTIRQ-triggered.md)

