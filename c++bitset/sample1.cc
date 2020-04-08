// 10進数をビット列で表示する
#include <iostream>
#include <bitset>
using namespace std;

int main() {
    int A = 0x2d;
    int B = 0x19;
    cout << A << " AND " << B << " = " << (A&B) << endl;

    // ビット列で表示する
    cout << bitset<8>(A) << " AND " << bitset<8>(B) << " = " << bitset<8>(A&B) << endl;
}
