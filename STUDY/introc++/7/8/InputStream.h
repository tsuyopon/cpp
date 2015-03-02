#ifndef INPUTSTREAM_H_
#define INPUTSTREAM_H_

#include "Stream.h"

class InputStream : public Stream {
	public:
		InputStream(double n);     // 基底クラスの呼び出しは実体には必要ですが、定義には不要です。
		~InputStream();
};

#endif
