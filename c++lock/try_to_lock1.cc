#include <iostream>
#include <mutex>
#include <stdexcept>

int main()
{
    std::mutex mtx;
    {
        std::unique_lock<std::mutex> lk(mtx, std::try_to_lock); // try_lock()が呼ばれる

        if (!lk.owns_lock()) {
            throw std::runtime_error("ロックの取得に失敗！");
        }

        // 共有リソースにアクセス...

    } // unlock()が呼ばれる
}
