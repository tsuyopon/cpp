// The full class definition for a thread-safe queue using condition variables
#include <iostream>
#include <memory>
#include <condition_variable>
#include <stack>
#include <mutex>
#include <exception>
#include <queue>

template<typename T>
class threadsafe_queue
{
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;

public:
    threadsafe_queue()
    {}

    void push(T new_value) {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(std::move(new_value));
        data_cond.notify_one();                  // 1. 状態変数を通知する
    }

    // empty()をcallし続けるのではなく、
    // 状態変数の更新を検知するまでwaitingする
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        value=std::move(data_queue.front());
        data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mut);
        // data_cond.waitは、キューに1つでも要素を持たないとreturnされない。
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        std::shared_ptr<T> res(
            std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return false;
        value=std::move(data_queue.front());
        data_queue.pop();
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(
            std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};


int main(){
    threadsafe_queue<int> tq; 
    std::shared_ptr<int> pop;
    int value;
    int& pop2 = value;
    tq.push(5);
    tq.push(6);
    tq.push(7);
    tq.push(8);
    pop = tq.try_pop();
    std::cout << "pop value = " << *pop << std::endl;
    pop = tq.try_pop();
    std::cout << "pop value = " << *pop << std::endl;
    tq.empty();
    pop = tq.try_pop();
    std::cout << "pop value = " << *pop << std::endl;
    return 0;
}
