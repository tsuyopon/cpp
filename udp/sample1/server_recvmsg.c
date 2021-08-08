/*
 * 引数を指定するとクライアントモード(sendmsg)
 * 引数を指定しないとサーバモード(recvmsg)
 *
 */
#define _GNU_SOURCE

#include <sched.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <netdb.h>
#include <pthread.h>
#include <getopt.h>

#define PORT "22222"
#define USEC 1000000
#define BUF_LEN 50

void receiver(struct addrinfo *res_local);

int main(int argc, char** argv) {

    struct addrinfo hints_local, hints_remote, *res_local, *res_remote;
    char *local_ip = NULL;
    char *remote_port = NULL;
    char *remote_ip = NULL;
    char *local_port = NULL;
    unsigned int delay = USEC;

    memset(&hints_local, 0, sizeof hints_local);
    memset(&hints_remote, 0, sizeof hints_remote);

    //IPv4/IPv6 agnostic
    hints_local.ai_family = AF_UNSPEC;
    hints_remote.ai_family = AF_UNSPEC;
    
    //UDP socket
    hints_local.ai_socktype = SOCK_DGRAM;
    hints_remote.ai_socktype = SOCK_DGRAM;
    
    local_ip = NULL;   //NULL - any interface  - 0.0.0.0 
    local_port = PORT; //local binding port
    
    hints_local.ai_flags = AI_PASSIVE; //ask kernel fillin local_ip
    
    int status;
    if ((status = getaddrinfo(local_ip, local_port, &hints_local, &res_local)) != 0) {
        fprintf(stderr, "receiver: local_ip '%s' local_port '%s' getaddrinfo error: %s\n",local_ip, local_port, gai_strerror(status));
        exit(EXIT_FAILURE);
    }
    fprintf(stderr,"receiver: local_ip '%s' local_port '%s'\n",local_ip?local_ip:"any", local_port);
    receiver(res_local);

    fprintf(stderr,"Finish!\n");
    
    freeaddrinfo(res_local);
    freeaddrinfo(res_remote);
    
    return (EXIT_SUCCESS);
}

void receiver(struct addrinfo *res_local) {
    int sock;
    unsigned char buf[BUF_LEN] = {0};

    sock = socket(res_local->ai_family, res_local->ai_socktype, res_local->ai_protocol);

    if (bind(sock, res_local->ai_addr, res_local->ai_addrlen) < 0) {
        perror("bind local addr");
        exit(EXIT_FAILURE);
    }

    struct msghdr msg;
    struct iovec iov[1];
    
    msg.msg_name = (void *) res_local->ai_addr;
    msg.msg_namelen = res_local->ai_addrlen;
    iov[0].iov_base = (void *) buf;
    iov[0].iov_len = sizeof (buf);

    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    while (1) {
        errno = 0;
        int r = recvmsg(sock, &msg, 0);
        printf("Recieved from %d bytes.\n", r);

        if (r <= 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
                continue;
            }
            perror("recvmsg()");
            continue;
        }

        {
            //Old style
            char *s = inet_ntoa(((struct sockaddr_in *) msg.msg_name)->sin_addr);
            printf("RCV FROM IP address: %s\n", s);
            unsigned char outputbuf[BUF_LEN] = {0};
            snprintf(outputbuf, msg.msg_iov->iov_len,"%s", msg.msg_iov->iov_base);
            printf("%s\n", outputbuf);
       
            
            //Modern style (show names: flag=0, show disgits: flag=NI_NUMERICHOST | NI_NUMERICSERV)
            char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
            if (getnameinfo(((struct sockaddr *) msg.msg_name), msg.msg_namelen, hbuf, sizeof(hbuf), sbuf,
                   sizeof(sbuf), 
                    NI_NUMERICHOST | NI_NUMERICSERV
                    //0
                    ) == 0)
           printf("host=%s, serv/port=%s\n", hbuf, sbuf);
        }

    }
    close(sock);
}
