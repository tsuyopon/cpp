#include<iostream>

// constやvolatileを除去するためのキャストで、 このキャストも不正な場合はコンパイルエラーとなります。 
int main(void) {

    // constを除去する場合
    const int* HOGE;
    int* hoge = const_cast<int*>(HOGE);

    // volatileを除去する場合(volatileはコンパイルによる最適化を抑制するフラグです)
    volatile int* HOGE2;
    int* hoge2 = const_cast<int*>(HOGE2);
}
