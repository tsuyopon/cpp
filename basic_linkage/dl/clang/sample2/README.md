# dlopenしたsoの中からmain中に定義された関数を呼び出す場合

## 課題
- main.cのコンパイル時に-export-dynamicを付与しないと、実行時にmainhoge()がundefined symbolだと表示される。

## ポイント
- soからmain.c中のシンボルが見えるように-export-dynamicを付与すれば実行できる。
- 試しに-export-dynamicを抜いて実行してみると良い
