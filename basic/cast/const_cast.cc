#include<iostream>

// constやvolatileを除去するためのキャストで、 このキャストも不正な場合はコンパイルエラーとなります。 
int main(void) {
    const int* HOGE;
    int* hoge = const_cast<int*>(HOGE);
}
