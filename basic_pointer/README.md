# 概要
ポインタ関連について
ただし、ここではC Basedなポインタのみについて

# 詳細

- pointer_of_pointer_NG.c, pointer_of_pointer_OK.c
  - ポインタのポインタで起こる問題点とポインタのポインタの利用する意味がわかるプログラムを準備しているので比較して確認すること
```
// 異常な場合
$ gcc pointer_of_pointer_NG.c 
tsuyoshi@tsuyoshi:~/git/cpp/basic_pointer$ ./a.out 
Segmentation fault (core dumped)

// 正常な場合
$ gcc pointer_of_pointer_OK.c 
$ ./a.out 
45
45
45
45
45
```
