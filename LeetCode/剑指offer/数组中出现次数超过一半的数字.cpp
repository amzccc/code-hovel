// 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
// 你可以假设数组是非空的，并且给定的数组总是存在多数元素。

#include <vector>
#include <unordered_map>
using namespace std;

//用表不是最佳  O(N)  O(N)
int majorityElement(vector<int>& nums) {
    int half_size = nums.size() / 2;
    unordered_map<int, int> mp{};
    for(auto it: nums){
        if(mp.find(it) != mp.end())
            mp[it]++;
        else
            mp.insert(make_pair(it, 1));
        if(mp[it] > half_size)
            return it;
    }
}


//摩尔投票法  O(N) O(1)
int majority_Element(vector<int>& nums){
    int result = 0;
    int vote = 0;
    for(auto it: nums){
        if(vote == 0){
            result = it;
        }
        result == it? vote++: vote--;
    }
    return result;
}