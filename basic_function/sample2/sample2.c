#include <stdio.h>
 
const float pi = 3.14;
 
// 関数の宣言と定義 
float calc_a(float r) {
    float area = pi * r * r;
    return area;
}
 
float calc_l(float r) {
    float len = pi * 2 * r;
    return len;
}
 
void prt(float r, float f1, float f2) {
    printf("半径%.1fの円の面積は%.2f、円周の長さは%.2f\n", r, f1, f2);
}
 
// 関数の呼び出し、実行
int main(void) {
    float r = 10.0f, ans = 0, len = 0;
    ans = calc_a(r);
    len = calc_l(r);
    prt(r, ans, len);
 
    return 0;
}
