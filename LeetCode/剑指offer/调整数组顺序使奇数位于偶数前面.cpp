// 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。

//双指针，类似快排
#include <iostream>
#include <vector>
using namespace std;

vector<int> exchange(vector<int>& nums)
{
    int l_ptr = 0;
    int r_ptr = nums.size() - 1;
    if(l_ptr == r_ptr)
        return nums;
    while(l_ptr <= r_ptr)
    {
        if(l_ptr == r_ptr)
            return nums;
        while((nums[l_ptr] % 2 == 1) && l_ptr < nums.size() && l_ptr < r_ptr)
            l_ptr++;
        while((nums[r_ptr] % 2 == 0) && l_ptr < r_ptr)
            r_ptr--;
        int temp = nums[l_ptr];
        nums[l_ptr] = nums[r_ptr];
        nums[r_ptr] = temp;

    }
    return nums;


}

int main()
{
    vector<int> vec{2, 1, 4, 1, 3, 6, 3};
    vec = exchange(vec);
    for(auto it: vec)
        cout << it;
}