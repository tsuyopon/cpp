#ifndef INPUTSTREAM_H_
#define INPUTSTREAM_H_

#include "Stream.h"

class InputStream : public Stream {
//	public:
//		double m_n;             // 派生クラスでもm_nを定義すると結果がかわってくる
	protected:
		virtual void SetBase();
};

#endif
