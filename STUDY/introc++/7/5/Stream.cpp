#include "Stream.h"
#include <iostream>
using namespace std;

double Stream::Get() const {
	return m_n;
}

bool Stream::Set() {
	SetBase();
	return m_n >= 0;
}

void Stream::SetBase(){
	cout << "Stream::SetBase" << endl;
	m_n = -1;
}
