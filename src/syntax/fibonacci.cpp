#include <ostream>
#include <vector>

#include "../collections.h"

int main() {

    // there is no standard syntax for infinite lists

    // Collection syntax
    auto fibGen = [](std::vector<int> v) {
                      return std::vector<int> { v[1], v[0] + v[1] };
                  };

    auto fibs = Collection<int>::take(20, fibGen, std::vector<int> {0,1});
}
