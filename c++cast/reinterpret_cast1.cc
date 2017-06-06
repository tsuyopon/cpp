// reinterpret_castのサンプルプログラム
//
// *reinterpret_cast<int*>(&a);を分解してみていくと
//   1. aのアドレスを受け付けます
//   2. reinterpret_castにint*と指定します。
//   3. 上記によりaが差示すものをint*型に戻します。
//   4. 戻ってきたポインタの値をデリファレンスしてintとして取得します。
// 
// これにより出力結果は1094713344となります。
//  floatとしての12はIEEE表現で表すと次のビット列となります。
//  0100 0001 0100 0000 0000 0000 0000 0000
//
//  このfloatのビット列表現をunsigned intで読むと1094713344となります。
//  ということで非常に危険なキャストであることがわかります。
//
// see http://stackoverflow.com/questions/18544849/how-to-use-reinterpret-cast-in-c
#include <iostream>

int main()
{
    float a = 12;
    int b = *reinterpret_cast<int*>(&a);

    std::cout << b << std::endl;  // 1094713344

    std::cout << static_cast<int>(a) << std::endl;
}
