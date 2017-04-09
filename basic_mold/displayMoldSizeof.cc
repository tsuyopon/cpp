#include<iostream>

struct INT16{
    int16_t n;
    int8_t d;
};

struct FAST16{
    int_fast16_t n;
    int_fast8_t d;
};

struct LEAST16{
    int_least16_t n;
    int_least8_t d;
};

struct PINT16{
    int16_t n;
    int8_t d;
}__attribute__((__packed__));

struct PFAST16{
    int_fast16_t n;
    int_fast8_t d;
}__attribute__((__packed__));

struct PLEAST16{
    int_least16_t n;
    int_least8_t d;
}__attribute__((__packed__));


using namespace std;

int main(){    

    cout << "sizeof(char)          =" << sizeof(char) << endl;
    cout << "sizeof(unsigned char) =" << sizeof(unsigned char) << endl;
    cout << "sizeof(signed char)   =" << sizeof(signed char) << endl;
    cout << "sizeof(int)           =" << sizeof(int) << endl;
    cout << "sizeof(unsigned int)  =" << sizeof(unsigned int) << endl;
    cout << "sizeof(signed int)    =" << sizeof(signed int) << endl;
    cout << "sizeof(short)         =" << sizeof(short) << endl;
    cout << "sizeof(float)         =" << sizeof(float) << endl;
    cout << "sizeof(double)        =" << sizeof(double) << endl;
    cout << "sizeof(long)          =" << sizeof(long) << endl;
    cout << "sizeof(long long)     =" << sizeof(long long) << endl;
    cout << "sizeof(long double)   =" << sizeof(long double) << endl;

    cout << "sizeof(int8_t) =" << sizeof(int8_t) << endl;
    cout << "sizeof(int16_t)=" << sizeof(int16_t) << endl;
    cout << "sizeof(int32_t)=" << sizeof(int32_t) << endl;
    cout << "sizeof(int64_t)=" << sizeof(int64_t) << endl;

    cout << "sizeof(int_fast8_t) =" << sizeof(int_fast8_t) << endl;
    cout << "sizeof(int_fast16_t)=" << sizeof(int_fast16_t) << endl;
    cout << "sizeof(int_fast32_t)=" << sizeof(int_fast32_t) << endl;
    cout << "sizeof(int_fast64_t)=" << sizeof(int_fast64_t) << endl;

    cout << "sizeof(int_least8_t) =" << sizeof(int_least8_t) << endl;
    cout << "sizeof(int_least16_t)=" << sizeof(int_least16_t) << endl;
    cout << "sizeof(int_least32_t)=" << sizeof(int_least32_t) << endl; 
    cout << "sizeof(int_least64_t)=" << sizeof(int_least64_t) << endl; 

    cout << "sizeof(intmax_t)=" << sizeof(intmax_t) << endl;
    cout << "sizeof(intptr_t)=" << sizeof(intptr_t) << endl;

    cout << "sizeof(uintmax_t)=" << sizeof(uintmax_t) << endl;
    cout << "sizeof(uintptr_t)=" << sizeof(uintptr_t) << endl;

    cout << endl << "CHECKI FOR PADDING" << endl;
    cout << "sizeof(INT16)=" << sizeof(INT16) << endl;
    cout << "sizeof(FAST16)=" << sizeof(FAST16) << endl;
    cout << "sizeof(LEAST16)=" << sizeof(LEAST16) << endl;

    cout << "sizeof(PINT16)=" << sizeof(PINT16) << endl;
    cout << "sizeof(PFAST16)=" << sizeof(PFAST16) << endl;
    cout << "sizeof(PLEAST16)=" << sizeof(PLEAST16) << endl;

    return 1;
}
