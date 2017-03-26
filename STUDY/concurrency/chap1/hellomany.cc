#include<iostream>
#include<thread>
#include<algorithm> // for_each

int main(){
	std::vector<std::thread> workers;
	for(int i=0; i<10; i++){
		workers.push_back(std::thread([i]()
				{
					std::cout << "From thread" << i << std::endl;
				}));
	}
	std::cout << "From main\n";
	std::for_each(workers.begin(), workers.end(), [](std::thread &th)
			{
				th.join();
			});
	return 0;
}
