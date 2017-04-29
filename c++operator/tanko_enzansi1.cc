// 単項演算子のオーバーロードの例
#include <iostream>

using namespace std;

class TEST
{
private:
  int m_data_;
public:
  TEST(int data) :m_data_(data) {};
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

  //単項演算子のオーバーロード
  TEST& operator=(const TEST &obj)
  {
    cout << "operator=" << endl;
    m_data_ = obj.m_data_;
    return(*this);
  }

  void operator++(int)
  {
    cout << "operator++" << endl;
    m_data_++;
    return;
  }
  void operator--()
  {
    cout << "operator--" << endl;
    --m_data_;
    return;
  }
  TEST* operator->()
  {
    cout << "operator->" << endl;
    return(this);
  }
};

int main(int argc, char** argv)
{
  TEST obj1(2);
  TEST obj2(3);

  obj1 = obj2;
  std::cout << "ope= m_data_ = " << obj1.print() << std::endl;
  obj1++;
  std::cout << "ope= m_data_ = " << obj1.print() << std::endl;
  --obj1;
  std::cout << "ope= m_data_ = " << obj1.print() << std::endl;

  std::cout << "ope= m_data_ = " << obj1->print() << std::endl;
  return(0);
}

