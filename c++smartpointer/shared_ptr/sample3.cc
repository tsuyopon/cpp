/*
 * shared_ptrには配列を扱う機能がありませんが、少し工夫をすれば扱うことができる様になります。
 *
 * 参考: https://programming.pc-note.net/cpp/smartpointer3.html
 */
#include <iostream>
#include <memory>
 
int main()
{
    // 配列の場合にはmake_sharedを使うことはできない。このため、以下の例ではnewを利用します。
    // shared_ptrは配列に対応していないため、テンプレート引数に配列を指定できませんし、デフォルトのdeleterは「delete」が実行されるだけで、「delete[]」が実行されません。
    // このためにdeleterでint[]を指定することで、delete[]を実行してくれる様になります。
    std::shared_ptr<int> ptr(new int[5], std::default_delete<int[]>());  // 
 
    for (int i = 0; i < 5; i++) 
        ptr.get()[i] = i;
 
    std::cin.get();
}
