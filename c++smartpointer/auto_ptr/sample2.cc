/*
 * auto_ptrの深刻な問題点について
 *   コピーによって コピー先にメモリの所有権が移動する。このため、気が付かない間に保持している auto_ptr<T>がアクセス不能になっている場合がある。
 * 
 * このほかにもいくつかの問題が指摘されているが詳細は以下を確認すること
 *   https://qiita.com/hmito/items/db3b14917120b285112f
 *
 * よって、C++11以降ではauto_ptrが推奨されていません。
 *
 */
#include<iostream>
#include<memory>
class hoge{
private:
   std::auto_ptr<int> ptr;
public:
   hoge(int val_):ptr(new int(val_)){}
   int getValue()const{return *ptr;}
};

int main(){
   //hogeのコンストラクタでint型を動的に確保しauto_ptrに委ねる
   hoge Hoge(10);

   //コピーコンストラクタで二つ目のhogeを作成
   //この時Hoge.ptrからHoge2.ptrに所有権が移動！
   hoge Hoge2(Hoge);

   //Hogeの値を呼び出す
   Hoge.getValue();  //===ERROR===
   //実行時エラー！
   //Hoge.ptrはすでに所有権を失っているので、アクセスできない

   return 0;
}
