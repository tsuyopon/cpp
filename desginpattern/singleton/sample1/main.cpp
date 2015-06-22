// main.cpp
#include <iostream>
#include "Singleton.h"

int main(void) {
    SingletonClass* sc = SingletonClass::getInstance();
	SingletonClass::getInstance()->doSomething(100);
    sc->start();
    sc->doSomething(1);
    sc->end();
}
