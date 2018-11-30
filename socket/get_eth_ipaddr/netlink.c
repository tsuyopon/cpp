#include <stdio.h>
#include <asm/types.h>
#include <sys/socket.h>
#include <linux/sockios.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int idx;
    {
        int fd;
        struct ifreq req;

        fd = socket(AF_INET, SOCK_DGRAM, 0);
        strncpy(req.ifr_name, "enp0s3", IFNAMSIZ);
        ioctl(fd, SIOCGIFINDEX, &req);
        idx = req.ifr_ifindex;
    }

    {
        int fd;

        fd = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE);

        {
            struct {
                struct nlmsghdr hdr;
                struct ifaddrmsg payload;
            } msg;
            msg.hdr.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifaddrmsg));
            msg.hdr.nlmsg_type = RTM_GETADDR;
            msg.hdr.nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT;

            msg.payload.ifa_family = AF_INET;

            send(fd, &msg, sizeof(msg), 0);
        }
        {
            char buf[1024]; 
            struct nlmsghdr *hdr;
            ssize_t len = recv(fd, buf, sizeof(buf), 0);
            for (hdr = (struct nlmsghdr *)buf; NLMSG_OK(hdr, len); hdr = NLMSG_NEXT(hdr, len)) {
                if (hdr->nlmsg_type == NLMSG_ERROR) {
                    fprintf(stderr, "OOPS\n");
                    return 1;
                }
                {
                    struct ifaddrmsg *payload = (struct ifaddrmsg *)NLMSG_DATA(hdr);
                    if (payload->ifa_index == idx) {
                        char buf[1024];
                        inet_ntop(payload->ifa_family, RTA_DATA(payload + 1), buf, sizeof(buf));
                        printf("%s\n", buf);
                    }
                }
            }
        }
    }
    return 0;
}
