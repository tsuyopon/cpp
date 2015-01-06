#include <cstdio>
using namespace std;

int main(){
	signed char a = -1;
	int b;

	b = a;
	printf("%08X (%d)\n", b, b);

	b = (unsigned char)a;
	printf("%08X (%d)\n", b, b);
}
