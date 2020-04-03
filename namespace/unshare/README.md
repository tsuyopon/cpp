# 概要
unshare()システムコールのソースコードを確認

# 実行
実行プログラムはroot権限を使って実行する必要があります。

### CLONE_NEWNETの挙動を確認
```
$ ip link
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: enp0s3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAULT group default qlen 1000
    link/ether 08:00:27:ab:27:97 brd ff:ff:ff:ff:ff:ff
$ sudo ./a.out -n ip link
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
```

# 参考URL
- https://linuxjm.osdn.jp/html/LDP_man-pages/man2/unshare.2.html
