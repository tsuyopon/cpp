// main.cpp
#include <iostream>
#include "Singleton.h"

int main(void) {

	// getInstance()を通じてSingletonClassにアクセスできるようになります。
    SingletonClass* sc = SingletonClass::getInstance();
	SingletonClass::getInstance()->doSomething(100);

	// アドレスからの呼び出しはドット(.)ではなくアロー演算子(->)を用います
    sc->start();
    sc->doSomething(1);
    sc->doSomething(1);
    sc->end();
}
