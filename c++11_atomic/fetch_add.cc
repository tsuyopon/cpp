// fetch_addを使うことでその戻り値はstd::atomic<T*>オブジェクトの参照というよりもむしろプレインなT*の型を取得できます。
#include<atomic>
#include<cassert>
#include<iostream>

class Foo{
	int test;
};

int main(){

	Foo some_array[5];
	std::atomic<Foo*> p(some_array);    // std::atomic<T*>が宣言
	Foo* x=p.fetch_add(2);              // xにはstd::atomic<T*>オブジェクトの参照というよりもむしろプレインなT*の型を返します。
	assert(x==some_array);              // 戻り値xはFoo*に対する最初のポインタ
	assert(p.load()==&some_array[2]);   // p.load()だと先ほどfetch_add(2)したので、3番目(3-1=2)へのFoo*へのポインタを指す

	x=(p-=1);                           // 3番目のエントリから1つ戻る
	assert(x==&some_array[1]);          // 2番目のエントリオブジェクトをさす
	assert(p.load()==&some_array[1]);
}
