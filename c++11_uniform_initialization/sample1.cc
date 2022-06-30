/*
 * 一様初期化(uniform initialization)は、コンストラクタの呼び出しを、リスト初期化と合わせて波括弧{}で記述する構文です。
 * 一様初期化は統一初期化記法などとも呼ばれることがあります。
 *
 * cf. https://cpprefjp.github.io/lang/cpp11/uniform_initialization.html
 */
struct X {
  X(int) {}
};

int main()
{
  // 従来のコンストラクタ呼び出し
  // 従来の呼び出しだと関数宣言と勘違いして解釈されることもありました。
  X x1(0);
  X x2 = 0;

  // C++11から登場した初期化構文によるコンストラクタ呼び出し
  X x3 {0};
  X x4 = {0};
}
