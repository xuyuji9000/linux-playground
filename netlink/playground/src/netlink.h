// This file contains netlink related struct definition and macros

// byte alignment technique is used optimize for CPU access
// here also function as a convention to communicate with kernel
#define MNL_ALIGNTO 4
#define MNL_ALIGN(len) (((len)+MNL_ALIGNTO-1) & ~(MNL_ALIGNTO-1))

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


static pid_t mnl_socket_get_portid(struct mnl_socket *nl)
{
    return nl->addr.nl_pid;
}


