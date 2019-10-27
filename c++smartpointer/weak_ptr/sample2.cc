/*
 *
 * 参考: https://programming.pc-note.net/cpp/smartpointer3.html
 */
#include <iostream>
#include <memory>
 
int main()
{
    std::shared_ptr<int> sPtr1 = std::make_shared<int>(10);
    std::shared_ptr<int> sPtr2(sPtr1);
    std::weak_ptr<int> wPtr(sPtr1);
 
    // 参照先のshared_ptrのメモリ領域の所有者数はuse_count関数で確認できます。
    std::cout << wPtr.use_count() << std::endl;
 
    if(wPtr.expired())
        std::cout << "解放済み" << std::endl;
    else
        std::cout << "解放されていない" << std::endl;
 
    sPtr1.reset();
    sPtr2.reset();
 
    if (wPtr.expired())
        std::cout << "解放済み" << std::endl;
    else
        std::cout << "解放されていない" << std::endl;
 
    std::cin.get();
}
