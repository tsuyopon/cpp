#ifndef TRACE_H 
#define TRACE_H

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

static int ssl_print_handshake(/*BIO *bio, */const SSL *ssl, int server,
                               const unsigned char *msg, size_t msglen,
                               int indent);
void SSL_trace(int write_p, int version, int content_type,
               const void *buf, size_t msglen, SSL *ssl, void *arg);

#endif /* TRACE_H */
