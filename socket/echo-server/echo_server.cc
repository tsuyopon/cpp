/*
 * Creating TCP Server. This is Echo Server Program.
 *
 * TCP SERVER: 1.socket -> 2.bind -> 3.listen -> 4.accept -> 5.send or recv -> 6.closesock
 *     1. Creating socket to accept request.
 *     2. Associate socket with server info(IP addr and Port Num)
 *     3. Preparing connection.
 *     4. Established waiting accept request. And, creating new socket.
 *
 */
/* 
 * Reference URL
 *    http://www.multisoft-lab.com/voicechat/socket.html
 *    http://x68000.q-e-d.net/~68user/net/c-echo-1.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_LEN 256

/*
 * Read 1 line from socket. and insert read line into p parameter.
 *
 */
int read_line(int socket, char *p){
    int len = 0;
    while (1){
        int ret;
        ret = read(socket, p, 1);
        if ( ret == -1 ){
            perror("read");
            exit(1);
        } else if ( ret == 0 ){
            break;
        }

        if ( *p == '\n' ){
            p++;
            len++;
            break;
        }
        p++;
        len++;
    }
    *p = '\0';
    return len;
}

int main(int argc, char *argv[]){
    int connected_socket, listening_socket;
    struct sockaddr_in sin;
    int len, ret;
    int sock_optval = 1;
    int port = 5000;
                                
	// 1. LISTENING
	// Creating Listening Socket
    listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    if ( listening_socket == -1 ){
        perror("socket");
        exit(EXIT_FAILURE);
    }
                               
	// Configuring Socket Option
    if ( setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR,
                    &sock_optval, sizeof(sock_optval)) == -1 ){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

	// Address Family, Port Number, IP Address Configuration
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

	// 2. BIND
	// Assigned Socket with Address(Name)
    if ( bind(listening_socket, (struct sockaddr *)&sin, sizeof(sin)) < 0 ){
        perror("bind");
        exit(EXIT_FAILURE);
    }

	// 3. LISTEN
	// Command OS because of checking port.
    ret = listen(listening_socket, SOMAXCONN);
    if ( ret == -1 ){
        perror("listen");
        exit(EXIT_FAILURE);
    }
	printf("Checking Port %d\n", port);

    while (1){
        struct hostent *peer_host;
        struct sockaddr_in peer_sin;

        len = sizeof(peer_sin);

		// 4. ACCEPT
        connected_socket = accept(listening_socket, (struct sockaddr *)&peer_sin, (socklen_t *)&len);
        if ( connected_socket == -1 ){
            perror("accept");
        	exit(EXIT_FAILURE);
        }

        peer_host = gethostbyaddr((char *)&peer_sin.sin_addr.s_addr,
                                  sizeof(peer_sin.sin_addr), AF_INET);
        if ( peer_host == NULL ){
            printf("gethostbyname failed\n");
        	exit(EXIT_FAILURE);
        }

		printf("ConnectionInfo: %s [%s], Port %d\n", peer_host->h_name, inet_ntoa(peer_sin.sin_addr), ntohs(peer_sin.sin_port));
        while (1){
            int read_size;
            char buf[BUF_LEN];

			// 5-1. Recv From Echo Client
			// Read 1 line.
            read_size = read_line(connected_socket, buf);
            if ( read_size == 0 ) break;

			printf("Message: %s", buf);
			// 5-2. Send To Echo Client.
            write(connected_socket, buf, strlen(buf));
        }

		// 6. CLOSE
		printf("Connection Closed. Continue to checking port[%d]\n", port);
        ret = close(connected_socket);
        if ( ret == -1 ){
            perror("close");
        	exit(EXIT_FAILURE);
        }
    }
    ret = close(listening_socket);
    if ( ret == -1 ){
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
