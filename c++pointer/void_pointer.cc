#include<stdio.h>

// 関数の中に確保するとローカル変数扱いでメモリ確保・解放が必要なので、大局変数として定義する
static int array_[3][5] = {
		{ 1, 2, 3,  4,  5, },
		{ 2, 4, 6,  8, 10, },
		{ 3, 6, 9, 12, 15, },
};

// voidのアドレスに値を設定する関数
//    引数のvoid**はvoid*のアドレスを受け取ることを意味しているので、関数の型に応じて設定する
void insertVoidAddress(void** ret){

	printf("In insertVoidAddress. ret=%p\n", ret);

	// ret(void**)アドレスの値である*ret(void*)に対して値を設定する。設定される値はvoid*なのでアドレスになるはずである。
	*ret = reinterpret_cast<void*>(&array_);

	printf("In insertVoidAddress. ret=%p\n", ret);

}

/// insertVoidAddressは次の関数のようにも記述できる。
//void insertVoidAddress2(void* ret){
//
//	printf("In insertVoidAddress. ret=%p\n", ret);
//
//	ret = reinterpret_cast<void*>(&array_);
//
//	printf("In insertVoidAddress. ret=%p\n", ret);
//
//}

int main(){

	void *voidaddr_without_init;
	void *voidaddr_with_init = NULL;

	printf("In main: global variable &array_=%p\n", &array_);

	printf("\n================== voidaddr_without_init ==================\n");
	printf("In main: voidaddr_without_init=%p\n",  voidaddr_without_init);   // 初期化されていないvoidaddr_without_initの値を表示
	printf("In main: &voidaddr_without_init=%p\n", &voidaddr_without_init);  // voidaddr_without_initのアドレスの表示
	insertVoidAddress(&voidaddr_without_init);
	printf("In main: voidaddr_without_init=%p\n",  voidaddr_without_init);   // 初期化されていないvoidaddr_without_initの値を表示
	printf("In main: &voidaddr_without_init=%p\n", &voidaddr_without_init);  // voidaddr_without_initのアドレスの表示


	// 参考までに多次元配列に含まれる特定の値を出力する
	// multi dimention pointer cast
	//   See: https://stackoverflow.com/questions/11869056/how-to-cast-simple-pointer-to-a-multidimensional-array-of-fixed-size
	printf("array_[2][4]=%d\n", array_[2][4]);
	printf("(reinterpret_cast<int (*)[5]>(voidaddr_without_init))[2][4]=%d\n", (reinterpret_cast<int (*)[5]>(voidaddr_without_init))[2][4]);   // cast時に (*)[3]ではなく(*)[5]であることに注意

	// 以下の２つのアドレスは同一である
	printf("array_[2]=%p\n", &array_[2]);
	printf("&(reinterpret_cast<int (*)[5]>(voidaddr_without_init))[2]=%p\n", &(reinterpret_cast<int (*)[5]>(voidaddr_without_init))[2]);


	printf("\n================== voidaddr_with_init ==================\n");
	printf("In main: voidaddr_with_init=%p\n",     voidaddr_with_init);      // 初期化されたvoidaddr_with_initの値を表示
	printf("In main: &voidaddr_with_init=%p\n",    &voidaddr_with_init);     // voidaddr_with_initのアドレスの表示
	insertVoidAddress(&voidaddr_with_init);
	printf("In main: voidaddr_with_init=%p\n",     voidaddr_with_init);      // 初期化されたvoidaddr_with_initの値を表示
	printf("In main: &voidaddr_with_init=%p\n",    &voidaddr_with_init);     // voidaddr_with_initのアドレスの表示


}
