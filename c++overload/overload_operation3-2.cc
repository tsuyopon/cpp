#include <iostream>
using namespace std;

class TEST
{
private:
  int m_data_;
public:
  TEST(int data) :m_data_(data)
  {
  };
  ~TEST(){};
  //データのセット
  void setData(int data)
  {
    m_data_ = data;
  }

  int print()
  {
    return(m_data_);
  }

  //2項演算子のオーバーロード
  int operator+(const TEST &obj)
  {
    std::cout << "operator+ start" << std::endl;
    return(m_data_ + obj.m_data_);
  }
  int operator-(const TEST &obj)
  {
    std::cout << "operator- start" << std::endl;
    return(m_data_ - obj.m_data_);
  }
  int operator*(const TEST &obj)
  {
    std::cout << "operator* start" << std::endl;
    return(m_data_ * obj.m_data_);
  }
  int operator/(const TEST &obj)
  {
    std::cout << "operator/ start" << std::endl;
    return(m_data_ / obj.m_data_);
  }
  int operator%(const TEST &obj)
  {
    std::cout << "operator% start" << std::endl;
    return(m_data_ % obj.m_data_);
  }
  bool operator==(TEST &obj)
  {
    std::cout << "operator== start" << std::endl;
    return(this->m_data_ == obj.m_data_);
  }
};

int main(int argc, char** argv)
{
  int data = 0;
  TEST obj1(2);
  TEST obj2(3);

  data = obj1 + obj2; 
  std::cout << "ope+ data = " << data << std::endl;

  data = obj1 - obj2; 
  std::cout << "ope- data = " << data << std::endl;

  data = obj1 * obj2;
  std::cout << "ope* data = " << data << std::endl;

  obj1.setData(10);
  obj2.setData(5);
  data = obj1 / obj2;
  std::cout << "ope/ data = " << data << std::endl;

  data = obj1 % obj2;
  std::cout << "ope% data = " << data << std::endl;

  if (obj1 == obj2)
  {
    std::cout << "m_data_の値は一緒です" << std::endl;
  }
  else
  {
    std::cout << "m_data_の値は等しくありません" << std::endl;
  }


  return(0);
}

