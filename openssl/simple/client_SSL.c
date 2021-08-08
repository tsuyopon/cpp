//gcc -o test test.c -lssl -lcrypto
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

static int ssl_print_handshake(/*BIO *bio, */const SSL *ssl, int server,
                               const unsigned char *msg, size_t msglen,
                               int indent)
{
    size_t hlen;
    unsigned char htype;

    if (msglen < 4)
        return 0;
    htype = msg[0];
    hlen = (msg[1] << 16) | (msg[2] << 8) | msg[3];

    msg += 4;
    msglen -= 4;
    if (msglen < hlen)
        return 0;
    switch (htype) {
    case SSL3_MT_CLIENT_HELLO:
        printf("trace: SSL3_MT_CLIENT_HELLO\n");
        break;

    case DTLS1_MT_HELLO_VERIFY_REQUEST:
        printf("trace: DTLS1_MT_HELLO_VERIFY_REQUEST\n");
        break;

    case SSL3_MT_SERVER_HELLO:
        printf("trace: SSL3_MT_SERVER_HELLO\n");
        break;

    case SSL3_MT_SERVER_KEY_EXCHANGE:
        printf("trace: SSL3_MT_SERVER_KEY_EXCHANGE\n");
        break;

    case SSL3_MT_CLIENT_KEY_EXCHANGE:
        printf("trace: SSL3_MT_CLIENT_KEY_EXCHANGE\n");
        break;

    case SSL3_MT_CERTIFICATE:
        printf("trace: SSL3_MT_CERTIFICATE\n");
        break;

    case SSL3_MT_CERTIFICATE_VERIFY:
        printf("trace: SSL3_MT_CERTIFICATE_VERIFY\n");
        break;

    case SSL3_MT_CERTIFICATE_REQUEST:
        printf("trace: SSL3_MT_CERTIFICATE_REQUEST\n");
        break;

    case SSL3_MT_FINISHED:
        printf("trace: SSL3_MT_FINISHED\n");
        break;

    case SSL3_MT_SERVER_DONE:
        printf("trace: SSL3_MT_SERVER_DONE\n");
        break;

    case SSL3_MT_NEWSESSION_TICKET:
        printf("trace: SSL3_MT_NEWSESSION_TICKET\n");
        break;

    case SSL3_MT_ENCRYPTED_EXTENSIONS:
        printf("trace: SSL3_MT_ENCRYPTED_EXTENSIONS\n");
        break;

    case SSL3_MT_KEY_UPDATE:
        printf("trace: SSL3_MT_KEY_UPDATE\n");
        if (msglen != 1) {
            printf("trace: SSL3_MT_KEY_UPDATE. unexpected vaue\n");
            return 0;
        }
            return 0;
        break;

    default:
        printf("trace: default: unsupported \n");
    }
    return 1;
}

void SSL_trace(int write_p, int version, int content_type,
               const void *buf, size_t msglen, SSL *ssl, void *arg)
{
    const unsigned char *msg = buf;
    BIO *bio = arg;

    switch (content_type) {
    case SSL3_RT_HEADER:
        printf("trace: content-type: SSL3_RT_HEADER\n");
        break;

    case SSL3_RT_INNER_CONTENT_TYPE:
        BIO_printf(bio, "trace: content-type: SSL3_RT_INNER_CONTENT_TYPE\n");
        break;

    case SSL3_RT_HANDSHAKE:
        BIO_printf(bio, "trace: content-type: SSL3_RT_HANDSHAKE\n");
        if (!ssl_print_handshake(/*bio, */ssl, /*ssl->server ? write_p : !write_p,*/ !write_p,
                                 msg, msglen, 4))
            BIO_printf(bio, "Message length parse error!\n");
        break;

    case SSL3_RT_CHANGE_CIPHER_SPEC:
        if (msglen == 1 && msg[0] == 1)
            BIO_puts(bio, "trace: content-type: SSL3_RT_CHANGE_CIPHER_SPEC:    change_cipher_spec (1)\n");
        else
            BIO_printf(bio, "trace: content-type: SSL3_RT_CHANGE_CIPHER_SPEC: unknown value\n");
        break;

    case SSL3_RT_ALERT:
        if (msglen != 2)
            BIO_puts(bio, "trace: content-type: SSL3_RT_ALERT:    Illegal Alert Length\n");
        else {
            BIO_puts(bio, "trace: content-type: SSL3_RT_ALERT:\n");
        }

    }
    
    BIO_puts(bio, "\n");
}

int main(int argc, char *argv[]){
	int sd;
	struct hostent *host;
	struct sockaddr_in addr;
	BIO *outbio = NULL;
	SSL_CTX *ctx;
	SSL *ssl;
	char *req;
	int req_len;
	char hostname[] = "localhost";
	int port = 4433;
	int bytes;
	char buf[128];

	OpenSSL_add_all_algorithms();
	ERR_load_BIO_strings();
	ERR_load_crypto_strings();
	SSL_load_error_strings();

	outbio	= BIO_new(BIO_s_file());
	outbio	= BIO_new_fp(stdout, BIO_NOCLOSE);

	if(SSL_library_init() < 0){
		BIO_printf(outbio, "Could not initialize the OpenSSL library !\n");
	}

	ctx = SSL_CTX_new(SSLv23_client_method());
	SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);

	host = gethostbyname(hostname);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = *(long*)(host->h_addr);

	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == -1 ) {
		BIO_printf(outbio, "%s: Cannot connect to host %s [%s] on port %d.\n", argv[0], hostname, inet_ntoa(addr.sin_addr), port);
	}

	ssl = SSL_new(ctx); 
	SSL_set_msg_callback(ssl, SSL_trace);
	SSL_set_fd(ssl, sd);
	SSL_connect(ssl);

	req = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";	
	req_len = strlen(req);
	SSL_write(ssl, req, req_len);

	memset(buf, '\0', sizeof(buf));
	bytes = SSL_read(ssl, buf, sizeof(buf));
	while(bytes > 0){
		write(STDOUT_FILENO, buf, bytes);
		memset(buf, '\0', sizeof(buf));
		bytes = SSL_read(ssl, buf, sizeof(buf));
	}
	SSL_free(ssl);
	close(sd);
	SSL_CTX_free(ctx);
}
