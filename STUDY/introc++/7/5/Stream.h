#ifndef STREAM_H_
#define STREAM_H_

class Stream {
	public:
		double Get() const;
		bool Set();
		double m_n;

	protected:
		virtual void SetBase();  // virtual addded
};

#endif
