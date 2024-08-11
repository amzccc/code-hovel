// 在两条独立的水平线上按给定的顺序写下 nums1 和 nums2 中的整数。

// 现在，可以绘制一些连接两个数字 nums1[i] 和 nums2[j] 的直线，这些直线需要同时满足：

//  nums1[i] == nums2[j]
// 且绘制的直线不与任何其他连线（非水平线）相交。
// 请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。

// 以这种方法绘制线条，并返回可以绘制的最大连线数。

#include <iostream>
#include <vector>
#include <array>
#include <numeric>
#include <limits>

using namespace std;

int subLines(const vector<vector<int>>& dict, int row, int col);

int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
    int size1 = nums1.size();
    int size2 = nums2.size();
    array<array<int, 500>, 500> dict{};
    for(int i = 0; i < size1; i++) {
        for(int j = 0; j < size2; j++) {
            int max = 0;
            for(int k = 0; k < i && j > 0; k++) {
                max = dict[k][j - 1] < max ? max : dict[k][j - 1];
            }
            for(int k = 0; k < j && i > 0; k++) {
                max = dict[i - 1][k] < max ? max : dict[i - 1][k];
            }
            dict[i][j] = max + (nums1[i] == nums2[j] ? 1 : 0);
        }
    }
    int count = 0;
    for(int i = 0; i < size1; i++) {
        count = dict[i][size2 - 1] < count ? count : dict[i][size2 - 1];
    }
    for(int i = 0; i < size2; i++) {
        count = dict[size1 - 1][i] < count ? count : dict[size1 - 1][i];
    }
    return count;
}


int main() {
    vector<int> nums1{ 1,1,3,5,3,3,5,5,1,1 };
    vector<int> nums2{ 2,3,2,1,3,5,3,2,2,1 };
    cout << maxUncrossedLines(nums1, nums2) << endl;

    return 0;
}

