#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>

int main(void)
{
  SSL_CTX *ctx;
  SSL *ssl;

  int server, client, sd;
  int port = 8765;
  char crt_file[] = "server.crt";
  char key_file[] = "server.key";

  struct sockaddr_in addr;
  socklen_t size = sizeof(struct sockaddr_in);

  char buf[1024];

  char body[] = "hello world";
  char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 11\r\nConnection: Close\r\n";
  char msg[1024];

  SSL_load_error_strings();
  SSL_library_init();
  OpenSSL_add_all_algorithms();

  //ctx = SSL_CTX_new(TLSv1_server_method());
  ctx = SSL_CTX_new(SSLv23_server_method());
  SSL_CTX_use_certificate_file(ctx, crt_file, SSL_FILETYPE_PEM);
  SSL_CTX_use_PrivateKey_file(ctx, key_file, SSL_FILETYPE_PEM);

  server = socket(PF_INET, SOCK_STREAM, 0);
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  bind(server, (struct sockaddr*)&addr, sizeof(addr));
  listen(server, 10);

  while(1) {

    client = accept(server, (struct sockaddr*)&addr, &size);
    printf("Connection: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	int ret;
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client);
	ret = SSL_accept(ssl);

    if (ret > 0) {
	  printf("ACCEPT SUCCESSED ret=%d\n", ret);
      SSL_read(ssl, buf, sizeof(buf));
      printf("%s\n", buf);
      snprintf(msg, sizeof(msg), "%s\r\n%s", header, body);
      SSL_write(ssl, msg, strlen(msg));
    } else {
	  printf("ACCEPT ERROR OCCURED ret=%d\n", ret);
	}

    sd = SSL_get_fd(ssl);
    SSL_free(ssl);
    close(sd);
  }

  close(server);
  SSL_CTX_free(ctx);

  return EXIT_SUCCESS;
}
