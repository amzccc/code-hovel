// 输入一个非负整数数组，
// 把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
using namespace std;


void quicksort(vector<string> &strs, int l_ptr, int r_ptr) {
    if(l_ptr >= r_ptr)
        return;
    int l = l_ptr;
    int r = r_ptr;
    while(l < r) {
        while(strs[l] + strs[r_ptr] <= strs[r_ptr] + strs[l] && l < r)
            l++;
        while(strs[l] + strs[r_ptr] >= strs[r_ptr] + strs[l] && l < r)
            r--;
        swap(strs[l], strs[r]);
    }
    swap(strs[r_ptr], strs[l]);
    quicksort(strs, l_ptr, l - 1);
    quicksort(strs, l + 1, r_ptr); 
}

string minNumber(vector<int>& nums) {
    vector<string> strs;
    for(auto it : nums) {
        strs.push_back(to_string(it));
    }
    int l_ptr = 0; 
    int r_ptr = strs.size() - 1;
    quicksort(strs, l_ptr, r_ptr);
    string res;
    for(auto it: strs)
        res.append(it);
    return res;
}


int main()
{
    vector<int> vec{1,2,3,1};
    cout << minNumber(vec);
}