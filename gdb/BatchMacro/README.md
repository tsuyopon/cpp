# 概要
バッチ処理を行う場合の方法について

# 詳細
起動時に何か特定のブレークポイントを貼って、その後特定の何かをしたいといった際にバッチ機能が役立ちます。

Makefileは次のように定義されています。batchオプションでその後にxを指定してマクロファイルを指定しています。
```
all:
    g++ -g test.cpp -o test
    gdb ./test -batch -x test.macro
```

たとえば、test.macroを次のように準備します。
```
$ cat test.macro 
break Show
run
p student
cont
p student
cont
p student
quit
```

上記のmacroがインタラクティブに実行されているかのように表示されます。
```
$ make
Breakpoint 1, Show (student=@0x7fff5fbff960) at test.cpp:15
15		cout << "Name : " << student.name << endl;
$1 = (const Student &) @0x7fff5fbff960: {
  name = "taro", '\0' <repeats 12 times>, 
  scoreJapanese = 73, 
  scoreMath = 98, 
  scoreEnglish = 86
}
Name : taro
Japanese=73, Math=98, English=86

Breakpoint 1, Show (student=@0x7fff5fbff980) at test.cpp:15
15		cout << "Name : " << student.name << endl;
$2 = (const Student &) @0x7fff5fbff980: {
  name = "jiro", '\0' <repeats 12 times>, 
  scoreJapanese = 64, 
  scoreMath = 45, 
  scoreEnglish = 40
}
Name : jiro
Japanese=64, Math=45, English=40

Breakpoint 1, Show (student=@0x7fff5fbff9a0) at test.cpp:15
15		cout << "Name : " << student.name << endl;
$3 = (const Student &) @0x7fff5fbff9a0: {
  name = "saburo\000\000\000\000\000\000\000\000\000\000", 
  scoreJapanese = 76, 
  scoreMath = 78, 
  scoreEnglish = 69
}
```
