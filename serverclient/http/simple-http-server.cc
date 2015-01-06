/*
 * REF: http://blog.sarabande.jp/post/81779125752
 *
 * launch server using below command
 *   $ ./a.out
 * and launch other terminal and access localhost:3000 using telnet
 *   $ telnet localhost 3000
 *   Trying 127.0.0.1...
 *   Connected to localhost.
 *   Escape character is '^]'.
 *   HTTP/1.1 200 OK
 *   Content-Type: text/html
 *   Content-Length: 11
 *   Connection: Close
 *    
 *   hello world
 *
 * you can see below message at server
 *   $ ./a.out
 *   Incoming connection from 127.0.0.1 - sending welcome
 *
 */
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
    char body[] = "hello world";
    size_t body_size = 11;
    char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 11\r\nConnection: Close\r\n";
    size_t header_size = strlen(header);
    char *msg;
    size_t msg_size = body_size + header_size + 3;

    msg = (char*)malloc(sizeof(char) * msg_size);
    snprintf(msg, msg_size, "%s\r\n%s", header, body);
    msg[msg_size] = '\0';

    struct sockaddr_in dest;
    struct sockaddr_in serv;
    int mysocket;

    socklen_t socksize = sizeof(struct sockaddr_in);
 
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serv.sin_port = htons(3000);   

    mysocket = socket(AF_INET, SOCK_STREAM, 0);

    bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
 
    listen(mysocket, 1);
    int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
 
    while (consocket)
    {
        printf("Incoming connection from %s - sending welcome\n", inet_ntoa(dest.sin_addr));
        send(consocket, msg, strlen(msg), 0); 
        consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
    }
 
    close(consocket);
    close(mysocket);

    return EXIT_SUCCESS;
}
