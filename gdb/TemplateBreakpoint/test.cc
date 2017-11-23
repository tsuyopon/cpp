// g++ -g3 -O0 test.cc
#include <iostream>

template <typename T>
void coin(T v)
{
    std::cout << v << std::endl;
}

template<typename T>
class Foo
{
public:

    T bar(T c)
    {
        return c * 2;
    }
};

int main(int argc, char** argv)
{
    // int template
    Foo<int> f;
    coin(f.bar(10));

    // float template (But only used int)
    Foo<float> g;
    coin(g.bar(100));

    // float template
    Foo<float> h;
    coin(h.bar(100.5));
}
