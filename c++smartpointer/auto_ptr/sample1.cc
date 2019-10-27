/* g++ -std=c++03 sample1.cc
 *
 * auto_ptrはC++03まで用意されていた機能です。
 * delete 解放漏れを防ぐことができます。しかし、auto_ptr<T>には深刻な問題がある。これはsample2.ccで確認する。
 */

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

   // deleteを記述する必要がなくなる

   return 0;
}
