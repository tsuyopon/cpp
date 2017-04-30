// lvalueに該当するのか、rvalueに該当するのかをチェックするプログラム
// lvalueはrvalueに変換できるが、その逆、rvalueをlvalueに変換することは出来ない。 

#include<iostream>

struct X{};

void func(X&){
    std::cout << "lvalue" << std::endl;
};

void func(X&&){
    std::cout << "rvalue" << std::endl;
};

X hoge(){
    return X();
}

int main(){
	X x;
	func(x);                          // lvalue
	func( X() );                      // rvalue
	func( hoge() );                   // rvalue
	func( static_cast<X&&>(x) );      // rvalue
//	func( static_cast<X&>(hoge()) );  // rvalue->lvalue  なので上の注釈の通り「rvalueをlvalueに変換することはできない」(コンパイルエラー)
}
