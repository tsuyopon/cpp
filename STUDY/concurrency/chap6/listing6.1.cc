#include <iostream>
#include <memory>
#include <stack>
#include <mutex>
#include <exception>

// pop()して空の場合にこの処理が実行される
struct empty_stack: std::exception
{
    // 定義だけだとエラーになるので、returnを返すような実装が必要
    const char* what() const throw() {
         return "enter what message";
    }
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

    // 暗黙的なコピーコンストラクタの生成を拒否する
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


int main(){
	threadsafe_stack<int> si;
	std::shared_ptr<int> pop;
	si.push(5);
	pop = si.pop();
	std::cout << "pop value = " << *pop << std::endl;
	si.empty();
	pop = si.pop();
	std::cout << "pop value = " << *pop << std::endl;
	return 0;
}
