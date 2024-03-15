#include <unordered_set>
#include <iostream>
#include "buckets.hpp"

int main()
{
    //创建并初始化一个hashset
    std::unordered_set<int> intset {1, 3, 5, 7, 9, 11, 13, 17, 19};
    printHashTableState(intset);

    //插入值
    intset.insert({-7, 17, 33, 4});
    printHashTableState(intset);
}