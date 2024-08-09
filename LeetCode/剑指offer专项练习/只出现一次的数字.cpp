// 给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int singleNumber(vector<int>& nums) {
    unordered_map<int, int> mp;
    for(auto it: nums) {
        mp.find(it) != mp.end()? mp[it]++: mp[it] = 1;
    }
    for(auto it: mp) {
        if(it.second == 1)
            return it.first;
    }
    return -1;
}