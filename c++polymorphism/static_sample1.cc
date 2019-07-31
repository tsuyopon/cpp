// 静的ポリモーフィズムの簡単な例
//
// しかし、これにはまだ問題があります。
// Printer<myclass1>とPrinter<myclass2>は別クラスなので、1つの配列で複数の種類のインスタンスを格納できません。
// (改善プログラムはまだありません)

#include<iostream>

class myclass1{
 public:
    void print(){ std::cout << "myclass1" << std::endl; }
};

class myclass2{
public:
    void print(){ std::cout << "myclass2" << std::endl; }
};

template<class T>
class Printer{
T obj;
public:
   void print(){
        obj.print();
   }
};

int main(){
    Printer<myclass1> a;
    Printer<myclass2> b;

    a.print();
    b.print();

    return 0;
}
