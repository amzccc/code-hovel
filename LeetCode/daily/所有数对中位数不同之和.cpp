// 你有一个数组 nums ，它只包含 正 整数，所有正整数的数位长度都 相同 。

// 两个整数的 数位不同 指的是两个整数 相同 位置上不同数字的数目。

// 请你返回 nums 中 所有 整数对里，数位不同之和。

#include <iostream>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

long long sumDigitDifferences(vector<int>& nums) {
    long long res = 0;
    int size = nums.size();
    array<int, 10> digits{};
    long long base = 100000000;
    for(int i = 8; i >= 0; i--) {
        for(int j = 0; j < size; j++) {
            int num = (nums[j] % (base * 10)) / base;
            digits[num]++;
        }
        long long prev = 0;
        for(int k = 0; k < digits.size(); k++) {
            res += digits[k] * prev;
            prev += digits[k];
            digits[k] = 0;
        }
        base /= 10;
    }
    return res;
}

int main() {
    vector<int> nums{ 13,23,12 };
    cout << sumDigitDifferences(nums) << endl;

    
    return 0;
}