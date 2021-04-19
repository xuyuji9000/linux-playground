#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#include "netlink.h"


#define MNL_SOCKET_AUTOPID 0
#define SOCKET_BUFFER_SIZE (mnl_ideal_socket_buffer_size())
struct nlmsghdr *nlh = NULL;
struct iovec iov;
int sock_fd;

// control the size of buffer 
// so it fits the operating system page size
static size_t mnl_ideal_socket_buffer_size(void)
{
    static size_t size = 0;

    if(size)
        size;
    size = (size_t)sysconf(_SC_PAGESIZE);
    
    if (size > 8192)
        size = 8192;

    return size;
}

// put struct nlmsghdr on an empty buffer
static struct nlmsghdr* mnl_nlmsg_put_header(void* buf)
{
    int len = MNL_ALIGN(sizeof(struct nlmsghdr));
    struct nlmsghdr* nlh = buf;

    memset(buf, 0, len);
    nlh->nlmsg_len = len;
    
    return nlh;
}

// piggy-back an extra message type 
static void* mnl_nlmsg_put_extra_header(struct nlmsghdr* nlh, size_t size)
{
    char* ptr = (char*)nlh + nlh->nlmsg_len;
    size_t len = MNL_ALIGN(size);
    nlh->nlmsg_len += len;

    memset(ptr, 0, len);

    return ptr;
}

int main() 
{
    struct mnl_socket* nl = NULL;
    char* rtnl_buffer = NULL;

    int ret = 0;
    pid_t portid;            // netlink socket unicast address
    unsigned int seq;

    struct nlmsghdr* nlh;
    struct ifinfomsg* ifm;
    size_t message_len;
    ssize_t len;
    
    // prepare the file descriptor 
    // for communicating through rtnetlink
    nl= mnl_socket_open(NETLINK_ROUTE);
    if(!nl) 
    {
        ret = -errno;
        goto cleanup;
    }

    if (mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0) 
    {
        ret = -errno;
        goto cleanup;
    }


    // allocate buffer 
    rtnl_buffer = calloc(SOCKET_BUFFER_SIZE,1);
    if(!rtnl_buffer)
    {
        ret = -errno;
        goto cleanup;
    }
   
    // prepare the message 
    seq = time(NULL);
    portid = (int)mnl_socket_get_portid(nl);

    nlh = mnl_nlmsg_put_header(rtnl_buffer);
    nlh->nlmsg_type  = RTM_GETLINK;
    nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK | NLM_F_DUMP;
    nlh->nlmsg_seq   = seq;

    ifm = mnl_nlmsg_put_extra_header(nlh, sizeof(struct ifinfomsg));
    ifm->ifi_family = AF_UNSPEC;

    message_len = nlh->nlmsg_len;

    if (mnl_socket_sendto(nl, rtnl_buffer, message_len) < 0) {
            ret = -errno;
            goto cleanup;
    }

another:

    if ((len = mnl_socket_recvfrom(nl, rtnl_buffer, SOCKET_BUFFER_SIZE)) < 0) {
            ret = -errno;
            goto cleanup;
    }
    printf("message length received: %d\n", (int)len);

    process_message(rtnl_buffer, len);
    

    ret = 0;

cleanup:
    if(nl)
        mnl_socket_close(nl);
    return ret;
}
