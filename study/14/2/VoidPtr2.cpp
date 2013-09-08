#include<iostream>
#include<cstdio>

using namespace std;

// 16進数を出力する関数
// この時、データのアドレスをvoid型ポインタで受け付けるようにすれば、どんなデータ型であってもキャストの必要がありません。
void Dump(const void* vp, size_t size){
	static const int WIDTH = 16;
	const char* p = static_cast<const char*>(vp);

	for(size_t i = 0; i < size; i++){
		if(i % WIDTH == 0 && i != 0 ){
			cout << endl;
		}
		printf("%02X ", p[i]);
	}
	cout << endl;
}

int main(){
	int n = 0x12345678;
	const char str[] = "Hello!";

	Dump(&n, sizeof n);
	Dump(str, sizeof str);
}
