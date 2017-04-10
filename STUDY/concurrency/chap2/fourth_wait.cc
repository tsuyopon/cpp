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

void f() {
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread t(my_func);
    try
    {
    }
    catch(...) {
        t.join();
        throw;
    }
    t.join();
}

int main(){
	f();
}
