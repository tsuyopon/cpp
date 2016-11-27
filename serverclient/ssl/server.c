#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <openssl/evp.h>
#include <openssl/ssl.h>

#define SERVER_PORT "8000"
#define SERVER_CERT_FILE "server.crt"
#define SERVER_PRIVATE_KEY_FILE "server.key"

int main()
{
  SSL_library_init();
  SSL_CTX *ctx = SSL_CTX_new(SSLv23_server_method());

  SSL_CTX_use_certificate_file(ctx, SERVER_CERT_FILE, SSL_FILETYPE_PEM);
  SSL_CTX_use_PrivateKey_file(ctx, SERVER_PRIVATE_KEY_FILE, SSL_FILETYPE_PEM);

  struct addrinfo hints;
  struct addrinfo *ai = NULL;

  memset(&hints, sizeof(hints), 0);
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, SERVER_PORT, &hints, &ai);

  int server_fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
  bind(server_fd, ai->ai_addr, ai->ai_addrlen);
  freeaddrinfo(ai);
  listen(server_fd, 1);

  while (1) {
    int session_fd = accept(server_fd, NULL, NULL);

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, session_fd);
    SSL_accept(ssl);

    SSL_shutdown(ssl);
    SSL_free(ssl);

    close(session_fd);
  }

  close(server_fd);
  SSL_CTX_free(ctx);

  return 0;
}
