// 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。

// 给你一个可能存在 重复 元素值的数组 numbers ，
// 它原来是一个升序排列的数组，并按上述情形进行了一次旋转。
// 请返回旋转数组的最小元素。
// 例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一次旋转，该数组的最小值为1.

#include <iostream>
#include <vector>

using namespace std;

int minArray(vector<int>& numbers)
{
    int result = numbers[0];
    for(auto it: numbers)
    {
        if(result > it)
            result = it;
    }
    return result;
}