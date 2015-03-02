#ifndef STREAM_H_
#define STREAM_H_

class Stream {
	public:
		double Get() const;
		bool Set();
		double m_n;

	protected:
		virtual void SetBase() = 0;  // 純粋仮想関数です。宣言のみで、実際に定義されていないことに注意してください。
};

#endif
