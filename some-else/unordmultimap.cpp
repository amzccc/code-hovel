#include <unordered_map>
#include <string>
#include <iostream>
#include <utility>
#include "buckets.hpp"

int main()
{
    using namespace std;
    unordered_multimap<string, string> dict = {
                                {"day", "Tag"},
                                {"strange", "fremd"},
                                {"car", "Auto"},
                                {"smart", "elegant"},
                                {"trait", "Merkmal"},
                                {"strange", "seltsam"}
    };
    printHashTableState(dict);

    //插入一些键值对
    dict.insert({{"smart", "reffiniert"},
                {"smart", "klug"},
                {"clever", "raffiniert"},
    });
    printHashTableState(dict);

    //设置最大负载因子
    dict.max_load_factor(0.7);
    printHashTableState(dict);

}