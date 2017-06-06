/*
 * time_facetで時刻フォーマットを指定して取得する
 */
#include <iostream>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>

int
main(){
    namespace pt = boost::posix_time;
    namespace gg = boost::gregorian;

    // フォーマットの指定
    // facet はストリーム側で自動的に delete される
    // 実行サンプル
    // $ ./a.out 
    //  2017-04-26 08:40:26

    auto facet = new pt::time_facet("%Y-%m-%d %H:%M:%S");
    std::stringstream ss;
    ss.imbue(std::locale(std::cout.getloc(), facet));
    
    // 現在の時刻を取得
    auto now_time = pt::second_clock::local_time();
    ss << now_time;
    std::cout << ss.str() << std::endl;

    return 0;
}
