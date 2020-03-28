# 概要
配列の定義とポインタの定義の非常に単純なサンプルです。
また、オブジェクトの中ものぞいてみましょう。


# 詳細

コンパイルして実行してみましょう。

配列(s1)は値とアドレスが変わりません。
ポインタ(s2)は値とアドレスが変わることに着目してください。

```
$ ./a.out 
 s1     = 0x00601038
&s1     = 0x00601038
&s1[0]  = 0x00601038
&s1[1]  = 0x00601039
 s2     = 0x004006e0
&s2     = 0x00601048
&s2[0]  = 0x004006e0
&s2[1]  = 0x004006e1
siteof(s1) = 12
siteof(s2) = 8
```


以下のVMAのアドレスで論理アドレスを確認してみます。
s2の文字列は0x004006e0に存在するので、以下のVMAを参照すると.rodataに存在することがわかります。そして、s2ポインタのアドレス自体は.dataに存在します。
s1は値もアドレスも0x00601038となっているので、s1は.dataに存在することがわかります。
```
$ objdump -h a.out 

a.out:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn

(snip)

 10 .init         0000001a  0000000000400400  0000000000400400  00000400  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 11 .plt          00000040  0000000000400420  0000000000400420  00000420  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 12 .plt.got      00000008  0000000000400460  0000000000400460  00000460  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 13 .text         00000252  0000000000400470  0000000000400470  00000470  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .fini         00000009  00000000004006c4  00000000004006c4  000006c4  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 15 .rodata       000000d0  00000000004006d0  00000000004006d0  000006d0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 16 .eh_frame_hdr 00000034  00000000004007a0  00000000004007a0  000007a0  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 17 .eh_frame     000000f4  00000000004007d8  00000000004007d8  000007d8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 18 .init_array   00000008  0000000000600e10  0000000000600e10  00000e10  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 19 .fini_array   00000008  0000000000600e18  0000000000600e18  00000e18  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 20 .jcr          00000008  0000000000600e20  0000000000600e20  00000e20  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 21 .dynamic      000001d0  0000000000600e28  0000000000600e28  00000e28  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 22 .got          00000008  0000000000600ff8  0000000000600ff8  00000ff8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 23 .got.plt      00000030  0000000000601000  0000000000601000  00001000  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 24 .data         00000020  0000000000601030  0000000000601030  00001030  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 25 .bss          00000008  0000000000601050  0000000000601050  00001050  2**0
                  ALLOC
 26 .comment      0000002d  0000000000000000  0000000000000000  00001050  2**0
                  CONTENTS, READONLY
```
