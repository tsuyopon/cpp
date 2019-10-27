/*
 * weak_ptrは循環参照が必要に対応するための仕様である。
 * では、shared_ptrで発生する循環参照のプログラムを参考に紹介します。
 *
 * 参考: https://programming.pc-note.net/cpp/smartpointer3.html
 */
#include <iostream>
#include <memory>
 
class TestClass
{
public:
    std::shared_ptr<TestClass> ptr;
 
    TestClass(){ std::cout << "コンストラクタ" << std::endl; }
    ~TestClass() { std::cout << "デストラクタ" << std::endl; }
};
 
 
int main()
{
    {
        // shared_ptrで定義されていることに着目する
        std::shared_ptr<TestClass> ptr1 = std::make_shared<TestClass>();
        std::shared_ptr<TestClass> ptr2 = std::make_shared<TestClass>();
 
        // ptr1->ptrからはptr2を、ptr2->ptrからはptr1を相互に参照してしまっています。この状態を循環参照と呼びます。
        ptr1->ptr = ptr2;
        ptr2->ptr = ptr1;
    }
    // 循環参照の場合には、メモリは解放されない
 
    std::cin.get();
}
