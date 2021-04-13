This file document the source code learning of [wireguard-tools](https://git.zx2c4.com/wireguard-tools/about/) repo.


Q: How does `wg` command communicate with linux kernel wireguard module over rtnetlink mechanism?

- Take `kernel_get_wireguard_interfaces` as an example

``` C
// ./src/ipc-linux.h
static int kernel_get_wireguard_interfaces(struct string_list *list)
{
    // ...
    // Prepare a rtnetlink socket
    //
    // struct mnl_socket {
    //     int fd;
    //     struct sockaddr_nl addr;
    // };
    //
    // struct sockaddr_nl {
    //          sa_family_t     nl_family;  /* AF_NETLINK */
    //          unsigned short  nl_pad;     /* Zero */
    //          pid_t           nl_pid;     /* Port ID */
    //          __u32           nl_groups;  /* Multicast groups mask */
    // };
    nl = mnl_socket_open(NETLINK_ROUTE);
    // ...
}
```
