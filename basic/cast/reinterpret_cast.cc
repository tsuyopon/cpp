#include<iostream>

/*
 * 最も危険なキャストです。 このキャストは強制的にビット構成を変更するので、 void*の変換や整数型のポインタへの変換などに使用します。 このキャストは危険なので、使う気をなくすような長い名前が付けられています。 
 * 普通は使用しなくても大丈夫なのですが、Win32APIで一部使用する必要が出てきます。
 * reinterpret_castはビット構成を再解釈するだけなので、 constやvolatileの除去は出来ませんし、 継承関係にあってもポインタは再計算されません。
 */
int main(void) {
    long hoge = 1111;
    int* hogehoge = reinterpret_cast<int*>(hoge);
}
