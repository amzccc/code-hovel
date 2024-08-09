#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

void rotate(std::vector<int>& nums, std::size_t size) {
    if(size >= nums.size()) {
        return;
    }
    for(int i = 0, j = size - 1; i < j; i++, j--) {
        std::swap(nums[i], nums[j]);
    }
    for(int i = size, j = nums.size() - 1; i < j; i++, j--) {
        std::swap(nums[i], nums[j]);
    }
    for(int i = 0, j = nums.size() - 1; i < j; i++, j--) {
        std::swap(nums[i], nums[j]);
    }
}

int main() {
    std::vector<int> nums{ 0,1,2,3,4,5,6,7,8,9 };
    rotate(nums, 3);
    std::for_each(nums.begin(), nums.end(), [](int num) {
        cout << num << " ";
    });
    cout << endl;
    return 0;
}