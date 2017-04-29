// newとdeleteのオペレータについて
#include <iostream>
using namespace std;

void* operator new(size_t size) {
  std::cout << "new operator, alloc size = " << size << std::endl;
  return(malloc(size));
}

void* operator new[](size_t size) {
  std::cout << "new[] operator, alloc size = " << size << std::endl;
  return(malloc(size));
}

void operator delete(void* po) {
  std::cout << "delete operator, delete address = " << std::hex << po << std::endl;
}

void operator delete[](void* po) {
  std::cout << "delete[] operator, delete address = " << std::hex << po << std::endl;
}

int main(int argc, char** argv)
{
  int *p_value1 = (int *)new int;
  int *p_value2 = (int *)new int[10];
  delete p_value1;
  delete[] p_value2;
}

