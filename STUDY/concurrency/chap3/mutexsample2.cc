// 参考
// http://minus9d.hatenablog.com/entry/20130914/1379168684
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// グローバル領域にmtxを用意
std::mutex mtx;

void worker() {

    // lock_guardを使うと、スコープの終わりでlock()変数が破棄されるのにともなって、自動的にロックも解除される
    std::lock_guard<std::mutex> lock(mtx);

    // 資源を使った処理を行う
    std::cout << "thread id: " << std::this_thread::get_id() << std::endl;

}

int main() {

    // スレッドを100作る
    std::vector<std::thread> ths(100);
    for (auto& th : ths) {
        th = std::thread(worker);
    }

    // すべてのスレッドが終わるのを待つ
    for (auto& th : ths) {
        th.join();
    }

    return 0;
}
