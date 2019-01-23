# 概要
openssl-1.0.2からはALPNがサポートされています。

- server.c
  - ALPNを選択するコールバック関数SSL_CTX_set_alpn_select_cbを利用して、ClientHelloからのALPN応答を選択しています
  - 選択したALPNをSSL_get0_alpn_selected() で取得しています。
- client_SSL.c
  - これから修正予定


# サンプルリクエスト

server.cをコンパイルして4433ポートを起動する。
```
$ make
$ ./server
```

接続して確認を行う。
```
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect 127.0.0.1:4433 -alpn "http/1.1" | grep -i ALPN -A 3 -B 3
depth=0 C = XX, L = Default City, O = Default Company Ltd
verify error:num=18:self signed certificate
verify return:1
depth=0 C = XX, L = Default City, O = Default Company Ltd
verify return:1
DONE
Secure Renegotiation IS NOT supported
Compression: NONE
Expansion: NONE
ALPN protocol: http/1.1
Early data was not sent
Verify return code: 18 (self signed certificate)
---
```

# 参考URL
- https://qiita.com/tatsuhiro-t/items/dea3fb279ad265681049
- https://www.openssl.org/docs/man1.1.0/ssl/SSL_CTX_set_alpn_select_cb.html


# TODO
- s_clientでの接続初回はALPNコールバックが呼ばれていないので、なぜかを確認する
