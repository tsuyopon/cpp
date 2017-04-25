// boost::functionを利用した色々な操作について
// $ g++ test3.cc -I/usr/include/boost141/ -std=c++11
// 参考:
//    http://d.hatena.ne.jp/osyo-manga/20100930/1285800075
#include <iostream>
#include <assert.h>

#include <boost/function.hpp>
#include <boost/functional.hpp>
#include <boost/bind.hpp>

int
division(int n, int m){
    return n / m;
}

template<typename T>
bool
is_equal(const T& lhs, const T& rhs){
    return lhs == rhs;
}

struct game{
    void even1(int n){
        std::cout << "game::even1("<< n << ")" << std::endl;
    }
    void even2(int n){
        std::cout << "game::even2("<< n << ")" << std::endl;
    }
};


int
main(){
    // 関数の保持
    boost::function<int(int, int)>    division_func = &division;
    assert(division_func(10, 2) == 5);

    // ラムダも保持できる
    boost::function<bool(int)> is_even = [](int n)->bool{ return n % 2 == 0; };
    assert(is_even(4) == true);

    // あらかじめ、関数に渡す引数を設定しておく事も出来る
    boost::function<bool()>    three_is_even = boost::bind(is_even, 3);
    assert(three_is_even() == false);    // is_even(3)

    // template の場合は、渡す時に template 型も設定する
    boost::function<bool(int, int)>    is_equal_int(&is_equal<int>);
    assert(is_equal_int(10, 10) == true);

    // 非 static メソッドを保持する場合は、第一引数にクラスのポインタを設定する
    boost::function<void(game*, int)>    any_game_even(&game::even1);
    game    g;
    any_game_even(&g, 10);    // g.even1(10);

    // あらかじめクラスのポインタを渡しておくと呼び出し時に楽
    boost::function<void(int)>    any_game_even2 = boost::bind(&game::even2, &g, ::_1);
    any_game_even2(10);
    
    return 0;
}
