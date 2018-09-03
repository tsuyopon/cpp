#include <iostream>
#include <memory>
#include <stack>
#include <mutex>
#include <exception>

// pop()して空の場合にこの処理が実行される
struct empty_stack: std::exception
{
    const char* what() const throw();
};

template<typename T> class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack& other)
    {
       std::lock_guard<std::mutex> lock(other.m);
       data=other.data;
    }

    // C++11では"= delete"は純粋仮想関数(=0)と同様
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
    }

    // pop処理を行う。戻り値には削除された先頭要素を含める
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack();
        std::shared_ptr<T> const res(
        std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res; 
    }

    // pop処理を行う。引数には削除された先頭要素を含める
    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack();
        value=std::move(data.top());
        data.pop();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};
