# SSLハンドシェイクテスト

コンパイルはmakeするだけで即座に作成できます。
```
$ make
```

SSLサーバとして予め起動します。
```
$ ./server
```

ssldumpコマンドを使うとclientがserverに接続した際にハンドシェイクなどの処理を表示してくれます。
```
$ sudo dumpssl/ssldump/ssldump -n -H -i lo
```

別のターミナルからclientを実行するとssldumpに出力されます。
```
$ ./client
```


# ssldumpサンプル
```
$ sudo dumpssl/ssldump/ssldump -n -H -i lo
New TCP connection #1: 127.0.0.1(34491) <-> 127.0.0.1(8000)
1 1  0.0009 (0.0009)  C>S  Handshake
      ClientHello
        Version 3.1 
        cipher suites
        TLS_DHE_RSA_WITH_AES_256_CBC_SHA
        TLS_DHE_DSS_WITH_AES_256_CBC_SHA
        TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA
        TLS_DHE_DSS_WITH_CAMELLIA_256_CBC_SHA
        TLS_RSA_WITH_AES_256_CBC_SHA
        TLS_RSA_WITH_CAMELLIA_256_CBC_SHA
        TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA
        TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA
        TLS_RSA_WITH_3DES_EDE_CBC_SHA
        TLS_DHE_RSA_WITH_AES_128_CBC_SHA
        TLS_DHE_DSS_WITH_AES_128_CBC_SHA
        TLS_DHE_RSA_WITH_SEED_CBC_SHA
        TLS_DHE_DSS_WITH_SEED_CBC_SHA
        TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA
        TLS_DHE_DSS_WITH_CAMELLIA_128_CBC_SHA
        TLS_RSA_WITH_AES_128_CBC_SHA
        TLS_RSA_WITH_SEED_CBC_SHA
        TLS_RSA_WITH_CAMELLIA_128_CBC_SHA
        TLS_RSA_WITH_RC4_128_SHA
        TLS_RSA_WITH_RC4_128_MD5
        TLS_DHE_RSA_WITH_DES_CBC_SHA
        TLS_DHE_DSS_WITH_DES_CBC_SHA
        TLS_RSA_WITH_DES_CBC_SHA
        TLS_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA
        TLS_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA
        TLS_RSA_EXPORT_WITH_DES40_CBC_SHA
        TLS_RSA_EXPORT_WITH_RC2_CBC_40_MD5
        TLS_RSA_EXPORT_WITH_RC4_40_MD5
        TLS_EMPTY_RENEGOTIATION_INFO_SCSV
        compression methods
                  NULL
1 2  0.0011 (0.0001)  S>C  Handshake
      ServerHello
        Version 3.1 
        session_id[32]=
          b5 c9 53 c9 db 5a 08 1a 70 18 aa d8 65 ef ed e1 
          d1 ce 4e 96 a2 1a 55 9e 39 32 6b eb 2f d0 1c 61 
        cipherSuite         TLS_RSA_WITH_AES_256_CBC_SHA
        compressionMethod                   NULL
1 3  0.0011 (0.0000)  S>C  Handshake
      Certificate
1 4  0.0011 (0.0000)  S>C  Handshake
      ServerHelloDone
1 5  0.0040 (0.0029)  C>S  Handshake
      ClientKeyExchange
1 6  0.0040 (0.0000)  C>S  ChangeCipherSpec
1 7  0.0040 (0.0000)  C>S  Handshake
1 8  0.0151 (0.0110)  S>C  ChangeCipherSpec
1 9  0.0151 (0.0000)  S>C  Handshake
1 10 0.0151 (0.0000)  S>C  Alert
1    0.0151 (0.0000)  S>C  TCP FIN
1 11 0.0152 (0.0000)  C>S  Alert
```

# MEMO
鍵はこのプログラムだけのために適当に作成したやつです
```
$ openssl genrsa 2048 > server.key
$ openssl req -new -key server.key > server.csr
$ openssl x509 -days 3650 -req -signkey server.key < server.csr > server.crt
```
