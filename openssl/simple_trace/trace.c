#include "trace.h"

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
        printf("trace: content-type: SSL3_RT_INNER_CONTENT_TYPE\n");
        break;

    case SSL3_RT_HANDSHAKE:
        printf("trace: content-type: SSL3_RT_HANDSHAKE\n");
        if (!ssl_print_handshake(/*bio, */ssl, /*ssl->server ? write_p : !write_p,*/ !write_p,
                                 msg, msglen, 4))
            printf("trace: content-type: SSL3_RT_HANDSHAKE: Message length parse error!\n");
        break;

    case SSL3_RT_CHANGE_CIPHER_SPEC:
        if (msglen == 1 && msg[0] == 1)
            printf("trace: content-type: SSL3_RT_CHANGE_CIPHER_SPEC:    change_cipher_spec (1)\n");
        else
            printf("trace: content-type: SSL3_RT_CHANGE_CIPHER_SPEC:    unknown value\n");
        break;

    case SSL3_RT_ALERT:
        if (msglen != 2)
            printf("trace: content-type: SSL3_RT_ALERT:    Illegal Alert Length\n");
        else {
            printf("trace: content-type: SSL3_RT_ALERT\n");
        }

    }
    
    BIO_puts(bio, "\n");
}
