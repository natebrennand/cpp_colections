#include <cmath>
#include <ostream>
#include <vector>
#include <cassert>

#include "../cpp_collections.h"

using namespace cpp_collections;

int main() {

    // Collection syntax

    def_generator(ones, int) {
        return Stream<int>(1, ones);
    };

    Stream<int> test = 2 & ones();

    assert(test.take(3) == Collection<int>(std::vector<int>{2,1,1}));

}
