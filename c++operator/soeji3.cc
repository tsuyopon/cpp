// 添え字演算子のオーバーロード([], =)
#include <iostream>
class TEST
{
private:
  int m_cur_data_;
  int *m_data_;
  unsigned int m_max_size_;
public:
  TEST(unsigned int size) : m_cur_data_(0), m_data_(0), m_max_size_(size) {
    if (m_max_size_ > 0) {
      m_data_ = new int[m_max_size_];
    }
  };
  TEST(const TEST& obj) : m_cur_data_(0), m_data_(0), m_max_size_(0) {}
  ~TEST() { if (m_data_ != NULL)
    {
      delete[] m_data_;
    }
  };
  void operator=(int data) {
    std::cout << "operator=" << std::endl;
    m_cur_data_ = data;
  }
  TEST& operator[](unsigned int suffix)
  {
    std::cout << "operator[]" << std::endl;
    if (suffix < 0 || suffix > m_max_size_) {
      std::cout << "不正メモリへのアクセスです" << std::endl;
    } else {
      std::cout << "要素[" << suffix << "]にデータ" << m_cur_data_ << "を格納しました" << std::endl;
      m_data_[suffix] = m_cur_data_;
    }
    return(*this);
  }
};

int main(int argc, char** argv)
{
  TEST obj(10);
  obj[1] = 3;
  return(0);
}

