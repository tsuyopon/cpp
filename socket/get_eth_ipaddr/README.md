# 概要
eth0のIPアドレスを取得する方法として次の２つがある。
ioctlの方はかなり直感的。
- ioctl(2)によるインターフェイスの操作
- netlink(7)によるインターフェイスの操作

ifconfigなどはioctlによる参照をしていて、ip addrなどのコマンドではnetlinkを使っているらしい(実装は見ていない)

# 参考資料
- http://moriyoshi.hatenablog.com/entry/2012/10/28/025220
