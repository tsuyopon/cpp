#include "Fraction.h"
#include <iostream>
using namespace std;

// constructor
Fraction::Fraction(double numer, double denom) : m_numer(numer), m_denom(denom){
}

// 分子の取得
double Fraction::GetNumer() const {
	return m_numer;
}

// 分母の取得
double Fraction::GetDenom() const {
	return m_denom;
}

//////////////////////////////////////////////////
// キャスト演算子のオーバーロード定義
//////////////////////////////////////////////////
// 以下はdouble()型のオーバーロード定義です。
Fraction::operator double() const { 
	cout << "##### double() overload called" << endl;
	return m_numer / m_denom;
}

// 単項演算子"*"に対するオーバーロード定義
Fraction Fraction::operator*(const Fraction& rop) {
	cout << "##### * overload called" << endl;
	m_numer *= rop.m_numer;
	m_denom *= rop.m_denom;
	return Fraction(m_numer, m_denom);
}

// 単項演算子"-"に対するオーバーロード定義
Fraction Fraction::operator-() const {
	cout << "##### - overload called" << endl;
	return Fraction(-m_numer, m_denom);
}

// ２項演算子"*="のオーバーロード定義
Fraction& Fraction::operator*=(const Fraction& rop){
	cout << "##### *= overload called" << endl;
	m_numer *= rop.m_numer;
	m_denom *= rop.m_denom;

	// ここで返すべき値は、「このメンバ関数を呼ぶために使用したオブジェクトに対する参照です。これは「*this」で表現できます。[j
	// thisは、メンバー関数を呼ぶのに使ったオブジェクトのアドレスを持つポインタです。 *thisによりメンバ関数を呼ぶのに使ったオブジェクトを指し示します。
	return *this;
}

// 前置インクリメント"++"のオーバーロード定義(例: ++a)
Fraction& Fraction::operator++(){
	cout << "##### before increment ++ overload called" << endl;
	m_numer += m_denom;
	return *this;
}

// 後置インクリメント"++"のオーバーロード定義(例: a++)
Fraction& Fraction::operator++(int){            // 後置インクリメントではint型のダミー引数が必要です。
	cout << "##### after increment ++ overload called" << endl;
	Fraction& ret = *this;
	m_numer += m_denom;
	return ret;
}

