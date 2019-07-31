// Base::calltestで呼ばれるthis->test()は各種派生クラスが呼び出されることを期待しているが、Base::testが必ず呼ばれてしまう。
// この場合Base::testへvirtualが付与されていないことが上記問題を引き起こしている。
#include <iostream>

class Base
{
public:
    Base() { std::cout << "Base() called" << std::endl; }
    ~Base() { std::cout << "~Base() called" << std::endl; }
    void calltest() { std::cout << "Base::calltest called" << std::endl; this->test(); }
    void test() { std::cout << "Base::test called" << std::endl; }       // virtualが付与されていないので、this->test()が呼ばれると必ずBase::test()が呼ばれます。
};

class Derived1 : public Base
{
public:
    Derived1() { std::cout << "Derived1() called" << std::endl; }
    ~Derived1() { std::cout << "~Derived1() called" << std::endl; }
    void test() { std::cout << "Derived1::test called" << std::endl; }   // ここは呼ばれない
};

class Derived2 : public Base
{
public:
    Derived2() { std::cout << "Derived2() called" << std::endl; }
    ~Derived2() { std::cout << "~Derived2() called" << std::endl; }
    void test() { std::cout << "Derived2::test called" << std::endl; }   // ここは呼ばれない
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
