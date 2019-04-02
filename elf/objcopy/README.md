# objcopyを使う

objcopyコマンドを使うことによって

gmakeコマンドを実行すると次のような出力になります。
objectファイルを生成した後にobjcopyコマンドを使ってオブジェクトファイルにbindataセクションとしてbinary.datを追加していることが確認できます。
```
$ gmake
gcc -c binary.c 
binary.c: In function 'main':
binary.c:10:40: warning: cast from pointer to integer of different size [-Wpointer-to-int-cast]
   printf("__start_bindata = 0x%08x\n", (int)(&__start_bindata));
                                        ^
binary.c:11:39: warning: cast from pointer to integer of different size [-Wpointer-to-int-cast]
   printf("__stop_bindata = 0x%08x\n", (int)(&__stop_bindata));
                                       ^
objcopy --add-section=bindata=binary.dat --set-section-flags=bindata=contents,alloc,load,readonly,data binary.o binary_tmp.o
gcc binary_tmp.o -o binary
./binary
__start_bindata = 0x004006b3
__stop_bindata = 0x004006bf
Hello World
```

readelfコマンドを使うことで新しくbindataというセクションが追加されたことを確認することができます。
```
$ readelf -W -S binary_tmp.o
There are 14 section headers, starting at offset 0x450:

Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        0000000000000000 000040 000065 00  AX  0   0  1
  [ 2] .rela.text        RELA            0000000000000000 000360 0000d8 18   I 12   1  8
  [ 3] .data             PROGBITS        0000000000000000 0000a5 000000 00  WA  0   0  1
  [ 4] .bss              NOBITS          0000000000000000 0000a5 000000 00  WA  0   0  1
  [ 5] .rodata           PROGBITS        0000000000000000 0000a5 000033 00   A  0   0  1
  [ 6] .comment          PROGBITS        0000000000000000 0000d8 00002e 01  MS  0   0  1
  [ 7] .note.GNU-stack   PROGBITS        0000000000000000 000106 000000 00      0   0  1
  [ 8] .eh_frame         PROGBITS        0000000000000000 000108 000038 00   A  0   0  8
  [ 9] .rela.eh_frame    RELA            0000000000000000 000438 000018 18   I 12   8  8
  [10] bindata           PROGBITS        0000000000000000 000140 00000c 00   A  0   0  1
  [11] .shstrtab         STRTAB          0000000000000000 00014c 000069 00      0   0  1
  [12] .symtab           SYMTAB          0000000000000000 0001b8 000168 18     13  10  8
  [13] .strtab           STRTAB          0000000000000000 000320 00003d 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)
```

binary.datに含まれる「Hello World」は上記のbindataが始まるオフセット00140と同じ以下の箇所に配置されていることが確認できます。
```
$  hexdump -C binary_tmp.o | grep "Hello World"
00000140  48 65 6c 6c 6f 20 57 6f  72 6c 64 0a 00 2e 73 79  |Hello World...sy|
```

このほかにも関数を埋め込む方法なども参考URLで紹介されているので必要あればそちらを参照すること

# 参考URL
- http://yktwww.hatenablog.com/entry/2016/07/06/024752
