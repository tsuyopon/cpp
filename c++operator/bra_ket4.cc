// ()オペレータについて
#include <iostream>
using namespace std;

class TEST
{
private:
public:
  TEST()
  {
  };
  ~TEST(){};

  TEST& operator()()
  {
    std::cout << "operator() start" << std::endl;
	return (*this);
  }
};

int main(int argc, char** argv)
{
  TEST obj;
  TEST obj2;
  TEST obj3();   // ここでは呼ばれない
  std::cout << "operator() before" << std::endl;
  obj2 = obj();  // ここで呼ばれる
  std::cout << "operator() after" << std::endl;

  return(0);
}

