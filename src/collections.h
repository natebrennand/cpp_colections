
#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <vector>
#include <functional>
#include <iostream>


template<typename T>
class Collection {
private:
    std::vector<T> Data;
public:
    Collection<T>(std::vector<T> d) {
        Data = d;
    }

    Collection<T>
    filter(std::function<bool(T)> func);

    Collection<T>
    slice(int low, int high);

    template<typename Function>
    Collection<typename std::result_of<Function(T)>::type>
    map(Function func);

    T
    fold(std::function<T(T, T)> func);

    template<typename Function, typename U>
    typename std::result_of<Function(U, T)>::type
    reduce(Function func, U init);

    T
    operator[] (const int index);

    void
    print();

};


template<typename T>
Collection<T>
Collection<T>::filter(std::function<bool(T)> func) {
    std::vector<T> list;
    for (auto i : Data)
        if (func(i))
            list.push_back(i);
    return Collection<T>(list);
};

template<typename T>
Collection<T>
Collection<T>::slice(int low, int high) {
    // TODO: bounds checking
    std::vector<T> list;
    for (int i = low; i <= high; i++)
        list.push_back(Data[i]);
    return Collection<T>(list);
};

template<typename T>
template<typename Function>
Collection<typename std::result_of<Function(T)>::type>
Collection<T>::map(Function func) {
    using return_type = typename std::result_of<Function(T)>::type;

    std::vector<return_type> list;
    for (int i = 0; i < Data.size(); i++)
        list.push_back(func(Data[i]));
    return Collection<return_type>(list);
};

template<typename T>
T
Collection<T>::fold(std::function<T(T, T)> func) {
    // TODO: bounds checking
    T val = func(Data[0], Data[1]);
    for (int i = 2; i < Data.size(); i++)
        val = func(val, Data[i]);

    return val;
};

template<typename T>
template<typename Function, typename U>
typename std::result_of<Function(U, T)>::type
Collection<T>::reduce(Function func, U init) {
    using return_type = U;
    /*
    static_assert(
        std::is_same<
            decltype(func),
            std::function<U(U, T)>
        >::value,
           "Reduce fn must return the same type as the initial value");
    */

    // TODO: bounds checking
    return_type val = func(init, Data[0]);
    for (int i = 1; i < Data.size(); i++)
        val = func(val, Data[i]);

    return val;
};

template<typename T>
T
Collection<T>::operator[] (const int index) {
    return Data[index];
};

template<typename T>
void
Collection<T>::print() {
    std::cout << "[";
    for (int i = 0; i < Data.size() - 1; i++)
        std::cout << Data[i] << ",";
    std::cout << Data[Data.size() - 1] << "]" << std::endl;
};

#endif

