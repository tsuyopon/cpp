// boost::bindを用いた単純なサンプル
// http://arikalog.hateblo.jp/entry/2013/09/28/011734
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

typedef boost::function<int()> TestFunction;

int GetVal()
{
	return 10;
}

int main()
{
	TestFunction Tf;
	int Result = 0;

	// ここでboost::bindを使用しています。
	// ここは Tf = &GetVal; でも動作します。
	Tf = boost::bind(&GetVal);
	Result = Tf();
	
	std::cout << "Result: " << Result << std::endl;
	return 0;
}

