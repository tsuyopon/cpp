// adopt_lock_t型とその値adopt_lockは、ロック済みミューテックスを受け取るためのタグである。

#include <iostream>
#include <mutex>

int main()
{
  std::mutex mtx;
  {
    mtx.lock(); // ロックを取得する

    std::unique_lock<std::mutex> lk(mtx, std::adopt_lock); // ロック済みミューテックスの管理を移譲する

	// ロックを取得しているかどうかを確認する(1なら取得済み)
	std::cout << lk.owns_lock() << std::endl;

	// 以下の1行をコメントアウトすると次の様なエラーが出力される
	// エラーメッセージ: libc++abi.dylib: terminating with uncaught exception of type std::__1::system_error: unique_lock::lock: already locked: Resource deadlock avoided
	//lk.lock();

  } // unique_lockの破棄時にunlock()される
}

