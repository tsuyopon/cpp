#ifndef VALUEFACTORY_H_
#define VALUEFACTORY_H_

class Value;

class ValueFactory {
	public:
		Value* New(int n) const;
};

#include "Value.h"

#endif  // #ifndef VALUEFACTORY_H_
