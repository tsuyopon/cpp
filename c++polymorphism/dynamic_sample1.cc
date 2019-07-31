// 動的ポリモーフィズムのサンプル
#include<iostream>

class Base{
 public:
 virtual void print(){ std::cout << "Base" << std::endl; }
 virtual ~Base()=default;
};

class Super : public Base{
 public:
 void print() override{ std::cout << "Super" << std::endl; }
};

int main(){
 Base* array[2] = {new Base,new Super} ;
 array[0]->print();   // Base
 array[1]->print();   // Super
 delete array[0]; delete array[1];
 return 0;
}
