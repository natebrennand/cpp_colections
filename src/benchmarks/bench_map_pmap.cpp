#include <iostream>
#include <vector>

#include "../collections.h"
#include "benchmark.h"


#define size 100000
#define trials 100


int main() {
    // timing map on a vector of size 100,000
    auto input = [](){ return Collection<int>::range(0, size); };
    auto inc = [](int x) {return x+1;};
    random_generator rand_gen;

    auto rand_input = [&](){
        std::vector<int> data(size);
        for (int i = 0; i < size; i++)
            data[i] = rand_gen(size);
        return data;
    };

    std::cout << "Comparing map & pmap" << std::endl;


    bench(input, [&](Collection<int> i){
        return i.map(inc);
    }, trials, "map: linear map");

    bench(input, [&](Collection<int> i){
        return i.pmap(inc, 10);
    }, trials, "pmap: parallel map");

    bench(rand_input, [&](Collection<int> i){
        return i.map(inc);
    }, trials, "map: linear map w/ random data");

    bench(rand_input, [&](Collection<int> i){
        return i.pmap(inc, 10);
    }, trials, "pmap: parallel map w/ random data");
}
