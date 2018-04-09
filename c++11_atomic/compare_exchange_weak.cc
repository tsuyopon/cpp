// g++ -std=c++11 -pthread compare_exchange_weak.cc
//
// 説明: このプログラムではincrementとdecrementのスレッドをそれぞれ10万回実行してカウンタの値を表示するプログラムです。
//
// 一般的にはmutexによる排他制御はかなり高いコストなので、排他したい期間が短く、しかもさほど競合しないのであれば、
// std::atomic<T>のメンバー関数であるcompare_exchange_weakをループ中で用いることにより処理を実現できます。
// これを利用することで「書く前に現在値を読み、以前と変わりないなら変更する。変わってたら(途中で誰かが変更したとみなして)書くのをあきらめる」といったことを実現できます。
// このプログラムではincrementとdecrementを双方10万回実行して結果が0になっているかどうかを確認します。
// 結構競合が発生しそうなプログラムですが、自分が試した限り全て0が出力されました。
//
// See: https://qiita.com/episteme/items/9e6e17512ecadb2ccb40
#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> value;

/* bool atomic<T>::compare_exchange_weak(T& expected, T desired)
 * 現在の値が expected に等しければ desired を書いて true を返す
 * さもなくば expected を現在の値に書き換えて false を返す
 */
void increment(int n) {
    for (int i = 0; i < n; ++i) {
        int expected = value.load();
        int desired;
        do {
            desired = expected + 1;
        } while ( !value.compare_exchange_weak(expected, desired));
    }
}

void decrement(int n) {
    for (int i = 0; i < n; ++i) {
        int expected = value.load();
        int desired;
        do {
            desired = expected - 1;
        } while (!value.compare_exchange_weak(expected, desired));
    }
}

int main() {
    const int N = 10000000;
    thread th0(&increment, N);
    thread th1(&decrement, N);
    th0.join(); th1.join();
    cout << value << endl;
}
