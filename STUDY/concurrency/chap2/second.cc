// トラップ
#include<iostream>
#include<thread>
#include<unistd.h> //sleep

struct func {
	int& i;
	func(int& i_):i(i_){}
	void operator()()
	{
		std::cout << "operator() start" << std::endl;
		for(unsigned j=0;j<10;++j)
		{
			do_something(i);                        // iは&iの参照として定義されているが、hogeが終了と同時に参照が破壊される
		}
	}
	void do_something(int i){
		std::cout << "do_something:" << i << std::endl;
	}
};

void hoge() {
	std::cout << "start" << std::endl;
	int some_local_state=0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	sleep(1);                           // このsleepを抜くとfunc側の構造体で定義される出力は表示されない
	my_thread.detach();                 // joinがないのでスレッドが完了するのをまたない。つまり、この後スレッドが実行され続ける(mainだから終わっちゃうけど)
	std::cout << "end" << std::endl;
}

int main(){
	hoge();
}
