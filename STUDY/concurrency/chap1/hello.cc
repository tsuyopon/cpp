#include<iostream>
#include<thread>
#include<unistd.h>

void hello(){
	std::cout << "Hello World\n";
}

int main() {
	std::thread t(hello);
	t.join();
}
