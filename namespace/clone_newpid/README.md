# 概要
clone(2)システムコールのflagsにCLONE_NEWPIDを指定した場合のサンプル

# 実行
実行プログラムはroot権限を使って実行する必要があります。
```
## 上記プログラムをroot(特権ユーザー)で実行
clone() = 3063
My PID: 3062
Child PID: 1   ## 子プロセスからは自分のPIDは1に見える
Parent PID: 0  ## 子プロセスからは親プロセスのPIDは0に見える
```

clone(2)でクローンされたプログラムのPPIDは0で、そのプロセス自体のIDは1となっていることが確認できます。

# 参考URL
- https://qiita.com/wellflat/items/7d62f2a63e9fcddb31cc
