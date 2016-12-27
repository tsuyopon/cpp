# soを動的にロードするhelloworld的なプログラム

# ポイント
- 共有ライブラリのコンパイルには-staticの他に-fPICも必要です
- dlopenやdlsymを使うmainプログラム側は-ldl指定が必要です。

# 参考
- http://kaworu.jpn.org/kaworu/2008-11-26-1.php

