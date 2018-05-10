# 概要

- server.c
  - サーバサンプル
- クライアント
  - client_BIO.c: BIOを使ったサンプル
  - client_SSL.c: SSLを使ったサンプル  

# 詳細
このサンプルではSSLv3もできます。(POODLE攻撃が可能となるので利用しないでください)
```
$ openssl s_client -ssl3 -connect localhost:4433
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
Server Temp Key: ECDH, P-256, 256 bits
---
SSL handshake has read 1293 bytes and written 298 bytes
---
New, TLSv1/SSLv3, Cipher is ECDHE-RSA-AES256-SHA
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
SSL-Session:
    Protocol  : SSLv3
    Cipher    : ECDHE-RSA-AES256-SHA
    Session-ID: A08AC6B8DD9EAD08FFB6181C9AAF3C7464BFD9CDC63651109AD921D7C3E4223E
    Session-ID-ctx: 
    Master-Key: 9E1A8148EE5E9875466D5074B8EC08FB58247F724A10A60BCE8A04D2AA16A2FB4E50E9378E54407C56ADD3B89DC31DAE
    Key-Arg   : None
    Krb5 Principal: None
    PSK identity: None
    PSK identity hint: None
    Start Time: 1525209593
    Timeout   : 7200 (sec)
    Verify return code: 18 (self signed certificate)
---
test
read:errno=0
```
