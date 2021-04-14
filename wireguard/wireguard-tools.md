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
// 1. Pass in a buffer buf for manipulation
// 2. Get nlmsghdr data structure ALIGNed length 
// 3. Reserve an ALIGNed nlmsghdr length on buffer buf for a nlmsghdr pointer
// 4. The nlmsghdr's self-awared length is ALIGNed length as well
// 5. Return the nlmsghdr pointer

static struct nlmsghdr *mnl_nlmsg_put_header(void *buf)
{
        int len = MNL_ALIGN(sizeof(struct nlmsghdr));
        struct nlmsghdr *nlh = buf;

        memset(buf, 0, len);
        nlh->nlmsg_len = len;
        return nlh;
}


```

Q: What does `mnl_nlmsg_ok` do?

``` C
static bool mnl_nlmsg_ok(const struct nlmsghdr *nlh, int len)
{
    // check if recvmsg system call get more data than just the headers
    return len >= (int)sizeof(struct nlmsghdr) &&
            nlh->nlmsg_len >= sizeof(struct nlmsghdr) &&
            (int)nlh->nlmsg_len <= len;
}
```


