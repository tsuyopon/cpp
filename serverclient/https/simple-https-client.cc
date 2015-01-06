/*
 * REF: http://x68000.q-e-d.net/~68user/net/ssl-1.html
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#define BUF_LEN 256

int main(int argc, char **argv)
{
  int ret;
  int s;
  struct hostent *servhost; 
  struct sockaddr_in server;
  struct servent *service; 

  SSL *ssl;
  SSL_CTX *ctx;

  char request[BUF_LEN];

  char *host = (char*)"localhost";
  char *path = (char*)"/";
  int port = 8765;

  if ( argc == 3 ){
    host = argv[1];
    path = argv[2];
  } else if( argc == 4 ){
    host = argv[1];
    path = argv[2];
    port = atoi(argv[3]);
  }

  servhost = gethostbyname(host);
  if ( servhost == NULL ){
    fprintf(stderr, "failed to gethostbyname [%s]\n", host);
    exit(1);
  }

  bzero((char *)&server, sizeof(server));
  server.sin_family = AF_INET;

  bcopy(servhost->h_addr, (char *)&server.sin_addr, servhost->h_length);

  if( argc == 4 ){
    service = getservbyname("https", "tcp");
    server.sin_port = service->s_port;        // you must consider about where service returns NULL.
  } else {
    server.sin_port = htons(port);
  }

  s = socket(AF_INET, SOCK_STREAM, 0); 
  if ( s < 0 ){
    fprintf(stderr, "failed to create socket\n");
    exit(1);
  }

  if ( connect(s, (struct sockaddr*) &server, sizeof(server)) == -1 ){
    fprintf(stderr, "failed to connect\n");
    exit(1);
  }

  SSL_load_error_strings();
  SSL_library_init();
//  ctx = SSL_CTX_new(SSLv23_client_method());
  ctx = SSL_CTX_new(TLSv1_client_method());
  if ( ctx == NULL ){
    ERR_print_errors_fp(stderr);
    exit(1);
  }
  SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
  SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv3);

  ssl = SSL_new(ctx);
  if ( ssl == NULL ){
    ERR_print_errors_fp(stderr);
    exit(1);
  }

  ret = SSL_set_fd(ssl, s);
  if ( ret == 0 ){
    ERR_print_errors_fp(stderr);
    exit(1);
  }

  /* SSL_connect */
  ret = SSL_connect(ssl);
  if ( ret != 1 ){
      ERR_print_errors_fp(stderr);
      exit(1);
  }

  /* SEND Request */
  sprintf(request, 
      "GET %s HTTP/1.0\r\n"
      "Host: %s\r\n\r\n",
          path, host);

  ret = SSL_write(ssl, request, strlen(request));
  if ( ret < 1 ){
    ERR_print_errors_fp(stderr);
    exit(1);
  }

  printf("Server Response Start\n");
  while (1){
    char buf[BUF_LEN];
    int read_size;
    read_size = SSL_read(ssl, buf, sizeof(buf)-1);
    
    if ( read_size > 0 ){
      buf[read_size] = '\0';
      write(1, buf, read_size);
    } else if ( read_size == 0 ){
      /* recieve FIN*/
      break;
    } else {
      ERR_print_errors_fp(stderr);
      exit(1);
    }
  }
  
  ret = SSL_shutdown(ssl); 
  if ( ret != 1 ){
    ERR_print_errors_fp(stderr);
    exit(1);
  }
  close(s);

  SSL_free(ssl); 
  SSL_CTX_free(ctx);
  ERR_free_strings();

  exit(0);
}

