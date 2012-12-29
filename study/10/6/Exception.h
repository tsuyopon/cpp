#ifndef EXCEPTION_H_
#define EXCEPTION_H_

class Exception {
	public:
		virtual ~Exception();   // destructer

	public:
		virtual const char* What() const = 0;
};

#endif   // #ifndef EXCEPTION_H_
