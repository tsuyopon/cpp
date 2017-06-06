/*
 * 初期化でstd::vectorに約3000のrandomなデータをセットして、それらをソートするときの時間を測定するベンチマークプログラム
 * ***このプログラムではrvalueやlvalueは登場していませんが、裏側で利用されるものが異なります。***
 * 
 * コンパイルして実行比較してみた感じだとソート処理が-std=c++11を付与したほうがすごい早いです。(違いは-std=c++11が付与されているかどうかのみ)
 * $ g++ sample4.cc -std=c++11
 * $ ./a.out 
 * construction 6.18407
 * sort 0.009821
 * destruction 0.834368
 * Total time = 7.02826
 * 
 * -std=c++11をつけない場合。先程に比べてsortがすごい遅い
 * $ g++ sample4.cc   // nooption
 * $ ./a.out 
 * construction 9.55442
 * sort 7.09672
 * destruction 0.827705
 * Total time = 17.4788
 * 
 * なぜこのような違いが発生しているのかというと、
 * 「コピーが発生しないので気軽にコンテナに入れ放題ということです。」
 * BigDataなクラスでも作ってSTLコンテナに突っ込もうものなら大変なコピーコストになってしまうということです。
 */
#include <vector>
#include <iostream>
#include <time.h>
#include <set>
#include <algorithm>

static const int N = 3001;

std::set<int> get_set(int)
{
  std::set<int> s;
  for (int i = 0; i < N; ++i) {
    while (!s.insert(std::rand()).second) ;
  }
  return s;
}

std::vector<std::set<int> > generate()
{
  std::vector<std::set<int> > v;
  for (int i = 0; i < N; ++i) {
    v.push_back(get_set(i));
  }
  return v;
}

void output(const char* s, clock_t t1, clock_t t2)
{
  std::cout << s <<
    static_cast<float>(((t2 - t1) /
    static_cast<double>(CLOCKS_PER_SEC)))
  << std::endl;
}

float time_it()
{
  clock_t t1, t2, t3;
  clock_t t0 = clock();
  {
    std::vector<std::set<int> > v = generate();
    t1 = clock();
    output("construction ", t0, t1);
    std::sort(v.begin(), v.end());
    t2 = clock();
    output("sort ", t1, t2);
  }
  t3 = clock();
  output("destruction ", t2, t3);
  return static_cast<float>(((t3 - t0) /
         static_cast<double>(CLOCKS_PER_SEC)));
}

int main()
{
  float t = time_it();
  std::cout << "Total time = " << t << '\n';
}
