
#include <dlfcn.h>

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    void* handle = dlopen("test.so", RTLD_NOW);
    if(!handle)
    {
        std::cerr << "Failed to load shared object: " << dlerror() << std::endl;
        return 1;
    }

    int rc = dlclose(handle);
    if(rc)
    {
        std::cerr << "Failed to unload shared object: " << dlerror() << std::endl;
        return 1;
    }

    std::ifstream map("/proc/self/maps");
    while(!map.eof())
    {
        std::string line;
        std::getline(map, line);
        if(line.find("test.so") != std::string::npos)
        {
            std::cout << line << std::endl;
        }
    }

    return 0;
}
