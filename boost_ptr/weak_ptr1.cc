// shared_ptrの参照数を増やさないための変数としてweak_ptrが存在する。
#include <iostream>
#include <string>
#include <memory>
#include <cassert>

using namespace std;

class Hoge 
{
    private:
        string s_; 
    public:
        explicit Hoge(const string &s) :s_(s) {   
            cout << "Hoge::Hoge(" + s_ + ")" << endl;
        }   
        ~Hoge() {   cout << "Hoge::~Hoge(" + s_ + ")" << endl; }   
};

int main()
{
    weak_ptr<Hoge> weak;

    {   
        // この時点でAのカウント数は1である
        shared_ptr<Hoge> shared0(new Hoge("A"));
        assert(shared0.use_count() == 1); 

        // shared0の参照者が増えると、参照カウント数も増える
        shared_ptr<Hoge> shared1= shared0;
        assert(shared0.use_count() == 2); 

        // weakがshared0を監視するも、参照カウント数は増えない
        weak = shared0;
        assert(shared0.use_count() == 2); 
    } // ここでshared_ptrは無効になる

    // 監視しているshared_ptrの寿命は無効
    assert(weak.expired());
    return 0;
}

