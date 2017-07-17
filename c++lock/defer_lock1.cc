// adopt_lock1.cc とこのファイルの違いをよく比較すること
// defer_lockでは
//    try_lock
//    try_lock_for
//    try_lock_until
// を好きに呼び出せます。

#include <iostream>
#include <mutex>

int main()
{
  std::mutex mtx;
  {
    mtx.lock(); // ロックを取得する

    std::unique_lock<std::mutex> lk(mtx, std::defer_lock); // ロック済みミューテックスの管理を移譲する

	// ロックを取得しているかどうかを確認する。defer_lockだと0となるはず。(iadopt_lockだと1になる)
	std::cout << lk.owns_lock() << std::endl;

	// 遅延ロックなので後からでもロックが取れる。(なお、adopt_lockだと、lk.lock()を記述するとエラーになる。)
	lk.lock();

  } // unique_lockの破棄時にunlock()される
}

