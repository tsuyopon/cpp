#ifndef ARRAYSTREAM_H_
#define ARRAYSTREAM_H_

#include "Stream.h"

class ArrayStream : public Stream {
	public:
		ArrayStream(const double* array);
		bool Set();

	private:
		const double* m_array;
		int m_i;
};

#endif
