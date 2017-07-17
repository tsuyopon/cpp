// std::threadと合わせてみたサンプル
// スコープが終了したらunique_lockがunlockedされる。
//
// g++ -std=c++11 -lpthread sample.cc
#include <iostream>
#include <thread>
#include <exception>
#include <mutex>
#include <vector>
#include <ctime>
using namespace std;
std::timed_mutex m;
std::vector<time_t> v;
 
void
do_worker1 () {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::unique_lock<std::timed_mutex> ul(m, std::chrono::milliseconds(3)); // wait upt to 3ms
        if (ul) { // If I got the lock, access data.
                v.push_back(time(NULL));
        }
        // mutex unlocked !
}
 
int
main (int argc, char *argv[]) {
        try {
                std::thread t1(do_worker1);
                std::thread t2(do_worker1);
                t1.join();
                t2.join();
                for(auto t:v) {
                        cout << t << endl;
                }
        } catch (std::exception &ex) {
                std::cerr << ex.what() << std::endl;
        }
        return (0);
}
