This file documents the annotation learning of netlink.

Q: Where is rtnetlink registered?


``` C
// ./net/core/rtnetlink.c
static int __net_init rtnetlink_net_init(struct net *net)
{
    // ..
    sk = netlink_kernel_create(net, NETLINK_ROUTE, &cfg);
    //
}
```


Q: How is rtnetlink registered?

``` C
// ./net/netlink/af_netlink.c
struct sock *
__netlink_kernel_create(struct net *net, int unit, struct module *module,
                        struct netlink_kernel_cfg *cfg)
{
    // ..
    // nl_table is the global variable 
    // used for storing netlink registration
    BUG_ON(!nl_table);

    // ..
    // create a new socket
    if (sock_create_lite(PF_NETLINK, SOCK_DGRAM, unit, &sock))
        return NULL;
    
    // ..
    // set data struct netlink_sock as data structure socket's container
    if (__netlink_create(net, sock, cb_mutex, unit, 1) < 0)
        goto out_sock_release_nosk;

    // ..
}
```
