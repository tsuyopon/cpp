/*
 *  同一のメモリの所有権を複数で共有できるようにしたスマートポインタ
 *
 */
#include<memory>
#include<iostream>
int main(){

   //空のshared_ptrを作成
   std::shared_ptr<int> ptr;

   {
      //intの所有権を持つ、ptr2を作成
      std::shared_ptr<int> ptr2(new int(0));

      //ptr2の所有権をptrにコピー、共有する
      ptr=ptr2;

      *ptr+=10;
      *ptr2+=10;

   } //ここで、ptr2のディストラクタが呼ばれる。ptrも同一のメモリに対する所有権を持っているため、まだ解放はされない

   // ptrはまだ使用可能
   std::cout<<"ptr="<<*ptr<<std::endl;  //"ptr=20"と出力

}
