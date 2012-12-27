#ifndef ARRAY_H_
#define ARRAY_H_

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>

template <typename TYPE> class Array {
	public:
		void Error();
		const int m_size();
};

template <typename TYPE> void Array<TYPE>::Error(){
	m_size = 0;
}

#endif   // #ifndef ARRAY_H_
