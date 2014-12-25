#include<iostream>
#include<cstdio>    /* vprintf */
#include<cstdarg>   /* va_list, va_start, va_end */

using namespace std;

void PrintF(const char* format, ...){
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

int main(){
	PrintF("Hello %s!\n Point=%d. Name=%s. age=%d\n", "world", 95, "Azarashi", 32);
}
