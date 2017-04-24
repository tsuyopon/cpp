// 関数ポインタをboost::functionに格納するパターン
#include <iostream>
#include <boost/function.hpp>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    boost::function<int(int, int)> f = add; // 関数ポインタをboost::functionに格納

    const int result = f(2, 3); // 関数呼び出し
    std::cout << result << std::endl;
}
