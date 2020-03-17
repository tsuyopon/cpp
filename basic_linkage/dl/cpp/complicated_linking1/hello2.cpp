#include <iostream>
#include <string>
#include <vector>
#include <dlfcn.h>
#include "external.h"

extern "C" void hello2() {
    external();
    std::cout << "hello2" << '\n';
        std::vector<std::string> data;
        std::vector<std::string>::iterator itr;
        data.push_back("sub1");
        data.push_back("sub2");
        for(itr=data.begin(), data.end(); itr != data.end(); ++itr){
                data.erase(data.begin());
        }

    std::cout << "Opening hello3.so...\n";
    void* handle2 = dlopen("./hello3.so", RTLD_NOW|RTLD_GLOBAL);
    dlclose(handle2);

}
