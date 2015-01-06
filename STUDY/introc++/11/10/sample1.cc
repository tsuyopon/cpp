#include <iostream>
#include "Fraction.h"
using namespace std;

int main(){

	// double()のキャストオーバーロード
	double l = Fraction(100, 5);
	cout << "Fraction(100, 5) => " << l << endl;

	double m = Fraction(10, 2);
	cout << "Fraction(10, 2) => " << m << endl;

	// 単項演算子- のオーバーロード
	double n = - Fraction(6, 2);
	cout << "-Fraction(6, 2) => " << n << endl;

	// 単項演算子* のオーバーロード
	double o = Fraction(10, 5) * Fraction(6, 2);
	cout << "Fraction(10, 5) * Fraction(6, 2) => " << o << endl;

	// 2項演算子*= のオーバーロード
	int p = (Fraction(6,2) *= Fraction(3,1));
	cout << "Fraction(6,2) *= Fraction(3,1) => " << p << endl;

	// 前置インクリメント++のオーバーロード
	double q = ++Fraction(6,2);
	cout << "++Fraction(6,2) => " << q << endl;

	// 後置インクリメント++のオーバーロード
	double r = Fraction(6,2)++;
	cout << "Fraction(6,2)++ => " << r << endl;
}
