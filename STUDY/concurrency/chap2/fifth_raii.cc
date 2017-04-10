// RAII(Resource Aquisition Is Initialization
//   https://ja.wikipedia.org/wiki/RAII
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

class thread_guard {
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_): t(t_) {}

    ~thread_guard()
    {
        if(t.joinable()) {  // threadオブジェクトがスレッドと関連付けられているか否か取得する
            t.join();
        }
    }

    // https://cpprefjp.github.io/lang/cpp11/defaulted_and_deleted_functions.html
    // コピーを禁止する(これはコンパイラによって自動割り当てされるのでこれを回避する)
    thread_guard(thread_guard const&)=delete;             // コピーコンストラクタ
    thread_guard& operator=(thread_guard const&)=delete;  // コピーオペレータの禁止
};

void f() {
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    //do_something_in_current_thread();
    // ここに到達するとローカルオブジェクトが破壊される。
    //   まずg変数がまず破壊される。
    //   thread_guardクラスの中にあるデストラクタ~thread_guard()のt.join()が実行される。
    //   t.joinableでjoinできるかどうかを調べる必要がある
}

int main(){
	f();
}
