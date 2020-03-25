# 概要
ASN1をダンプするプログラムサンプル

以下のサイトに掲載されているプログラムです。
- https://www.cs.auckland.ac.nz/~pgut001/

コンパイル方法はgccでコンパイルするだけです。
```
$ gcc dumpasn1.c
```

設定ファイルであるdumpasn1.cfgも実行ファイルと同一ディレクトリ上に配置する必要があります。

# 使い方

### サーバ証明書
以下の出力からBEGIN CERTIFICATE, END CERTIFICATEまでを取得してファイルcert.pemに保存する
```
$ echo -n | openssl s_client -connect www.yahoo.co.jp:443 -showcerts
$ openssl x509 -in cert.pem -inform PEM -out cert.der -outform DER
```

あとは次の様に引数に入れて実行するだけ。
```
$ ./dumpasn1 -al cert.der
```

### 公開鍵
対象をderファイルに変換する
```
$ echo -n | openssl s_client -connect www.google.com:443 | openssl x509 -noout -pubkey | openssl rsa -pubin -outform der >  google.der
```

出力サンプルは以下の通り

```
$ ./dumpasn1 -dial google.der
  0 290: SEQUENCE {
  4  13: . SEQUENCE {
  6   9: . . OBJECT IDENTIFIER rsaEncryption (1 2 840 113549 1 1 1)
       : . . . (PKCS #1)
 17   0: . . NULL
       : . . }
 19 271: . BIT STRING, encapsulates {
 24 266: . . SEQUENCE {
 28 257: . . . INTEGER
       : . . . . 00 EB 06 05 7A 53 0E EB 70 BD 0F E2 54 88 3B FD
       : . . . . 9F EB F2 D8 52 81 AB A2 5F 0F ED 6D 3E 67 09 52
       : . . . . BF EC 09 6C 53 61 0B BF CB A1 22 6A 4D 75 FB 5E
       : . . . . 03 C8 72 FF B3 3B 35 B6 2D 72 FD 0C F9 D7 80 73
       : . . . . A3 4A C3 26 8B 04 06 E5 05 7F A4 BF 64 C5 9F BC
       : . . . . 68 CE C7 3A 39 E0 1A 86 81 F6 09 2C BF 5C 3F 91
       : . . . . 43 65 30 D9 31 05 0B AA AA 5E B1 40 9A 68 71 AB
       : . . . . FB C9 02 B3 2D C7 B8 45 73 3D C0 BA 00 A6 F8 40
       : . . . . 53 1C FC 34 3B C2 50 FB EC 36 7B 67 26 E6 C4 0D
       : . . . . 53 4C A8 5D 41 62 8C 1A 60 C1 DF 1A A3 AA 39 BF
       : . . . . 14 28 C1 4D CB 97 52 EA 4F 15 47 FB 4E 40 18 FF
       : . . . . 69 60 08 01 C3 F5 75 A0 B3 B9 E6 E2 42 C8 30 38
       : . . . . F4 D3 3D 4E EF C9 09 C4 5D 21 81 E6 93 3B 26 1B
       : . . . . 59 58 1D 58 47 14 D4 5E 4C D5 09 92 D3 3E 25 43
       : . . . . D6 22 E5 15 29 9E 2F B5 19 E5 F8 DD DC 7D 14 52
       : . . . . 64 0E 83 A5 67 7C 45 68 FD 37 91 D4 60 BC C5 46
       : . . . . 15
289   3: . . . INTEGER 65537
       : . . . }
       : . . }
       : . }

0 warnings, 0 errors.
```

# 参考URL
使い方は以下のサイトを参考のこと
- https://qiita.com/hnw/items/8dcfb1befd5f8a15112c
