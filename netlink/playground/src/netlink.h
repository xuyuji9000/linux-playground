#include <stdint.h>
#include <stdbool.h>




// byte alignment technique is used optimize for CPU access
// here also function as a convention to communicate with kernel
#define MNL_ALIGNTO 4
#define MNL_ALIGN(len) (((len)+MNL_ALIGNTO-1) & ~(MNL_ALIGNTO-1))
#define MNL_NLMSG_HDRLEN MNL_ALIGN(sizeof(struct nlmsghdr))
#define MNL_ATTR_HDRLEN MNL_ALIGN(sizeof(struct nlattr))

struct mnl_socket {
    int                fd;
    struct sockaddr_nl addr;
};

static struct mnl_socket* mnl_socket_open(int bus) 
{
    struct mnl_socket *nl;

    nl = calloc(1, sizeof(struct mnl_socket));
    if (nl == NULL)
        return NULL;

    // AF_* here stands for "Address Family"
    // While PF_* stands for "Protocol Family", it's not used.
    nl->fd = socket(AF_NETLINK, SOCK_RAW,bus);
    if (nl->fd == -1) { 
        free(nl);
        return NULL;
    }

    return nl;
}

// If the destination is kernel, pid should be set to 0
// and kernel will update pid
static int mnl_socket_bind(struct mnl_socket *nl, unsigned int groups, pid_t pid)
{
    int ret;
    socklen_t addr_len;

    nl->addr.nl_family = AF_NETLINK;
    nl->addr.nl_groups = groups;
    nl->addr.nl_pid       = pid;

    ret = bind(nl->fd, (struct sockaddr *)&nl->addr, sizeof(nl->addr));
    if(ret < 0)
        return ret;

    addr_len = sizeof(nl->addr);
    ret = getsockname(nl->fd, (struct sockaddr *)&nl->addr, &addr_len);
    if(ret < 0)
        return ret;

    if (addr_len != sizeof(nl->addr)) {
        errno = EINVAL;
        return -1;
    }

    if (nl->addr.nl_family != AF_NETLINK) {
        errno = EINVAL;
        return -1;
    }

    return 0;
}


static int mnl_socket_close(struct mnl_socket *nl)
{
    int ret = close(nl->fd);
    free(nl);
    return ret;
}

static ssize_t mnl_socket_sendto(const struct mnl_socket *nl, const void *buf,
                                 size_t len)
{
        static const struct sockaddr_nl snl = { 
                .nl_family = AF_NETLINK
        };  
        return sendto(nl->fd, buf, len, 0,
                      (struct sockaddr *) &snl, sizeof(snl));
}

static ssize_t mnl_socket_recvfrom(const struct mnl_socket *nl, void *buf,
                                   size_t bufsiz)
{
        ssize_t ret;
        struct sockaddr_nl addr;
        struct iovec iov = {
                .iov_base       = buf,
                .iov_len        = bufsiz,
        };
        struct msghdr msg = {
                .msg_name       = &addr,
                .msg_namelen    = sizeof(struct sockaddr_nl),
                .msg_iov        = &iov,
                .msg_iovlen     = 1,
                .msg_control    = NULL,
                .msg_controllen = 0,
                .msg_flags      = MSG_DONTWAIT,
        };
        ret = recvmsg(nl->fd, &msg, 0);
        if (ret == -1)
                return ret;

        if (msg.msg_flags & MSG_TRUNC) {
                errno = ENOSPC;
                return -1;
        }
        if (msg.msg_namelen != sizeof(struct sockaddr_nl)) {
                errno = EINVAL;
                return -1;
        }
        return ret;
}


static pid_t mnl_socket_get_portid(struct mnl_socket *nl)
{
    return nl->addr.nl_pid;
}

static uint16_t mnl_attr_get_type(const struct nlattr *attr)
{
        return attr->nla_type & NLA_TYPE_MASK;
}

static void *mnl_attr_get_payload(const struct nlattr *attr)
{
        return (void *)attr + MNL_ATTR_HDRLEN;
}

void process_message(const void *buf)
{
    const struct nlmsghdr *nlh = buf;
    struct nlattr *attr = NULL;
    int count = 1;

    mnl_attr_for_each(attr, nlh, MNL_ALIGN(sizeof(struct ifinfomsg)))
    {
        /*
        printf("number %d attribute type received: %d \n", count, (int)mnl_attr_get_type(attr));
        printf("attribute payload: %s\n", (char *)mnl_attr_get_payload(attr));
        */
        if(mnl_attr_get_type(attr) == IFLA_IFNAME)
        {
            printf("attribute type received: IFLA_IFNAME\n");
            printf("attribute payload: %s\n", (char *)mnl_attr_get_payload(attr));
        }
    }

}

// Give back the pointer to netlink message payload 
static void *mnl_nlmsg_get_payload_offset(const struct nlmsghdr *nlh, size_t offset)
{
        return (void *)nlh + MNL_NLMSG_HDRLEN + MNL_ALIGN(offset);
}


// Give back the pointer to the tail of netlink message payload 
static void *mnl_nlmsg_get_payload_tail(const struct nlmsghdr *nlh)
{
        return (void *)nlh + MNL_ALIGN(nlh->nlmsg_len);
}


// Give back the pointer to the next nlattr 
static struct nlattr *mnl_attr_next(const struct nlattr *attr)
{
        return (struct nlattr *)((void *)attr + MNL_ALIGN(attr->nla_len));
}


#define mnl_attr_for_each(attr, nlh, offset) \
        for ((attr) = mnl_nlmsg_get_payload_offset((nlh), (offset)); \
             mnl_attr_ok((attr), (char *)mnl_nlmsg_get_payload_tail(nlh) - (char *)(attr)); \
             (attr) = mnl_attr_next(attr))

static bool mnl_attr_ok(const struct nlattr *attr, int len)
{
        return len >= (int)attr->nla_len &&
               attr->nla_len >= sizeof(struct nlattr);
}
