#include <cstdio>
using namespace std;

int main(){

	int n = 0x12345678;

	// int* から const char*へのcastを行っています。
	// 1Byteが8bitの環境であれば、
	//    リトルエンディアンでは、"78 56 34 12"
	//    ビッグエンディアンでは、"12 34 56 78"
	// と出力されます。このように環境依存的な処理を意図的に行う場合にreinterpret_castを利用します。
	const char* p = reinterpret_cast<const char*>(&n);

	for(size_t i = 0; i < sizeof n; ++i){
		printf("%02X ", p[i]);
	}
	printf("<-> %08X\n", n);
}
