// UTCを表示するサンプル
// 参考: http://kkayataka.hatenablog.com/entry/2013/05/04/184549
#include <iostream>

#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/local_time_adjustor.hpp>

int main(const int argc, const char * const argv[]) {
  using namespace boost;

  posix_time::ptime now = posix_time::second_clock::universal_time();

  // utc to local 1
  date_time::c_local_adjustor<posix_time::ptime> adj1;
  posix_time::ptime t1 = adj1.utc_to_local(now);
  
  // utc to local 2
  date_time::local_adjustor<posix_time::ptime, 9, posix_time::no_dst> adj2;
  posix_time::ptime t2 = adj2.utc_to_local(now);
  
  // local to utc
  posix_time::ptime t3 = adj2.local_to_utc(t2);

  // out
  std::cout << now << std::endl;  // UTC
  std::cout << t1 << std::endl;   // JapanTime(UTC+9h)
  std::cout << t2 << std::endl;   // JapanTime(UTC+9h)
  std::cout << t3 << std::endl;   // UTC

  return 0;
}

