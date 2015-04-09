#include <vector>
#include <iostream>
#include <cassert>
#include <tuple>


#include "../collections.h"


int main(){

    auto fibs = [](std::vector<int> t) { 
        return std::vector<int> {t[1], (t[0] + t[1])};
    };

    Collection<int> ints = Collection<int>::take(5, fibs, std::vector<int> {0,1});

    assert(ints == Collection<int>(std::vector<int> {0, 1, 1, 2, 3}));
}
