// 给你两个整数数组 nums1 和 nums2。

// 从 nums1 中移除两个元素，并且所有其他元素都与变量 x 所表示的整数相加。如果 x 为负数，则表现为元素值的减少。

// 执行上述操作后，nums1 和 nums2 相等 。当两个数组中包含相同的整数，并且这些整数出现的频次相同时，两个数组 相等 。

// 返回能够实现数组相等的 最小 整数 x 。

#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <limits>

using namespace std;

int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    int res = numeric_limits<int>::max();
    for(size_t i = 0, j = 1; i < nums1.size() && j < nums1.size();) {
        size_t k = 0;
        while(k == i || k == j) {
            ++k;
        }
        int diff = nums2[0] - nums1[k];
        size_t n = 0;
        while(k < nums1.size()) {
            if(k == i || k == j) {
                ++k;
                continue;
            }
            if(diff != nums2[n] - nums1[k]) {
                break;
            }
            ++k;
            ++n;
        }
        if(k == nums1.size() && res > diff) {
            res = diff;
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
    vector<int> nums1{ 9,4,3,9,4 };
    vector<int> nums2{ 7,8,8 };
    cout << minimumAddedInteger(nums1, nums2) << endl;


    return 0;
}