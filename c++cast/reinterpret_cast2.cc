#include<iostream>

using namespace std;

int main()
{
  int a = 22;
  float b = (float)33.3333;

  cout<<"1. a = "<< a <<"   b = "<< b <<endl;

  a = (int)b; //Old C programming way
  cout<<"2. a = "<< a <<"   b = "<< b <<endl;

  // Wont work in this case because floating point format is different
  a = reinterpret_cast<int&>(b);
  cout<<"3. a = "<< a <<"   b = "<< b <<endl;

  a = static_cast<int>(b); //Correct approach
  cout<<"4. a = "<< a <<"   b = "<< b <<endl;

  char c;
  //Convert int to char
  c = reinterpret_cast<char&>(a);
  cout<<"5. c = "<< (int)c <<"   a = "<< a <<endl;

  //Dangerous to convert from char to int
  a = reinterpret_cast<int&>(c);
  cout<<"6. c = "<< (int)c <<"   a = "<< a <<endl;

  //What we actually wanted was just the last 8 bits so...
  a = a & 0x000000FF; //00 = 8 bits
  cout<<"7. c = "<< (int)c <<"   a = "<< a <<endl;

  return 0;
}

