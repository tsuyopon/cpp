#include<iostream>
#include "namespace2.h"

namespace Azarashi {
	namespace Goma {
		// ヘッダファイルで宣言しているのでここに class Tamachan { } はかけないことに注意
		Tamachan::Tamachan(){
			std::cout << "I am Azarashi::Goma::Tamachan::Tamachan()" << std::endl;
		}
		Tamachan::~Tamachan(){
			std::cout << "Sleep Azarashi::Goma::Tamachan::Tamachan()" << std::endl;
		}
		void Tamachan::cry(){
			std::cout << "Kyu-" << std::endl;
		}
	}

	namespace Zou{
		// ヘッダファイルで宣言しているので、ここに class Normal{ } はかけないことに注意
		Normal::Normal(){
			std::cout << "I am Azarashi::Zou::Normal::Normal()" << std::endl;
		}
		Normal::~Normal(){
			std::cout << "Sleep Azarashi::Zou::Normal::Normal()" << std::endl;
		}
		void Normal::cry(){
			std::cout << "KyuKyu-" << std::endl;
		}
	}
}

int main(){
	Azarashi::Goma::Tamachan obj;
	Azarashi::Zou::Normal obj2;
	std::cout << "hello" << std::endl;
	return 0;
}
