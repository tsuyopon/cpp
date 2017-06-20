#include <vector>
#include <iostream>
#include <algorithm>

static int NUM_ITEMS = 10;

class gen_range {
    public:
        gen_range(int i) { idx = i; }
        int operator()() { return (idx++); };

    int idx;
};

int main() {

    std::vector<int> x(NUM_ITEMS);
    std::generate_n(x.begin(), NUM_ITEMS, gen_range(0));

    for (int i=0; i < x.size(); i++) {
        std::cout << x[i] << std::endl;
    }
}
