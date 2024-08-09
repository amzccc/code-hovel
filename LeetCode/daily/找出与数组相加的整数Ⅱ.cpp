// 给你两个整数数组 nums1 和 nums2。

// 从 nums1 中移除两个元素，并且所有其他元素都与变量 x 所表示的整数相加。如果 x 为负数，则表现为元素值的减少。

// 执行上述操作后，nums1 和 nums2 相等 。当两个数组中包含相同的整数，并且这些整数出现的频次相同时，两个数组 相等 。

// 返回能够实现数组相等的 最小 整数 x 。

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    int res = 0;
    for(size_t i = 0, j = 1; i < nums1.size() && j < nums1.size();) {
        vector<int> tmp(nums1.begin(), nums1.begin() + i);
        tmp.insert(tmp.end(), nums1.begin() + i + 1, nums1.begin() + j);
        tmp.insert(tmp.end(), nums1.begin() + j + 1, nums1.end());
        res = nums2[0] - tmp[0];
        size_t k = 1;
        for(; k < nums2.size(); k++) {
            if(nums2[k] - tmp[k] != res) {
                break;
            }
        }
        if(k == nums2.size()) {
            break;
        }

        ++j;
        if(j == nums1.size()) {
            ++i;
            j = i + 1;
        }
    }
    return res;
}

int main() {
    vector<int> nums1{ 4,20,16,12,8 };
    vector<int> nums2{ 14,18,10 };
    cout << minimumAddedInteger(nums1, nums2) << endl;


    return 0;
}