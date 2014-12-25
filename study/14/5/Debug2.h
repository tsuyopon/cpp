#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef NDEBUG      // リリース

#define ASSERT(b)

#else              // デバッグ

#define ASSERT(b) Debug::Assert((b), __FILE__, __LINE__, __DATE__, __TIME__)
namespace Debug {
	void Assert(bool b, const char* file, int line, const char* date, const char*time);
}

#endif            // #ifndef NDEBUG

#endif            // #ifndef DEBUG_H_
