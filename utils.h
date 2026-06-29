#ifndef UTILS_H
#define UTILS_H
#include <vector>

template<typename T>
struct Edge{
    int source, destination;
    T w;
};

template<typename T>
struct ASPSResult{
    std::vector<std::vector<T>> distances;
    std::vector<std::vector<int>> preds;
    bool negative_cycle = false;
};
#endif