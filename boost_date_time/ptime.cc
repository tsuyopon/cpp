#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

int main()
{
	typedef boost::posix_time::ptime PTime;
	typedef boost::posix_time::second_clock Clock;
	PTime time = Clock::local_time();

	cout << time << endl;
	cout << time.date() << endl;
	cout << time.time_of_day() << endl;
	cout << time.time_of_day().hours() << endl;
	cout << time.time_of_day().minutes() << endl;
	cout << time.time_of_day().seconds() << endl;

	time = time + boost::posix_time::hours(4);
	cout << time.time_of_day() << endl;

	return 0;
}
