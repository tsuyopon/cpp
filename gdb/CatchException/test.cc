#include <string>

static void foo(void);

int main()
{
    foo();
    return 0;
}

static void foo()
{
    std::string s = "abc";
    s.replace(-1, 0, "d");
}
