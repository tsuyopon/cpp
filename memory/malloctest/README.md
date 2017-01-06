# 概要
mallocの動作を確認するサンプルプログラム
文字の入力を受け付ける前にmallocで128KB未満(heap)か128KB以上(mmap)かの出しわけ処理を行う

# 確認方法 
### (1) heapを使う確認をする場合
```
$ make heap
$ ./useheap
```
別のターミナルから
```
$ sudo cat /proc/`pidof useheap`/maps
```
[heap]が**ある**ことが確認できる

### (2) mmapを使う確認をする場合
```
$ make mmap
$ ./usemmap
```
別のターミナルから
```
$ sudo cat /proc/`pidof usemmap`/maps
```
[heap]が**ない**ことが確認できる


### (1)と(2)のstraceの差分を比較してみる。
```
$ sudo strace ./useheap 2> heap.txt
(ここでCtrl+C)
$ sudo strace ./usemmap 2> mmap.txt
(ここでCtrl+C)
$ vimdiff heap.txt mmap.txt
```

比較するとheapを使う方だけbrkシステムコールが呼ばれていることが確認できる。  
mallocの行っているheap処理のgrewとshrineはbrk, sbrkシステムコールによって行われている。
