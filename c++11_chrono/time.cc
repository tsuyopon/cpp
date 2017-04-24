// $ g++ time.cc -I/usr/include/boost141/ -std=c++11
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std::chrono;

int main()
{
  system_clock::time_point p = system_clock::now();

  std::time_t t = system_clock::to_time_t(p);
  std::cout << std::ctime(&t) << std::endl;
  std::cout << std::time(&t) << std::endl;

  const tm* lt = std::localtime(&t);
  std::cout << lt << std::endl;

  auto tp = std::chrono::system_clock::from_time_t(t);
  std::time_t t2 = system_clock::to_time_t(tp);
  std::cout << std::ctime(&t2) << std::endl;
}

