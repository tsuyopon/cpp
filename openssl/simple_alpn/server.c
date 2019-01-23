// ALPN
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define TLS_SERVER_PORT 4433
#define SERVER_CERTIFICATE "../key/cert.pem"
#define SERVER_PRIVATE_KEY "../key/key.pem"

// SSL_CTX_set_alpn_select_cbに指定するコールバック関数
static int alpn_select_cb(SSL *ssl, const unsigned char **out,
                          unsigned char *outlen, const unsigned char *in,
                          unsigned int inlen, void *arg)
{
    
    unsigned int protlen = 0;
    const unsigned char *prot;
    const char *servalpn = "http/1.1";      // "http/1.1"であれば受け付けるようにする

    for (prot = in; prot < in + inlen; prot += protlen) {
        protlen = *prot++;
        if (in + inlen < prot + protlen)
            return SSL_TLSEXT_ERR_NOACK;    // ALPN protocol not selected.

        if (protlen == strlen(servalpn)
                && memcmp(prot, servalpn, protlen) == 0) {
            // out, outlenに何も指定しないとSSL_TLSEXT_ERR_NOACK扱いとなるので注意
            // ここで指定された値がClientHelloに対する応答としてServerHelloメッセージで返されることになる
            *out = prot;
            *outlen = protlen;
            return SSL_TLSEXT_ERR_OK;      // ALPN protocol selected.
        }
    }

    return SSL_TLSEXT_ERR_NOACK;           // ALPN protocol not selected.
}

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

    // ALPNが指定された場合に呼ばれるコールバックを登録します。
    SSL_CTX_set_alpn_select_cb(ctx, alpn_select_cb, NULL);

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

        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        } else {
            const unsigned char *data;
            unsigned len = 0;
            printf("SSL_write start\n");
            SSL_write(ssl, reply, strlen(reply));
            SSL_get0_alpn_selected(ssl, &data, &len);
            char proto[256] = {'\0'};
            snprintf(proto, len+1, data);
            printf("%s", proto);
        }

        SSL_free(ssl);
        close(client);
    }

    close(sock);
    SSL_CTX_free(ctx);
    EVP_cleanup();
}



