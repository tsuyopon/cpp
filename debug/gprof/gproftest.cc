// g++ -pg test.cc  

#include <cstdio>

int a(void) {
    int i=0,g=0;
    while(i++<1000)
    {
        g+=i;
    }
    return g;
}
int b(void) {
    int i=0,g=0;
    while(i++<4000)
    {
        g+=i;
    }
    return g;
}

int main()
{
    int iterations = 100000;
    while(iterations--)
    {
        a();
        b();

        int i=0,g=0;
        while(i++<3000)
        {
            g+=i;
        }
    }

    return 0;
}
