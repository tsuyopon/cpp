# 概要
クライアント認証を行うサーバのサンプルです。

# ポイント
server.ccに次のコードが含まれています。
SSL_CTX_load_verify_locationsには本来はクライアント認証に必要なクライアント証明書のpemを指定します。
ここではテストを簡単にするために単純にサーバ証明書を指定しています。
```
#define SERVER_CERTIFICATE "../key/cert.pem"

...

    // ClientCertificateを要求する
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);

    // 信頼できる証明書ストアのロード
    if (!SSL_CTX_load_verify_locations(ctx, SERVER_CERTIFICATE, NULL)){
        printf("SSL_CTX_load_verify_locations error!\n");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
  }
```

クライアント証明書が指定されていたら次の関数でSSL_get_peer_certificateをして証明書の内容を取得するようになっています。
```
void ShowCerts(SSL* ssl)
{
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
    if ( cert != NULL )
    {   
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0); 
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0); 
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }   
    else
        printf("No certificates.\n");
}
```


# テスト方法
CTX_load_verify_locationsには../key/cert.pemが指定されていますのでcertにそれを指定して、keyにはcertに指定したのに応答する鍵を指定します。

次のようにしてリクエストします。「Client Certificate Types」と表示されていることが確認できます。
```
$ openssl s_client -connect localhost:4433 -cert ../key/cert.pem -key ../key/key.pem 
CONNECTED(00000003)
depth=0 C = XX, L = Default City, O = Default Company Ltd
verify error:num=18:self signed certificate
verify return:1
depth=0 C = XX, L = Default City, O = Default Company Ltd
verify return:1
---
Certificate chain
 0 s:/C=XX/L=Default City/O=Default Company Ltd
   i:/C=XX/L=Default City/O=Default Company Ltd
---
Server certificate
-----BEGIN CERTIFICATE-----
MIIDADCCAegCCQDbRBwU17EebDANBgkqhkiG9w0BAQUFADBCMQswCQYDVQQGEwJY
WDEVMBMGA1UEBwwMRGVmYXVsdCBDaXR5MRwwGgYDVQQKDBNEZWZhdWx0IENvbXBh
bnkgTHRkMB4XDTE2MTEyNzE1MDEyNFoXDTI2MTEyNTE1MDEyNFowQjELMAkGA1UE
BhMCWFgxFTATBgNVBAcMDERlZmF1bHQgQ2l0eTEcMBoGA1UECgwTRGVmYXVsdCBD
b21wYW55IEx0ZDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANl/L8DB
f1pBzZW1ZRu/D6VwxKdOEn5k8ccKuF7eFA/4wTgI5GhNs6zM+lEB5LHRYedl8CaO
WHgPBGJXeJdEU7otcZQHNv/DtHJcmRNipXqIF863PaEq3xY+xPPePl5C/Y3yvUjA
vryNwMydhF4JYpDMGXIYLCvfikeVHXU9BQVkedXOO678GnS3PCkcpNy3Btymo+hq
ga8Xs3VXYteDt1OdLtflpVOqEPgXAoxQdgqz82eiPh3uhhTU2qwuAWclXRvJXkar
xMTNwlnFU3JE0ozuRfKaZIZp+qdc4c0K+qPdWQ1tnZADvs7jTcUjneqMX8Cn+XbZ
9d98doN6IB8HTF0CAwEAATANBgkqhkiG9w0BAQUFAAOCAQEAXaDunSjZqHQK/1cN
6iy3fhTPY/p72toNvBwlqUjS9Bt5mLs04F48tqvBbJgedtzL4xrtCURQcH5P5y5N
dIAfjnsie+4sAUdvdudUPlHRFr9TyBLG4F73g/V9+1q1rEqG8Mtgkh2YbBm/WyTh
RnxYogUkl42IMA2ucQqGHRIJPc5J0Cow+lcxA7K+QCatQlw4/Y6sC8jfPTXYknlE
8Zwl0Y3EBaaXROAeM+p97v8aqYw0ISi//YCGOFgmGWyx87W1zw8PC4Fz7PeDCG8F
M9QKqIdIARKqvcqdwrisVekiihpW3X8lmZylSMlxptXFHLk/d6j9KDvVteokO+ia
eFaV0A==
-----END CERTIFICATE-----
subject=/C=XX/L=Default City/O=Default Company Ltd
issuer=/C=XX/L=Default City/O=Default Company Ltd
---
No client certificate CA names sent
Client Certificate Types: RSA sign, DSA sign, ECDSA sign
Requested Signature Algorithms: ECDSA+SHA256:ECDSA+SHA384:ECDSA+SHA512:0x07+0x08:0x08+0x08:0x09+0x08:0x0A+0x08:0x0B+0x08:0x04+0x08:0x05+0x08:0x06+0x08:RSA+SHA256:RSA+SHA384:RSA+SHA512:ECDSA+SHA224:ECDSA+SHA1:RSA+SHA224:RSA+SHA1:DSA+SHA224:DSA+SHA1:DSA+SHA256:DSA+SHA384:DSA+SHA512
Shared Requested Signature Algorithms: ECDSA+SHA256:ECDSA+SHA384:ECDSA+SHA512:RSA+SHA256:RSA+SHA384:RSA+SHA512:ECDSA+SHA224:ECDSA+SHA1:RSA+SHA224:RSA+SHA1:DSA+SHA224:DSA+SHA1:DSA+SHA256:DSA+SHA384:DSA+SHA512
Peer signing digest: SHA512
Server Temp Key: ECDH, P-256, 256 bits
---
SSL handshake has read 2257 bytes and written 1471 bytes
---
New, TLSv1/SSLv3, Cipher is ECDHE-RSA-AES256-GCM-SHA384
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
SSL-Session:
    Protocol  : TLSv1.2
    Cipher    : ECDHE-RSA-AES256-GCM-SHA384
    Session-ID: 4C4D8CC2D6E9AAF4FA0D91962B9ED33E72361278584D8D7B71D19B7A64D462CC
    Session-ID-ctx: 
    Master-Key: DBACEFB713DB4544CFF7AB367EA54B8D90887FA2F10DDA1C565CD2144CFDFB0FA848139451DD737DA597D5256D22AAD9
    Key-Arg   : None
    Krb5 Principal: None
    PSK identity: None
    PSK identity hint: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 4b f3 94 38 b2 0a 44 84-d3 23 16 75 2f 9d b5 df   K..8..D..#.u/...
    0010 - d2 01 a2 db 71 19 73 95-56 b3 df 14 69 40 a6 04   ....q.s.V...i@..
    0020 - eb 37 87 96 e9 c1 8c d7-8d 9b f0 df 3a c7 ab ad   .7..........:...
    0030 - 29 82 ce f3 21 32 42 cf-76 67 52 32 f8 e9 9d 95   )...!2B.vgR2....
    0040 - 8c d9 a9 dd cb 36 fb 8b-c6 5f c0 f9 d1 0f 13 69   .....6..._.....i
    0050 - 5e bb 71 d1 c5 b0 0c c6-de 93 d9 5e 3e 7c 8d 32   ^.q........^>|.2
    0060 - ab c3 bb ad 68 75 5c 25-46 f1 54 6b 9b 8d 66 b7   ....hu\%F.Tk..f.
    0070 - 46 bf 3b ce 50 e9 99 f8-08 eb 17 c8 7c 00 90 e0   F.;.P.......|...
    0080 - e3 0d 2d 70 cd 0d a0 00-18 e8 87 7b ec 21 63 38   ..-p.......{.!c8
    0090 - f6 53 dc a4 be 48 0a 08-7f a2 26 e8 62 05 ad 1c   .S...H....&.b...
    00a0 - 66 7e 2e a9 34 3c 8a 7b-ba c3 5f ff 00 1e 73 5e   f~..4<.{.._...s^
    00b0 - 82 64 cc fd 8a 77 be 6a-3c 67 3c 90 01 89 d0 e4   .d...w.j<g<.....
    00c0 - f0 ef ac 2b f4 92 85 99-6c 2c 5b 8a 71 aa 32 6b   ...+....l,[.q.2k
    00d0 - ba ca f9 23 13 c7 98 87-74 7a 7d 0f ef 46 48 1f   ...#....tz}..FH.
    00e0 - 83 fd cc 94 21 d0 e3 7e-f6 db 3f f7 8c 7d 89 cf   ....!..~..?..}..
    00f0 - 8e d4 3c cb 5e 20 30 81-a7 6f ed a9 61 3b c2 bd   ..<.^ 0..o..a;..
    0100 - 44 4a f3 a4 bb 83 0f a7-1c 0f 42 73 08 8b 89 90   DJ........Bs....
    0110 - 93 02 6c a1 d7 e7 53 a9-11 29 9f 10 01 92 c3 43   ..l...S..).....C
    0120 - a3 5e 97 07 ad af b5 0c-86 b9 ee 3c 8d f8 3a b7   .^.........<..:.
    0130 - a6 a6 39 76 73 dd 68 a0-a5 0a 05 c0 e8 9e ac d9   ..9vs.h.........
    0140 - 76 44 28 34 8b 12 18 48-36 c3 e1 d6 b2 fe ae 21   vD(4...H6......!
    0150 - 09 db de 2e 3a a2 a3 bb-7c 0c 9a 59 7b c0 c1 45   ....:...|..Y{..E
    0160 - 0c 7d ed 47 53 91 b5 7a-98 b3 e9 53 8a de 72 a1   .}.GS..z...S..r.
    0170 - bc fe 56 36 e0 d6 14 65-47 a8 0c aa 43 78 a0 df   ..V6...eG...Cx..
    0180 - 63 10 92 d4 f0 36 47 c6-fa be bf 49 11 9d f8 96   c....6G....I....
    0190 - 8d 23 29 cb f9 e6 3a ea-f5 ce b6 0a 05 98 db 0f   .#)...:.........
    01a0 - af 25 90 14 8e 00 6f 3a-f6 0f 79 99 8f ee 6f 71   .%....o:..y...oq
    01b0 - 4e a0 3f 45 d3 ee 03 df-8c c8 4a 75 b0 eb 49 be   N.?E......Ju..I.
    01c0 - b4 94 d7 7e 98 ab 15 dc-00 dd ee 8e a7 47 cf 1a   ...~.........G..
    01d0 - ea 3d d3 5c 4c bc 92 ef-d2 f5 d5 c4 18 8e 7e 58   .=.\L.........~X
    01e0 - a9 b1 81 b0 04 21 05 ad-12 72 0e 43 8d e7 31 c3   .....!...r.C..1.
    01f0 - f2 be 6c 82 7e a5 a2 53-16 cb 7e 1d 8d 4f 7e a0   ..l.~..S..~..O~.
    0200 - 34 3f 67 87 be 6a 5c 90-6e f7 11 11 02 b6 ba 29   4?g..j\.n......)
    0210 - f8 9b 9c e0 d5 bb 2a de-04 0d 3b 09 da 8d 5a 16   ......*...;...Z.
    0220 - b8 d6 5d 2f 37 87 5a 9b-e0 96 bc d7 d8 04 da 09   ..]/7.Z.........
    0230 - 11 3c f8 79 ee 4b 1e e0-34 42 13 ba 43 14 91 02   .<.y.K..4B..C...
    0240 - 88 18 f5 e4 07 ad 82 1f-b4 d8 50 d9 9b 97 f8 81   ..........P.....
    0250 - 1b 77 f6 67 df db 90 3f-b5 07 fe ff 82 89 35 0e   .w.g...?......5.
    0260 - 1a cd 79 17 b6 bf ae 88-2f 23 94 e0 ab 57 47 5e   ..y...../#...WG^
    0270 - 84 dd a3 b3 08 23 a6 5d-b6 b3 72 5b 2a 46 bf 1a   .....#.]..r[*F..
    0280 - da f4 fd 17 7f 9f 41 34-08 fe 1a 73 99 c6 80 51   ......A4...s...Q
    0290 - f5 88 84 eb 44 53 fd 74-ad b6 bd d2 99 d7 4c 55   ....DS.t......LU
    02a0 - 17 78 9b 4d 2c 99 33 ce-c7 13 ae ce 0e e3 1a 35   .x.M,.3........5
    02b0 - f0 ec ad c3 64 ae 8d 92-8c 51 06 ac 55 cb f3 58   ....d....Q..U..X
    02c0 - d4 bd e2 3b 04 f3 ab 58-e2 86 b8 92 79 cf 7e 4e   ...;...X....y.~N
    02d0 - 16 84 b4 a7 52 b9 2f a3-28 6d ea de ec 59 4e c6   ....R./.(m...YN.
    02e0 - 7c 95 18 77 a7 23 56 1a-d0 d9 f8 c8 f4 be d0 40   |..w.#V........@
    02f0 - e7 79 e5 83 8e 38 35 6e-ba 60 a3 e9 58 5f 9a fb   .y...85n.`..X_..
    0300 - 90 f4 19 86 5c 1c d6 5e-68 40 27 7e ec 86 f7 67   ....\..^h@'~...g
    0310 - 79 0b 35 49 df b0 05 9f-20 80 90 24 45 11 ac 86   y.5I.... ..$E...
    0320 - 89 93 59 ea 34 f4 cd 8d-e9 2a 5d 25 b6 af d7 61   ..Y.4....*]%...a
    0330 - a4 f6 26 2a 96 bd 4e 61-5f 28 33 f3 c1 85 67 f5   ..&*..Na_(3...g.
    0340 - 12 5c 0d 2c 25 56 4e ed-32 67 6a 65 7b 30 e6 ff   .\.,%VN.2gje{0..
    0350 - 8f 48 29 cd c3 a9 e0 ac-8f be 13 e4 d5 f7 a6 2e   .H).............
    0360 - a3 14 e8 d2 9d 96 a7 47-66 3a 9a f0 94 d3 c4 ba   .......Gf:......
    0370 - e3 5b a2 1f 51 fb 47 aa-3f ac 94 af a6 f6 25 4d   .[..Q.G.?.....%M
    0380 - 99 f2 64 3e e7 d8 db 16-a4 e3 26 8e 9b 62 bf d8   ..d>......&..b..
    0390 - 97 c3 cb 74 c5 17 02 9d-e3 2c 63 5a 91 c7 ed d0   ...t.....,cZ....

    Start Time: 1554934430
    Timeout   : 300 (sec)
    Verify return code: 18 (self signed certificate)
---
test
read:errno=0
```

サーバ側には次のように表示されます。
```
$ ./server 
SSL_write start
Server certificates:
Subject: /C=XX/L=Default City/O=Default Company Ltd
Issuer: /C=XX/L=Default City/O=Default Company Ltd
```
