# 概要
TCPパケットに生データを付加するプログラムです。

# 詳細

### http_sample.c
HTTPリクエストを送付するプログラムです。
「GET /」をした後に、受け取ったデータを表示するだけのプログラムです。


### tls_client_hello.c
TCPの3 way handshakeを実施した後にTLSのClientHelloデータを送るプログラムです。
このプログラムの例ではTLSのClientHelloを送付します。

TLSのClientHelloデータを解析するには次のコマンドを実行して確認すると良いでしょう。
```
$ sudo tshark -i lo -V -d tcp.port==443,ssl -Y ssl
```

