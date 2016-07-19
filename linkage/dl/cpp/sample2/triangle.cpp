#include "polygon.hpp"
#include <cmath>

class triangle : public polygon {
public:
    virtual double area() const {
        return side_length_ * side_length_ * sqrt(3) / 2;
    }
};

////////////////////////////
// dlsymで呼び出す関数は以下のようにextern "c"で囲まれていることがポイントで、そこからnewをして呼び出している。
////////////////////////////
// the class factories
extern "C" polygon* create() {
    return new triangle;
}

extern "C" void destroy(polygon* p) {
    delete p;
}
