// 参考URL: http://blog.sarabande.jp/post/82068392478
// gcc -lssl -lcrypto  client.c -o client
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

int main(void)
{
    BIO *sbio, *out;
    int len;
    char buf[1024];
    SSL_CTX *ctx;
    SSL *ssl;
  
    ERR_load_crypto_strings();
    ERR_load_SSL_strings();
    OpenSSL_add_all_algorithms();
    SSL_library_init();

    ctx = SSL_CTX_new(SSLv23_client_method());
    sbio = BIO_new_ssl_connect(ctx);
    BIO_get_ssl(sbio, &ssl);

    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    BIO_set_conn_hostname(sbio, "localhost:4433");
    out = BIO_new_fp(stdout, BIO_NOCLOSE);

    BIO_do_connect(sbio);
    BIO_do_handshake(sbio);

    BIO_puts(sbio, "GET /index.html HTTP/1.0\r\n\r\n");

    while(1) {
        len = BIO_read(sbio, buf, 1024);

        if(len <= 0) {
            break;
        }

        BIO_write(out, buf, len);
    }
 
    BIO_free_all(sbio);
    BIO_free(out);

    return 0;
}
