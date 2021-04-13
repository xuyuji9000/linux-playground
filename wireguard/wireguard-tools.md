This file document the source code learning of [wireguard-tools](https://git.zx2c4.com/wireguard-tools/about/) repo.


Q: How does `wg` command communicate with linux kernel wireguard module over rtnetlink mechanism?

- Take `kernel_get_wireguard_interfaces` as an example

``` C
// ./src/ipc-linux.h
static int kernel_get_wireguard_interfaces(struct string_list *list)
{
    //...

    // Prepare an empty buffer rtnl_buffer
    rtnl_buffer = calloc(SOCKET_BUFFER_SIZE, 1);

    // ...
    // Prepare a rtnetlink socket

    // struct mnl_socket {
    //     int fd;
    //     struct sockaddr_nl addr;
    // };
    
    // struct sockaddr_nl {
    //          sa_family_t     nl_family;  /* AF_NETLINK */
    //          unsigned short  nl_pad;     /* Zero */
    //          pid_t           nl_pid;     /* Port ID */
    //          __u32           nl_groups;  /* Multicast groups mask */
    // };
    
    nl = mnl_socket_open(NETLINK_ROUTE);
    // ...

    // Use the empty buffer rtnl_buffer for storing
    // Netlink message data structure nlmsghdr
    nlh = mnl_nlmsg_put_header(rtnl_buffer);
    
    // ...

    // Add Rtnetlink message data structure ifinfomsg
    ifm = mnl_nlmsg_put_extra_header(nlh, sizeof(*ifm));

    // ...
}
```

Q: What does method `mnl_nlmsg_put_header` do?

``` C
// ./src/netlink.h
// 1. Take an empty buffer buf
// 2. Get nlmsghdr data structure size and ALIGN it
// 3. Initiate a nlmsghdr pointer, point to buf
static struct nlmsghdr *mnl_nlmsg_put_header(void *buf)
{
        int len = MNL_ALIGN(sizeof(struct nlmsghdr));
        struct nlmsghdr *nlh = buf;

        memset(buf, 0, len);
        nlh->nlmsg_len = len;
        return nlh;
}


```