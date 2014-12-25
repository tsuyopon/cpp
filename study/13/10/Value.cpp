#include "Value.h"

int Value::Get() const{
	return m_n;
}

Value::Value(int n) : m_n(n) {
}
