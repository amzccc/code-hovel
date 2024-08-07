// 输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
// 序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。
#include <iostream>
#include <vector>
using namespace std;

//滑动窗口
vector<vector<int>> findContinuousSequence(int target)
{
    int i = 1; // 滑动窗口的左边界
    int j = 1; // 滑动窗口的右边界
    int sum = 0; // 滑动窗口中数字的和
    vector<vector<int>> res;

    while (i <= target / 2) 
    {
        if (sum < target) 
        {
            // 右边界向右移动
            sum += j;
            j++;
        } 
        else if (sum > target) 
        {
            // 左边界向右移动
            sum -= i;
            i++;
        } 
        else 
        {
            // 记录结果
            vector<int> arr;
            for (int k = i; k < j; k++) 
            {
                arr.push_back(k);
            }
            res.push_back(arr);
            // 左边界向右移动
            sum -= i;
            i++;
        }
    }
    return res;
}

//test
int main()
{
    vector<vector<int>> s = findContinuousSequence(9);
    system("pause");
    return 0;
}