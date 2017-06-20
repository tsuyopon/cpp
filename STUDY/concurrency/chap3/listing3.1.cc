//  std::list
#include<list>
#include<mutex>
#include<iostream>
#include<algorithm>
#include<thread>

int count;
std::list<int> some_list;
std::mutex some_mutex;

void increment(){
	count++;
}

void add_to_list(int new_value){
	std::cout << "add_to_list" << std::endl;
	std::lock_guard<std::mutex> guard(some_mutex);
	some_list.push_back(new_value);
}

bool list_contains(int value_to_find){
	std::cout << "list_contains" << std::endl;
	std::lock_guard<std::mutex> guard(some_mutex);
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

int main(){
    std::vector<std::thread> workers;
    for(int i=0; i<30000; i++){
        workers.push_back(std::thread([i]()
                {
                    //std::cout << "From thread" << i << std::endl;
                    increment();
                    add_to_list(i);
//					if(list_contains(i)){ std::cout << "true" << std::endl; } else { std::cout << "false" << std::endl;}
//                    std::cout << (int)list_contains(i) << std::endl;
                }));
    }
    std::cout << "From main\n";
    std::for_each(workers.begin(), workers.end(), [](std::thread &th)
            {
                th.join();
            });
    std::cout << "list size: " << some_list.size() << std::endl;
    std::cout << "count: " << count << std::endl;
    return 0;
}



