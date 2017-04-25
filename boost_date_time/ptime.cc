// 現在時刻を様々な形式で取得する
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

int main()
{
	typedef boost::posix_time::ptime PTime;
	typedef boost::posix_time::second_clock Clock;
	PTime time = Clock::local_time();   // その地域を取得する

	// 現在の時刻・日付・時・分・秒を取得する
	cout << time << endl;
	cout << time.date() << endl;
	cout << time.time_of_day() << endl;
	cout << time.time_of_day().hours() << endl;
	cout << time.time_of_day().minutes() << endl;
	cout << time.time_of_day().seconds() << endl;

	// 4時間加算した時刻の日付を表示する
	time = time + boost::posix_time::hours(4);
	cout << time.time_of_day() << endl;

	return 0;
}
