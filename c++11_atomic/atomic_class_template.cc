// スピンロックの実装

// Boost Atomic Library - Usage Example
// http://www.boost.org/doc/libs/1_53_0/doc/html/atomic/usage_examples.html#boost_atomic.usage_examples.example_spinlock

#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>

class spinlock {
private:
  enum LockState {Locked, Unlocked};
  std::atomic<LockState> state_;

public:
  spinlock() : state_(Unlocked) {}

  void lock() {
    // 現在の状態をLockedと入れ替える
    while (state_.exchange(Locked, std::memory_order_acquire) == Locked) {
      // busy-wait...アンロックされるまで待機
    }
  }

  void unlock() {
    // 値をUnlockedに更新
    state_.store(Unlocked, std::memory_order_release);
  }
};

namespace {
  spinlock lock;
}

template <class T>
void print(const T& x)
{
  std::lock_guard<spinlock> lk(lock);
  std::cout << x << std::endl;
}

void func1() {
  print(1);
}

void func2() {
  print(2);
}

int main() {
  std::thread t1(func1);
  std::thread t2(func2);

  t1.join();
  t2.join();
}
