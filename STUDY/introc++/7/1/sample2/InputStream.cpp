#include "InputStream.h"
#include <iostream>
using namespace std;

double InputStream::Get() const {
	return m_n;
}

bool InputStream::Set(){
	cin >> m_n;
	return m_n >= 0;
}
