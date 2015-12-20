NASMとGASについて
====

# 概要
NASM(Netwide Assembler)とGAS(Gnu Assembler)について各々でまとめます。
デフォルトではgasだけが入っていることが多いが、簡単にネットで調べてみた感じだとどちらでも大差ないとのこと。
使いやすい方を選択すればいいらしい。

# 特記事項
- System V AMD64 ABI 呼出規約に従うこととする。よってWindowsやMacOSは対象外とする
 - https://ja.wikipedia.org/wiki/%E5%91%BC%E5%87%BA%E8%A6%8F%E7%B4%84

# 参考
- Linux のアセンブラー: GAS と NASM を比較する
 - http://www.ibm.com/developerworks/jp/linux/library/l-gas-nasm.html
