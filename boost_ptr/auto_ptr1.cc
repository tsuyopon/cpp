// auto_ptrは次に上げるような深刻な問題が存在するのでC++11以降での利用は非推奨となっている。
//  1. コピーによって コピー先にメモリの所有権が移動する。このため、気が付かない間に保持している auto_ptr<T>がアクセス不能になっている場合がある。
//  2. 内部処理でコピーを行うため、コンテナ（ std::vector<T>等）に入れることができない。
//  3. 配列を保持することができない。
//  4. deleter（後述）を指定することができない。

#include<iostream>
#include<memory>

int main(){
   //int型のメモリを動的に確保し、その所有権をauto_ptrに委ねる
   std::auto_ptr<int> ptr(new int(10));

   //operator*()で生ポインタのようにアクセスできる
   for(int i=0;i<10;++i){
      *ptr+=i;
   }
   std::cout<<"ptr="<<*ptr<<std::endl;

   return 0;
} //ディストラクタ内で、自動的にptrの中身をdelete
