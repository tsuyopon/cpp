// char*に関するポインタを扱う簡単なサンプルプログラム

// 参照を使うのでC++にしています。
#include<stdio.h>

// ポインタを引数として引き渡す場合
void func1(char* data){
	printf("func1: data address of addr = 0x%08x\n",    &data);       // アドレスのアドレス
	printf("func1: data address = 0x%08x\n",    data);                // アドレス
	printf("func1: data value   = 0x%08x\n", *data);                  // h(=0x68)
	printf("func1: print data   = %s\n\n", data);                     // 「hogehoge」
}

// 引数に入ってくる値はコピーされた値となる。
// charなので1文字hogehogeの最初の1文字「h」しかコピーされない。
void func2(char data){
	printf("func2: data address = 0x%08x\n", &data);                  // アドレス
	printf("func2: data value   = 0x%08x\n",    data);                // h(=0x68)
	printf("func2: print data   = %s\n\n", &data);                    // 「h」のみ
}

// ポインタのポインタを引数として引き渡す場合
void func3(char** data){
	printf("func3: data address(address_of_address)  = 0x%08x\n",  data);          // 引数で引き渡されたアドレスのアドレス
	printf("func3: data value(address_of_address)    = 0x%08x\n", *data);          // アドレスのアドレスからアドレスへと変換
	printf("func3: data value of value (address_of_address) = %s\n", *data);       // 「hogehoge」
	printf("func3: data value of value (address_of_address) = %c\n\n", **data);    // 「h」
}

// アドレスを参照渡しとして受け取る (参照はC++ only)
void func4(char* &data){
	printf("func4: data address of addr = 0x%08x\n",    &data);       // アドレスのアドレス
	printf("func4: data address = 0x%08x\n",    data);                // アドレス
	printf("func4: data value   = 0x%08x\n", *data);                  // h(=0x68)
	printf("func4: print data   = %s\n\n", data);                     // 「hogehoge」
}

int main(){
	char* data = (char*)"hogehoge";
	printf("main: data address of addr  = 0x%08x\n",    &data);       // アドレスのアドレス
	printf("main: data address          = 0x%08x\n",    data);        // アドレス
	printf("main: data value            = 0x%08x\n\n", *data);        // h(=0x68)

	func1(data);
	func2(*data);
	func3(&data);
	func4(data);
}
