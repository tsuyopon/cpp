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

void sender(struct addrinfo *res_local, struct addrinfo *res_remote, unsigned int usecs);

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
    hints_local.ai_family = AF_INET;
    hints_remote.ai_family = AF_INET;
    
    //UDP socket
    hints_local.ai_socktype = SOCK_DGRAM;
    hints_remote.ai_socktype = SOCK_DGRAM;
    
    remote_ip = argv[1];
    remote_port = PORT;    //remote server port
    local_port = "0";   //sender local port "0" - any free port or use custom and then do bind
    local_ip = NULL;       //NULL - any interface (may be kernel will choose by target ip)
    
    int status;
    
    if ((status = getaddrinfo( local_ip, local_port, &hints_local, &res_local)) != 0) {
        fprintf(stderr, "sender: local_ip '%s' local_port '%s' getaddrinfo error: %s\n",local_ip, "0", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    if ((status = getaddrinfo(remote_ip, remote_port, &hints_remote, &res_remote)) != 0) {
        fprintf(stderr, "sender: remote_ip '%s' remote_port '%s' getaddrinfo error: %s\n",remote_ip, remote_port, gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    fprintf(stderr,"sender:\nlocal_ip '%s' local_port '%s'\nremote_ip '%s' remote_port '%s'\n",local_ip?local_ip:"any", local_port,remote_ip, remote_port);
    sender(res_local, res_remote, delay);
        
    fprintf(stderr,"Finish!\n");
    
    freeaddrinfo(res_local);
    freeaddrinfo(res_remote);
    
    return (EXIT_SUCCESS);
}

void sender(struct addrinfo *res_local, struct addrinfo *res_remote, unsigned int usecs) {

    int sock;
    unsigned char buf[BUF_LEN] = {"hoge"};
    unsigned char buf2[BUF_LEN] = {"fuga"};

    sock = socket(res_remote->ai_family, res_remote->ai_socktype, res_remote->ai_protocol);
    
    struct iovec iov[2];
    iov[0].iov_base = (void*) buf;
    iov[0].iov_len = sizeof(buf);
    iov[1].iov_base = (void*) buf2;
    iov[1].iov_len = sizeof(buf2);

    // ここを {}で初期化しないと「sendmsg: Invalid argument」のエラ〜メッセージが表示されるので注意
    // see: https://stackoverflow.com/questions/9370479/sendmsg-invalid-arguments
    struct msghdr msg = {};

    msg.msg_name = (void *) res_remote->ai_addr;
    msg.msg_namelen = res_remote->ai_addrlen;
    
    msg.msg_iov = iov;
    msg.msg_iovlen = 2;
            
    while (1) {
        errno = 0;
        int k = sendmsg(sock, &msg, 0);
        if (k < 1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
                perror("sendmsg EAGAIN?");
            } else {
                perror("sendmsg");
                return;
            }
        }
        fprintf(stderr,".");
        usleep(usecs);
    }

    close(sock);

}
