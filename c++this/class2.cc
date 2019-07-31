// 基底クラスの関数からthis->test()を呼び出した際に、派生クラスのtest()を呼び出すようにするサンプルです。class1.ccと比較すると良い
// Baseクラスのtest()にvirtualを付与することでオーバーライドすることができます。
#include <iostream>

class Base
{
public:
    Base() { std::cout << "Base() called" << std::endl; }
    ~Base() { std::cout << "~Base() called" << std::endl; }
    void calltest() { std::cout << "Base::calltest called" << std::endl; this->test(); }
    virtual void test() { std::cout << "Base::test called" << std::endl; }    /*** virtualを付与していることに注意 **/
};

class Derived1 : public Base
{
public:
    Derived1() { std::cout << "Derived1() called" << std::endl; }
    ~Derived1() { std::cout << "~Derived1() called" << std::endl; }
    void test() { std::cout << "Derived1::test called" << std::endl; }
};

class Derived2 : public Base
{
public:
    Derived2() { std::cout << "Derived2() called" << std::endl; }
    ~Derived2() { std::cout << "~Derived2() called" << std::endl; }
    void test() { std::cout << "Derived2::test called" << std::endl; }
};

int main()
{
  {
    std::cout << "[[[Called From Base Object]]]" << std::endl;
    Base b;
    b.calltest();
  }

  {
    std::cout << std::endl << "[[[Called From Derived1 Object using Stack]]]" << std::endl;
    Derived1 d1;
    d1.calltest();
  }

  {
    std::cout << std::endl << "[[[Called From Derived1 Object using Heap]]]" << std::endl;
    Derived1 *d1 = new Derived1();
    d1->calltest();
    delete d1;
  }

  {
    std::cout << std::endl << "[[[Called From Derived2 Object using Stack]]]" << std::endl;
    Derived2 d2;
    d2.calltest();
  }

  {
    std::cout << std::endl << "[[[Called From Derived2 Object using Heap]]]" << std::endl;
    Derived2 *d2 = new Derived2();
    d2->calltest();
    delete d2;
  }

}
