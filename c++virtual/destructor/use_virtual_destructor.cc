/*
 * Baseデストラクタにvirtualを付与しない場合
 */
#include <stdio.h>

class Base {
	public:
		Base(){}
		virtual ~Base(){}    // ここにvirtualを追加しない
};

class Sub : public Base {
	public:
		Sub(){ printf("open\n"); }
		~Sub(){ printf("close\n"); }
};

int main(){
	Sub* sub = new Sub();
	delete sub;

	printf("\n");

	Base* base = new Sub();
	delete base;

	return 0;
}

