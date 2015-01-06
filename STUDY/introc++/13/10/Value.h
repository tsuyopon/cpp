#ifndef VALUE_H_
#define VALUE_H_

#include "ValueFactory.h"

class Value {
	friend Value* ValueFactory::New(int n) const;

	public:
		int Get() const;

	private:
		Value(int n);
		int m_n;
};

#endif  // #ifndef VALUE_H_
