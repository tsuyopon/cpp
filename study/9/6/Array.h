#ifndef ARRAY_H_
#define ARRAY_H_

#include <iostream>
#include <algorithm>
#include <cstdlib>

template <typename TYPE> class Array
{
	public:
		Array(int size);
		Array(const Array& other);
		void operator=(const Array& other);
		virtual ~Array();                    // See http://www33.ocn.ne.jp/~loreley/FSB/cpp02.html

	public:
		TYPE Get(int i) const;
		void Set(int i, TYPE value);

	public:
		int Size() const;

	private:
		void CheckIndex(int i) const;

	private:
		TYPE* m_array;
		int m_size;
};

	template <typename TYPE> Array<TYPE>::Array(int size){
		m_array = new TYPE[size];
		m_size = size;
	}

	template <typename TYPE> Array<TYPE>::Array(const Array& other){
		m_size = other.m_size;
		m_array = new TYPE[m_size];
		std::copy(other.m_array, other.m_array + m_size, m_array);
	}

	template <typename TYPE> void Array<TYPE>::operator=(const Array& other){
		TYPE* array = new TYPE[other.m_size];
		delete[] m_array;
		m_array = array;
		m_size = other.m_size;
		std::copy(other.m_array, other.m_array + m_size, m_array);
	}

	template <typename TYPE> Array<TYPE>::~Array(){
		delete[] m_array;
	}

	template <typename TYPE> TYPE Array<TYPE>::Get(int i) const{
		CheckIndex(i);
		return m_array[i];
	}

	template <typename TYPE> void Array<TYPE>::Set(int i, TYPE value){
		CheckIndex(i);
		m_array[i] = value;
	}

	template <typename TYPE> int Array<TYPE>::Size() const{
		return m_size;
	}

	template <typename TYPE> void Array<TYPE>::CheckIndex(int i) const{
		if( 0 <= i && i < m_size ){
			// Index is normal
		} else {
			std::cerr << "Index Invalid!" << std::endl
					<< "value: " << i << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

#endif // #ifndef ARRAY_H_

