#include<iostream>
#include<list>
#include<vector>
#include<map>

int main(){

	// 配列(&ありの場合)
	int ar[] = {3, 1, 4, 1, 5, 9};
	for(int &x : ar) {               // ここに&が付与されていると参照となるので、このforのscopeを抜けてもarの変更が維持される
		if( x == 1 )
			x = 123;
		std::cout << x << std::endl;
	}
	std::cout << std::endl;

	// 配列(&なしの場合)
	for(int x : ar) {                // &が付与されていないので、forを抜けたら値の変更は維持されない
		if( x == 5 )
			x = 567;
		std::cout << x << std::endl;
	}
	std::cout << std::endl;

	// 配列(constの場合)
	for(const int x : ar) {         // constが付与されていないので、xの値は変更できない
		// xの値を変更するとコンパイルエラーとなる
		std::cout << x << std::endl;
	}
	std::cout << std::endl;

	// 配列(&&の場合) (&&はreference collapsingで検索すると出てきます)
	// see http://d.hatena.ne.jp/prettysoft/20101113/1418577983
	for (auto&& x : ar) // access by reference, the type of i is int&
		std::cout << x << ' ';
	std::cout << std::endl;

	// 直接記述
	for (int n : {0, 1, 2, 3, 4, 5}) // the initializer may be a braced-init-list
		std::cout << n << ' ';
	std::cout << std::endl;

	// list
	std::list<double> lst{1.1, 1.2, 1.3, 1.4, 1.5};
	for(auto x : lst) {
		std::cout << x << std::endl;
	}
	std::cout << std::endl;

	// vector
	std::vector<int> vec = {55, 66, 77};
	for( auto x : vec ){
		std::cout << x << std::endl;
	}
	std::cout << std::endl;


	// map
	std::map<std::string, int> mp {{"aaa", 10}, {"bbb", 20}, {"ccc", 30}};
	for(const auto x : mp) {       
		std::cout << x.first << " " << x.second << "\n";
	}
	std::cout << std::endl;


	// 2次元配列の作成
	int a[4][3] = { {1, 2, 3},
					{4, 5, 6},
					{7, 8, 9},
					{10, 11, 12} };
	for (auto & row : a){
		for (auto & i : row){
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;


//	for (auto i : v) // access by value, the type of i is int
//		std::cout << i << ' ';
//	std::cout << std::endl;
//

}
