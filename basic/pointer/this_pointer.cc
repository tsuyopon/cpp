/*
 *  thisポインタの使用方法について
 */
#include<iostream>
using namespace std;

class MyClass {
	public:
		char *str;
		MyClass(char *str){
			this->str = str;     // thisポインタとは、メンバー関数が実行されたときのポインタ(例 obj[0], obj[1], obj[2]等のポインタを指しています)。メンバー関数が実行された時点からthisポインタは存在します。
		}
		void func(){
			cout << this->str << endl;
		}
};

int main()
{
	MyClass obj[3] = {
		(char*)"test1",
		(char*)"test2",
		(char*)"test3",
	};

	for(int i=0; i < 3; i++){
		obj[i].func();           // thisポインタがどのように扱われているか確認してください
	}
	return 0;
}
