#include<iostream>
#include<thread>
#include<unistd.h>

int globalvar=1;

void hello(){
	int hellovar=100;
	std::cout << "Hello World" << hellovar;
}

int main() {
	int mainvar=10;
	printf("%p, %d", hello, mainvar);
	std::thread t(hello);
	sleep(60);
	t.join();
}
