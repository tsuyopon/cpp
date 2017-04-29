#include <iostream>

// dynamic_castは安全な基底クラスから派生クラスへのキャスト(ダウンキャスト)時に用いる。
// ただし、基底クラスにはデストラクタを定義しないとdynamic_castは多態性を持っていると認識されない仕組みらしい。
// 派生クラスから基底クラスにも用いることが可能だがこの場合にはstatic_castが一般的らしい

class Base {};
class Derived: public Base {};

// 多態性を持たせるためには基底クラスにデストラクタ定義が必要となる。これをしないと基底クラスから派生クラスへのdynamic_cast変換で失敗します。
// (参考) http://stackoverflow.com/questions/15114093/getting-source-type-is-not-polymorphic-when-trying-to-use-dynamic-cast
class Base2 {
  public:
    virtual ~Base2(){}
};
class Derived2: public Base2 {};

int main(void) {

    /*
     *  BaseとDerivedの変換
     */
    // downcastの場合(基底クラスから派生クラスへのキャスト)
    Base * a = new Base;
    Derived * b = static_cast<Derived*>(a);
    //Derived * b_2 = dynamic_cast<Derived*>(a);   // downcmic_castastの場合のdynamic_castはコンパイルエラーになる
    // "dynamic_cast.cc:11:45: error: cannot dynamic_cast ‘a’ (of type ‘class Base*’) to type ‘class Derived*’ (source type is not polymorphic)" といったエラーが表示される

    // upcastの場合(派生クラスから基底クラスへのキャスト)
    Derived * a2 = new Derived;
    Base * b2 = static_cast<Base*>(a2);
    Base * b2_2 = dynamic_cast<Base*>(a2);


    /*
     *  Base2とDerived2の変換
     */
    // downcastの場合(基底クラスから派生クラスへのキャスト)
    Base2 * c = new Base2;
    Derived2 * b3 = static_cast<Derived2*>(c);
    Derived2 * b3_2 = dynamic_cast<Derived2*>(c);     // 先程はエラーだったのがBase2に「virtual ~Base2(){}」を定義しただけでエラーがでなくなる。

    // upcastの場合(派生クラスから基底クラスへのキャスト)
    Derived2 * d = new Derived2;
    Base2 * b4 = static_cast<Base2*>(d);
    Base2 * b4_2 = dynamic_cast<Base2*>(d);

}
