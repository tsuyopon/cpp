#include<iostream>
#include<atomic>

int main(){
	std::atomic<int> num(100);
	num.store(101, std::memory_order_release);
	std::cout << num.load() << std::endl;

	int old;
	old = num.fetch_add(1);
	std::cout << "old value:   " << old << std::endl;
	std::cout << "after fetch_add(1):   " << num.load() << std::endl;

	num += 10;
	std::cout << "after num += 10:     " << num.load() << std::endl;

	num -= 10;
	std::cout << "after num -= 10:     " << num.load() << std::endl;

	++num;
	std::cout << "after ++num:     " << num.load() << std::endl;

}
