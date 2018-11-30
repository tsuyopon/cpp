#include <stdio.h>
#include <linux/sockios.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv)
{
    {
        int fd;
        struct ifreq req;

        fd = socket(AF_INET, SOCK_DGRAM, 0);
        strncpy(req.ifr_name, "eth0", IFNAMSIZ);
        ioctl(fd, SIOCGIFADDR, &req);
        {
            char buf[1024];
            inet_ntop(req.ifr_addr.sa_family, (char *)req.ifr_addr.sa_data + 2, buf, sizeof(buf));
            printf("%s\n", buf);
        }
    }
    return 0;
}
