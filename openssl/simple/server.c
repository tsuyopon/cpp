// TLSサーバのサンプルプログラム
//
// $ gcc -lssl -lcrypto server.c
// $ ./a.out
//
// confirm 
// $ openssl s_client -connect localhost:4433
//
// 参考:
//   https://wiki.openssl.org/index.php/Simple_TLS_Server
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define TLS_SERVER_PORT 4433
#define SERVER_CERTIFICATE "../key/cert.pem"
#define SERVER_PRIVATE_KEY "../key/key.pem"

// socket, bind, listen
int create_socket(int port)
{
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(s, 1) < 0) {
        perror("Unable to listen");
        exit(EXIT_FAILURE);
    }

    return s;
}

void init_openssl()
{ 
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();   // SSL_library_init()と同じ
}

void cleanup_openssl()
{
    EVP_cleanup();
}

SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    // SSLv3, TLSv1, TLSv1.1 および TLSv1.2に対応する Server の機能を提供する SSL_METHOD を返す。
    method = SSLv23_server_method();  

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void configure_context(SSL_CTX *ctx)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    // サーバ証明書の登録
    if (SSL_CTX_use_certificate_file(ctx, SERVER_CERTIFICATE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    // サーバ秘密鍵の登録
    if (SSL_CTX_use_PrivateKey_file(ctx, SERVER_PRIVATE_KEY, SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    int sock;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();

    configure_context(ctx);

    sock = create_socket(TLS_SERVER_PORT);

    /* Handle connections */
    while(1) {
        struct sockaddr_in addr;
        uint len = sizeof(addr);
        SSL *ssl;
        const char reply[] = "test\n";

        int client = accept(sock, (struct sockaddr*)&addr, &len);
        if (client < 0) {
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        }

        ssl = SSL_new(ctx);           // SSLオブジェクトを生成する
        SSL_set_fd(ssl, client);      // SSLオブジェクトとファイルディスクリプタを接続

        if (SSL_accept(ssl) <= 0) {   // SSL通信の開始
            ERR_print_errors_fp(stderr);
        } else {
            printf("SSL_write start\n");
            SSL_write(ssl, reply, strlen(reply));
        }

        SSL_free(ssl);
        close(client);
    }

    close(sock);
    SSL_CTX_free(ctx);
    cleanup_openssl();
}

