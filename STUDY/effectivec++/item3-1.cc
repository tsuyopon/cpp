#include<iostream>

class Hoge{}
int main(){
	char greeting[] = "Hello";
	char *p = greeting;               // noconst
	const char* p = greeting;         // data: const
	char* const p = greeting;         // pointer: const
	const char* const p = greeting;   // pointer: const, data: const

	// 次の２つはconstの位置は異なっているが同じ
	const Hoge* hoge1;
	Hoge const* hoge2;
}
