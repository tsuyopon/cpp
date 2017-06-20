// boost::bindで１つの引数を常に固定にする場合
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

// <int(int, int)>ではなく<int(int)>となっている。
typedef boost::function<int(int)> TestFunction;

int Sum(int a, int b)
{
	return a + b;
}

int main()
{
	TestFunction Tf;
	int Result = 0;

	// _1, _2だったのが4, _1となっている。
	// これは第一引数を4で固定したこととなる。
	Tf = boost::bind(&Sum, 4, _1);
	// 引数の数が１つになっている。
	Result = Tf(5);
	
	std::cout << "Result: " << Result << std::endl;
	return 0;
}
