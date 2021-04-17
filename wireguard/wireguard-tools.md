This file document the source code learning of [wireguard-tools](https://git.zx2c4.com/wireguard-tools/about/) repo.

Currently focusing on Linux `netlink` feature.


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
// ./src/netlink.h
static bool mnl_nlmsg_ok(const struct nlmsghdr *nlh, int len)
{
    // there are 3 length parameters involved here
    //
    // - len:                           length of data received from recvmsg() system call
    // - (int)sizeof(struct nlmsghdr)   size of the nlmsghdr data structure
    // - nlh->nlmsg_len:                length info contained within nlh
    //
    // len >= (int)sizeof(struct nlmsghdr)
    //     received length need to be bigger than the length of the meesage header data structure
    //
    // nlh->nlmsg_len >= sizeof(struct nlmsghdr)
    //     nlmsg_len need to be bigger or eaqual to data structure size
    //     cause it may contain more than just one message header
    // 
    // len >= (int)nlh->nlmsg_len
    //     received length need to be bigger than nlmsg_len
    //     cause received length may contain payload 
    // 
    // Eventually, it's like 
    //     len >= (int)nlh->nlmsg_len >= sizeof(struct nlmsghdr)
    

    return len >= (int)sizeof(struct nlmsghdr) &&
            nlh->nlmsg_len >= sizeof(struct nlmsghdr) &&
            (int)nlh->nlmsg_len <= len;
}
```


Q: Better understand `__mnl_cb_run` path


``` C
// ./src/netlink.h
static int __mnl_cb_run(const void *buf, size_t numbytes,
                        unsigned int seq, unsigned int portid,
                        mnl_cb_t cb_data, void *data,
                        const mnl_cb_t *cb_ctl_array,
                        unsigned int cb_ctl_array_len)
{
     // ...
                // Execute the control logic based on message type
                // Below NLMSG_MIN_TYPE is reserved for control logic
                if (nlh->nlmsg_type >= NLMSG_MIN_TYPE) {
                        if (cb_data){
                                ret = cb_data(nlh, data);
                                if (ret <= MNL_CB_STOP)
                                        goto out;
                        }
                } 
     // ...
                else if (default_cb_array[nlh->nlmsg_type]) {

                        // Execute the control logic 

                        ret = default_cb_array[nlh->nlmsg_type](nlh, data);
                        if (ret <= MNL_CB_STOP)
                                goto out;
                }
    // ...
}
```

Q: What does `mnl_attr_parse` do?

``` C
// src/netlink.h

// 1. mnl_attr_parse loop through the buffer from nlattr data structure perspective
// 2. use cb process each nlattr
static int mnl_attr_parse(const struct nlmsghdr *nlh, unsigned int offset, mnl_attr_cb_t cb, void *data)
{
    const struct nlattr *attr;

    // ...
    // 1. This mnl_attr_for_each macro loop throug the message 
    //    see next snippet of annotation for more detailed explanation
    // 
    // 2. For every round of call on cb(), extract info from *attr* into *data*
    mnl_attr_for_each(attr, nlh, offset)
        if ((ret = cb(attr, data)) <= MNL_CB_STOP)
            return ret;
    // ...

}
```

``` C
// src/netlink.h

// ...
// As a whole this macro loop through the buffer attribute by attribute
#define mnl_attr_for_each(attr, nlh, offset) \

        // point to the attr to start
        // attr here means attribute
        for ((attr) = mnl_nlmsg_get_payload_offset((nlh), (offset)); \
             
             // check if the attribute is okie for the next round
             mnl_attr_ok((attr), (char *)mnl_nlmsg_get_payload_tail(nlh) - (char *)(attr)); \

             // point to the next attribute for the next round
             (attr) = mnl_attr_next(attr))
```

Q: What does `parse_infomsg` do?


``` C
// src/netlink.h
// parse_infomsg was passed into mnl_attr_parse as a callback function, to process each nlattr data structure
static int parse_infomsg(const struct nlattr *attr, void *data)
{
    if (mnl_attr_get_type(attr) == IFLA_LINKINFO)
        return mnl_attr_parse_nested(attr, parse_linkinfo, data);
    else if (mnl_attr_get_type(attr) == IFLA_IFNAME)
        interface->name = mnl_attr_get_str(attr);
    return MNL_CB_OK;
}
```

``` C
// src/netlink.h

// bitwise and the nlattr.nla_type with NLA_TYPE_MASK
// before actul usage

// This logic is copied right out of linux kernel netlink related code

// Check kernel source code file *include/net/netlink.h* `nla_type` function

static uint16_t mnl_attr_get_type(const struct nlattr *attr)
{
        return attr->nla_type & NLA_TYPE_MASK;
}

```

Q: How does `mnl_attr_parse_nested` works?


``` C
// src/netlink.h
static int mnl_attr_parse_nested(const struct nlattr *nested, mnl_attr_cb_t cb,
                                 void *data)
{
    // ..
    const struct nlattr *attr;

    mnl_attr_for_each_nested(attr, nested)
            if ((ret = cb(attr, data)) <= MNL_CB_STOP)
                    return ret;
}
```


``` C
// src/netlink.h

/*
struct nlattr {
        // nla_len here contain both header + payload length
        __u16           nla_len;
        __u16           nla_type;
};
*/



// nest is the nlattr that encapsulate/nest other nlattr(s)
#define mnl_attr_for_each_nested(attr, nest) \
        
        for ((attr) = mnl_attr_get_payload(nest); \
             mnl_attr_ok((attr), (char *)mnl_attr_get_payload(nest) + mnl_attr_get_payload_len(nest) - (char *)(attr)); \
             (attr) = mnl_attr_next(attr))

```




































