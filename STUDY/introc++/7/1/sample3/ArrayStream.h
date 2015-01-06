#ifndef ARRAYSTREAM_H_
#define ARRAYSTREAM_H_

class ArrayStream {
	public:
		ArrayStream(const double* array);
		double Get() const;
		bool Set();

	private:
		const double* m_array;
		int m_i;
		double m_n;
};

#endif
