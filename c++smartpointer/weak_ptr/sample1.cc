// 参考: https://cpprefjp.github.io/reference/memory/weak_ptr.html
#include <memory>
#include <iostream>

int main()
{
  // weak_ptrオブジェクトwpは、
  // shared_ptrオブジェクトspを監視する
  std::shared_ptr<int> sp(new int(42));
  std::weak_ptr<int> wp = sp;

  // wpの監視対象であるspが、有効なリソースを保持している状態なら処理する。
  if (std::shared_ptr<int> r = wp.lock()) {
    std::cout << "get weak_ptr value : " << *r << std::endl;
  }

  sp.reset();

  // shared_ptrオブジェクトが無効になったことを検知する
  if (wp.expired()) {
    std::cout << "shared_ptr managed object deleted." << std::endl;
  }
}
