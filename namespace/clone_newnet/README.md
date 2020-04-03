# 概要
clone(2)システムコールのflagsにCLONE_NEWNETを指定した場合のサンプル

# 実行
実行プログラムはroot権限を使って実行する必要があります。

以下のプログラムを実行するとclone(2)で生成されたプロセス空間はloのみしか生成されていないことが確認できます。
```
$ sudo ./a.out 
Original `net` Namespace:
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: enp0s3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAULT group default qlen 1000
    link/ether 08:00:27:ab:27:97 brd ff:ff:ff:ff:ff:ff


New `net` Namespace:
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
```


試しに、プログラムからCLONE_NEWNETを抜いてビルドし直して、実行すると実行元の状況と全く同一の状態であることが確認できます。
```
$ sudo ./a.out 
Original `net` Namespace:
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: enp0s3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAULT group default qlen 1000
    link/ether 08:00:27:ab:27:97 brd ff:ff:ff:ff:ff:ff


New `net` Namespace:
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: enp0s3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAULT group default qlen 1000
    link/ether 08:00:27:ab:27:97 brd ff:ff:ff:ff:ff:ff
```

# 参考URL
- https://qiita.com/wellflat/items/7d62f2a63e9fcddb31cc
