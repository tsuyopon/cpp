# 概要
Unix Domain Socketについて

# 参考
- https://ja.wikipedia.org/wiki/UNIX%E3%83%89%E3%83%A1%E3%82%A4%E3%83%B3%E3%82%BD%E3%82%B1%E3%83%83%E3%83%88
- UnixドメインソケットのManpage
 - https://linuxjm.osdn.jp/html/LDP_man-pages/man7/unix.7.html

# 概要

### 動作を確認する。
serverを起動した状態で、clientプログラムを実行すると、server側プログラムで以下の出力が表示されます。
```
$ ./server 
message: Hello World!
```


### curlをクライアントとして確認する。
サーバを起動した状態で、curlでunix domain socketの確認をすることもできます。
```
$ curl --unix-socket /tmp/unix-domain-socket test
```

以下のメッセージが確認できます。
```
message: GET / HTTP/1.1
Host: test
User-Agent: curl/7.54.0
Accept: */*
```
