#include<iostream>

// explicitキーワードは引数を一個しか持たないコンストラクタの暗黙の変換を禁止します。
class Hoge {
    int hoge;
public:
    explicit Hoge(int hoge) { this->hoge = hoge; }  // このexplicitを外すとコンパイルが通ります
    int getHoge(void) { return hoge; }
};

int main(void) {
    Hoge hoge = 10;         // エラー
    Hoge hoge2(20);
    return hoge2.getHoge();
}
