// 関数オブジェクトをboost::functionに格納する
// test1.ccと全く同様の結果なので、関数ポインタでも関数オブジェクトでも大丈夫とおぼえておけば良い
#include <iostream>
#include <boost/function.hpp>

struct add {
    typedef int result_type;
    int operator()(int a, int b) const
    {
        return a + b;
    }
};

int main()
{
    boost::function<int(int, int)> f = add(); // 関数オブジェクトをboost::functionに格納

    const int result = f(2, 3); // 関数呼び出し
    std::cout << result << std::endl;
}
