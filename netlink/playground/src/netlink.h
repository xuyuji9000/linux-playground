#include <stdint.h>




// byte alignment technique is used optimize for CPU access
// here also function as a convention to communicate with kernel
#define MNL_ALIGNTO 4
#define MNL_ALIGN(len) (((len)+MNL_ALIGNTO-1) & ~(MNL_ALIGNTO-1))
#define MNL_NLMSG_HDRLEN MNL_ALIGN(sizeof(struct nlmsghdr))
#define MNL_ATTR_HDRLEN MNL_ALIGN(sizeof(struct nlattr))

static void *mnl_nlmsg_get_payload_offset(const struct nlmsghdr *nlh, size_t offset)
{
        return (void *)nlh + MNL_NLMSG_HDRLEN + MNL_ALIGN(offset);
}

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

    attr = (void *)nlh + MNL_NLMSG_HDRLEN + MNL_ALIGN(sizeof(struct ifinfomsg));

    // print out nlattr 
    printf("attribute length received: %d\n", attr->nla_len);
    if(mnl_attr_get_type(attr) == IFLA_IFNAME)
    {
        printf("attribute type received: IFLA_IFNAME\n";
        printf("attribute payload: %s\n", mnl_attr_get_payload(attr));
    }

    // print out payload
    
}

