/*
 *  テンプレート関数について
 *   ※ このテンプレート関数は、複数の型の代入が行われる場合などに複数個のオーバーライド関数を記述しなくても良いというメリットがあります。
 */
#include<iostream>
using namespace std;


template <class X> void println(X out){                        // float, double等なんでも受け付けます。但し、int型だけは下記メソッドでint型がオーバーロードされているのでそちらが優先されます
	cout << "Template Class: " << out << endl;
}

void println(int out){                                         // println()関数の引数がint型であった場合にこのメソッドが呼び出されます(テンプレートのオーバーライド)
	cout << "Int: " << out << endl;
}

template <class X> X addData(X arg1, X arg2){                  // 引数の型は共にXと一致しているので、同じ型で無ければならない
	return arg1 + arg2;
}

template <class X, class Y> void  printData(X arg1, Y arg2){   // 引数の型はXとYと異なるので、異なる型を代入しても問題ありません
	cout << "arg1=" << arg1 << "\targ2=" << arg2 << endl;
}

int main()
{
	// println()
	println(10);
	println("helloworld");
	println(1.234);

	// addData()
	cout << addData(100, 200) << endl;
//	cout << addData(1.23, 200) << endl;                        // １つめの引数と２つめの引数が異なるので、この行があるとコンパイルできない。

	// printData()
	printData("hello", "world");
	printData(1.234, 100);

	return 0;
}
