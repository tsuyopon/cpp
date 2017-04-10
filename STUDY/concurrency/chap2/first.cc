#include<iostream>
#include<thread>

class background_task
{
public:
	void do_something() const {
		std::cout << "do_something" << std::endl;
	}

	void do_something_else() const {
		std::cout << "do_something_else" << std::endl;
	}

    void operator()() const
    {
        do_something();
        do_something_else();
    }
};

int main(){
	background_task f;
	std::thread my_thread(f);
}

