# 概要
HTTP/2のクライアントについて

# 詳細
- client.cc
  - TLSを使わないでhttp://nghttp2.org/にHTTP/2で接続するサンプルプログラム。TLSを使っていないので、実際とは若干乖離しています。
- tlsclient.cc
  - TLSを使ってhttps://www.yahoo.co.jp/にHTTP/2で接続するサンプルプログラム
