#include "Stream.h"
#include <iostream>
using namespace std;

double Stream::Get() const {
	return m_n;
}

// constroctor
Stream::Stream(){
	cout << "Stream constructor" << endl;
	m_n = -1;
}

Stream::~Stream(){
	cout << "Stream destructor" << endl;
}
