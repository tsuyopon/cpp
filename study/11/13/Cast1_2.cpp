#include <cstdio>
using namespace std;

int main(){
	signed char a = -1;
	int b;

	b = a;
	printf("%08X (%d)\n", b, b);

	// 静的な普通の型変換を行う場合、static_castを用いる
	b = static_cast<unsigned char>(a);
	printf("%08X (%d)\n", b, b);
}
