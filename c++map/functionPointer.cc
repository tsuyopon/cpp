//
// std::mapの中に関数ポインタを指定する例
//
// g++ test.cc -std=c++11
//
// 参考: https://qiita.com/nonbiri15/items/ff739d455377bc1bc9ed
#include <iostream>
#include <map>
#include <string>

double Add(double a, double b){ return a + b; }
double Sub(double a, double b){ return a - b; }
double Mul(double a, double b){ return a * b; }
double Div(double a, double b){ return a / b; }

std::map<std::string , double(*)(double, double)> funcMap= {
    { "+", Add },
    { "-", Sub },
    { "*", Mul },
    { "/", Div }
};

int main(int argc, char* argv[]){
    while(true){
        std::string letter;
        std::cout << "演算子を指定して下さい > " << std::flush;
        std::cin >> letter;

        if (funcMap.find(letter) != funcMap.end()){
            double     a, b;
            std::cout << "２つの数値を入力して下さい > " << std::flush;
            std::cin >> a >> b;
            std::cout << a << letter << b << " = ";
            std::cout << funcMap[letter](a, b) << std::endl;
        }
        else{
            std::cout << "そのような演算子はありません" << std::endl;
        }
    }
    return 0;
}
