// 输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。
// 如果有多对数字的和等于s，则输出任意一对即可。

#include <vector>
#include <iostream>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target)
{   
    int l_ptr = 0;
    int r_ptr = nums.size() -1;
    while(l_ptr < r_ptr)
    {
        if(target - nums[l_ptr] > nums[r_ptr])
            l_ptr++;
        else if(target - nums[l_ptr] < nums[r_ptr])
            r_ptr--;
        else
            return vector<int> {nums[l_ptr], nums[r_ptr]};
    }
    return {};
}


//test
int main()
{
    vector<int> v{2, 7, 11, 15};
    vector<int> r =twoSum(v, 9);
    cout << r[0] << endl;
    cout << r[1] << endl;
}