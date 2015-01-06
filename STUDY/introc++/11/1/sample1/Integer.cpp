#include "Integer.h"
#include <iostream>
using namespace std;

Integer::Integer(int num){
	m_value = num;
}

void Integer::Show(){
	cout << m_value << endl;
}
