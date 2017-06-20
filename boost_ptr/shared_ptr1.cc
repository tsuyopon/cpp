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
        ~Hoge() { cout << "Hoge::~Hoge(" + s_ + ")" << endl; }
};

int main()
{
    shared_ptr<Hoge> hoge_ptr0;

    {
        cout << "---AとBの構築---" << endl;
        shared_ptr<Hoge> hoge_ptr1(new Hoge("A"));
        shared_ptr<Hoge> hoge_ptr2(new Hoge("B"));
        shared_ptr<Hoge> hoge_ptr3(new Hoge("C"));

        // この時点でA,B,Cのカウント数は1である
        assert(hoge_ptr1.use_count() == 1);
        assert(hoge_ptr2.use_count() == 1);
        assert(hoge_ptr3.use_count() == 1);

        cout << "---Aの破棄---" << endl;
        hoge_ptr0 = hoge_ptr1 = hoge_ptr2; // ここでAは誰からも参照されなくなるので、Aはここで破棄される

        // hoge_ptr0とAがBを指す様になったのでBのカウント数は3となる
        assert(hoge_ptr2.use_count() == 3);
        assert(hoge_ptr3.use_count() == 1);

        cout << "---Cの破棄---" << endl;
    } // このスコープを抜けるとCを参照する者がいなくなるので、Cは破棄される

    cout << "---Bの破棄---" << endl;
    return 0;
} // ここでBを参照する者がいなくなるので、Bは破棄される
