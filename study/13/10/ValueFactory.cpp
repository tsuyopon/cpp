#include "ValueFactory.h"

Value* ValueFactory::New(int n) const {
	return new Value(n);
}
