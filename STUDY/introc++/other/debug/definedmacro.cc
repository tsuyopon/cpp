/*
 * http://d.hatena.ne.jp/satosystems/20120810/1344573313
 *
 * http://itog.seesaa.net/article/29163292.html
 *
 */
#include <iostream>
#include <cstdio>
#include <cstdarg>
using namespace std;

#ifndef DEBUG_PRINT

#define DEBUG1(fmt, ...) printf("%s(%d):" fmt, __func__, __LINE__, __VA_ARGS__)
#define DEBUG2(arg) do{ printf("%s(%d):", __func__, __LINE__), printf arg; } while(0)

#else    // #ifndef DEBUG_PRINT
#define DEBUG1(fmt, ...)
#define DEBUG2(arg)
#endif   // #ifndef DEBUG_PRINT


int DEBUG3(const char *fmt, ...){
	int rc;
	va_list va;
	va_start(va, fmt);
	rc = vprintf(fmt, va);
	va_end(va);
	return rc;
}

void myFunc(){
	cout << "__func__: " << __func__ << endl;
	cout << "__FILE__: " << __FILE__ << endl;
	cout << "__LINE__: " << __LINE__ << endl;
}

int main(int argc, char **argv){
	myFunc();
	DEBUG1("debug1:%s\n", "arg");
	DEBUG2( ("debug2:%s\n", "arg") );
	DEBUG3("debug1:%s\n", "arg");
	return true;
}
