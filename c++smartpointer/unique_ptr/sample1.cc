/* $ g++ -std=c++11 sample1.cc 
 *
 * unique_ptrを使ったサンプルプログラムです。
 * ポイントとしては、メモリ上の所有権を1つのポインタしか存在しないことを保証してくれます。このサンプルでは次の点を確認できます。
 *    コピーコンストラクタしようとすると、unique_ptrはコンパイルエラーとなります。
 *    所有権をstd::moveで明示的に指定するのであれば、コピーコンストラクタの場合にコンパイルエラーとなりません。
 * 
 */
#include<iostream>
#include<memory>
class hoge{
private:
   std::unique_ptr<int> ptr;              // ここでunique_ptrを指定する
public:
   hoge(int val_):ptr(new int(val_)){}
   int getValue()const{return *ptr;}
};

int main(){
   //hogeのコンストラクタでint型を動的に確保しunique_ptrに委ねる
   hoge Hoge(10);

   //unique_ptrはコピーできないので、
   //コピーコンストラクタで作成しようとすると、コンパイルエラー
   //hoge Hoge2(Hoge);  //===ERROR===

   //明示的にmoveするならOK
   hoge Hoge2(std::move(Hoge));

   return 0;
}//auto_ptr同様、ディストラクタで自動的にメモリ解放
