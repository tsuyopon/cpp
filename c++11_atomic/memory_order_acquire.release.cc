// SeeAlso: https://qiita.com/tetsu0121/items/cd28780bc30f3a1d3353
#include <iostream>
#include <atomic>
#include <thread>

int data;
std::atomic<bool> ready(false);

void f()
{
  while (!ready.load(std::memory_order_acquire)) {
  }

  // memory_order_acquireを指定することより、指定した箇所より下の箇所の実行順序を保証します。
  std::cout << data << std::endl;
}

int main()
{
  std::thread t(f);

  data = 765;
  // memory_order_releaseを指定することより、指定した箇所より上の箇所が値の書き込み前の実行順序を保証します。
  ready.store(true, std::memory_order_release);

  t.join();
}
