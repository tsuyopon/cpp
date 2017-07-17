# 概要
C++のLockについて整理する

- lock_guard
  - スコープが切れたら自動的にunlockして、ロック漏れを防ぐ
- unique_lock
  - シンプルなlock_guardと比較して次の４つの拡張機能を持つとのこと
    - コンストラクタでロックを取得せず、あとからロックを取得できる(defer_lock)
    - コンストラクタでのロック取得に、lock()ではなくtry_lock()を使用できる(try_to_lock)
    - ミューテックスの所有権を移動・交換(swap)・放棄(release)できる
    - 任意のタイミングで所有ミューテックスのロック操作を呼び出せる
- adopt_lock
  - ロック済みミューテックスの管理を移譲する
- defer_lock
  - すぐにlockのオーナーを取らずに、その後ロックを取得することができる。
- try_to_lock
  - ブロック無しでmutexのオーナーのオーナーを獲得しようとする


# 詳細
adopt_lock1.cc, defer_lock1.cc, try_to_lock1.cc の3つはvimdiffなどで比較してみると良い

# 参考URL
- スコープロックでの4つのロック方法
  - http://faithandbrave.hateblo.jp/entries/2012/09/05
