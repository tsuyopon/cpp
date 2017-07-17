// lock()/unlock()の呼び出しをRAIIで自動化します。
// lock_guradの拡張版です
//
//  g++ sample1.cc -std=c++11
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>  // sleep

class X {
    int value_ = 0;
    mutable std::mutex mtx_;   // mutableはconstなメンバー関数中でも操作できる変数(参考: http://soundengine.jp/wordpress/tips/tutorial/329/)
public:
    void add_value()
    {
		std::cout << "func start" << std::endl;
        std::unique_lock<std::mutex> lk = get_locked_mutex();   // 関連
		std::cout << "add_value() lock start" << std::endl;

        ++value_;
		std::cout << "add_value() lock end" << std::endl;
    } // ここでアンロックされる

    int get() const
    {
        std::unique_lock<std::mutex> lk = get_locked_mutex();
		std::cout << "get() lock start" << std::endl;
		sleep(1);
		std::cout << "get() lock end" << std::endl;
        return value_;
    }

private:
    std::unique_lock<std::mutex> get_locked_mutex() const
    {
        return std::unique_lock<std::mutex>(mtx_); // ロックして返す
    }
};

int main()
{
    X x;

    std::thread t1([&] { x.add_value(); });
    std::thread t2([&] { x.add_value(); });

    t1.join();
    t2.join();

    std::cout << x.get() << std::endl;
}
