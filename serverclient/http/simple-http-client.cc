#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(void)
{
    int mysocket;
    size_t size;
    char *msg;
    char *buf;
    struct sockaddr_in dest; 
    struct timeval tv;

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(mysocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));

    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    dest.sin_port = htons(3000);

    connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));

    msg = (char *) malloc(100);
    sprintf(msg, "GET / HTTP/1.1\r\n");
    sprintf(msg + strlen(msg), "Content-Length: 0\r\n");
    sprintf(msg + strlen(msg), "Connection: close\r\n");
    sprintf(msg + strlen(msg), "\r\n");

    write(mysocket, msg, strlen(msg));

    buf = (char *) malloc(100);
    size = read(mysocket, buf, 1024);
    printf("%s\n", buf);

    close(mysocket);

    return EXIT_SUCCESS;
}
