#include <iostream>
#include <vector>
using namespace std;

template <template <typename, typename> class TEMPL> class Hoge {
	public:
		void Run() {
			m_v.push_back(1);
			m_v.push_back(3);
			m_v.push_back(5);
			for(size_t i = 0, size = m_v.size(); i < size; ++i){
				cout << m_v[i] << ' ';
			}
			cout << endl;
		}

	private:
		TEMPL<int, allocator<int> > m_v;
};

int main(){
	Hoge<vector> hoge;
	hoge.Run();
}
