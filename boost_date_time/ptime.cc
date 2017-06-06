// 現在時刻を様々な形式で取得する
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
typedef boost::posix_time::ptime PTime;
typedef boost::posix_time::second_clock Clock;

void judgeTime(PTime time, PTime othertime){

	if( time > othertime){
		cout << "time > othertime" << endl;
	} else if( time == othertime ){
		cout << "time == othertime" << endl;
	} else {
		cout << "time < othertime" << endl;
	}

}

int main()
{
	PTime time = Clock::local_time();   // その地域を取得する

	// 現在の時刻・日付・時・分・秒を取得する
	cout << time << endl;
	cout << time.date() << endl;
	cout << time.time_of_day() << endl;
	cout << time.time_of_day().hours() << endl;
	cout << time.time_of_day().minutes() << endl;
	cout << time.time_of_day().seconds() << endl;

	// 特定の時間加算・減算した時刻の日付を表示する
	PTime time2 = time + boost::posix_time::hours(-24);
	PTime time3 = time + boost::posix_time::hours(0);
	PTime time4 = time + boost::posix_time::hours(24);
	cout << time2.time_of_day() << endl;
	cout << time3.time_of_day() << endl;
	cout << time4.time_of_day() << endl;

	// 時刻を判定することも可能です。
	judgeTime(time, time2);
	judgeTime(time, time3);
	judgeTime(time, time4);

	return 0;
}
