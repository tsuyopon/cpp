// このプログラムでは、テンプレートを使ってインターフェイスの共通化を行なっています。
#include <iostream>
#include <type_traits>

template<class T>
class Interface; //prototype

// myclass4のようなインターフェースは同一でもInterfaceクラスを継承していない不正なクラスを弾くために、std::is_base_ofを使っています。
template<class T, bool isExtended = std::is_base_of<Interface<T>, T>::value>
class Printer{
    static_assert(isExtended, "T is not extended interface class");
};

template<class T>
class Printer<T, true>{
    T _obj;
    public:
        void print(){ _obj.print(); };
};

template<class T>
class Interface{
public:
   void print(){ static_cast<T &>(this)->print(); }
};

class myclass1 : Interface<myclass1> {
public:
    void print(){ std::cout << "myclass1" << std::endl; }
};

class myclass2 : Interface<myclass2> {
public:
    void print(){ std::cout << "myclass2" << std::endl; }
};

class myclass3 : Interface<myclass3> {
};

class myclass4 {
    void print(){ std::cout << "myclass4" << std::endl; }
};

int main(){

   Printer<myclass1> a;
   Printer<myclass2> b;
   Printer<myclass3> c;

   // 以下の行を有効にすると、myclass4はInterfaceで継承していないのでコンパイルエラーとなる
   //Printer<myclass4> d; //compile error

   a.print();
   b.print();

   return 0;
}

