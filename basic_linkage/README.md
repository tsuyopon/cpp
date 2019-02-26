# ライブラリ関連
- dynamiclib
  - ダイナミックライブラリ作成について
- staticlib
  - スタティックライブラリ作成について
- dl
  - dlopenなどを利用したプログラムについて
- c_into_cpp
  - C言語のプログラムをCPPから呼び出す方法について


# dlopenを使ったライブラリの読み込み動作
- メインプログラムからdlopenしてsoファイルを開く場合
  - メインプログラムで最初にリンクされてしまったら、たとえso側でrpathを指定していても同じバージョンのライブラリをリンクしている限りメインプログラム側のライブラリのみが読み込まれる。
  - 例えば、/usr/lib/libxxxx.soをメインプログラムで読み込みso側も同じlibxxxx.soをrpathで指定された/rpath/to/libxxxx.soにあったとしても共有ライブラリのバージョンのバージョンが一致している限りは同じ
- メインプログラムとsoファイルで異なるバージョンでリンクした場合 
  - ビルド時に異なるsoバージョンでビルドした場合には、ELF中にはsoバージョンまで保持してる。
  - よって、この場合にはメインプログラム側で読み込んだバージョンとsoファイルで読み込んだライブラリがともにpmapで表示される。
  - たとえば、メインプログラムでは/usr/lib/libxxxx.so(libxxxx.so.10)、soファイルでは/rpath/to/libxxxx.so(libxxxx.so.11)などのようにリンクしたsoバージョンで最初に見つかったパスが利用されることになる。
- 下位ライブラリの互換性を保ちたい場合
  - メインプログラムから読み込まれるライブラリのパスを変更したい場合には、たとえロジックとしてそのAPIを使っていなかったとしてもrpath、-l(-L, -I)を指定して現在利用しているSOバージョンと合わせて於けば良い。


# MEMO
サンプルにはないけどmemo
- ライブラリを結合して大きなライブラリを作りたい場合にはno-whole-archiveオプションを利用するらしい
- 古いコンストラクタとデストラクタの仕組み(	\_initと\_finiを使いたかったら-nostartfilesオプションを付与する)


# 参考
- (Program Library HowTo)[https://linuxjf.osdn.jp/JFdocs/Program-Library-HOWTO/]
- (Shared library support for GNU)[http://web.sfc.wide.ad.jp/~sagawa/gnujdoc/libtool-1.4.2/index.html]
- (Beginner's Guide to Linkers)[http://www.lurklurk.org/linkers/linkers.html]
