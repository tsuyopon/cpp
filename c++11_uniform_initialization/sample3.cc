/*
 * 一様初期化(統一初期化法: Uniform Initialization)による様々な型の初期化
 */
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
	int x { 3 };
	int a[] { 0, 1, 2, 3 };
	struct S1 { int a, b; } s { 0, 1 };
	std::vector<int> v { 0, 1, 2, 3 };
	pair<int, double> p { 1, 2.3 };
	std::map<string, int> m {{"aaa", 10}, {"bbb", 20}, {"ccc", 30}};

}
