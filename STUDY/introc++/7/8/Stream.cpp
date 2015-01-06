#include "Stream.h"
#include <iostream>
using namespace std;

double Stream::Get() const {
	return m_n;
}

// constroctor
Stream::Stream(double n) : var(n*5){
	cout << "Stream constructor. arg = " << n << endl;
	cout << "Stream constructor. var = " << var << endl;
	m_n = n;
}

Stream::~Stream(){
	cout << "Stream destructor" << endl;
}
