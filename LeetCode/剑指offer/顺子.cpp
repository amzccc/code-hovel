// 从若干副扑克牌中随机抽 5 张牌，判断是不是一个顺子，即这5张牌是不是连续的。
// 2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。A 不能视为 14。

#include <vector>
#include <unordered_set>
using namespace std;

bool isStraight(vector<int>& nums)
{
    int zero_num = 0;
    int min = 14;
    int max = 0;
    unordered_set<int> index;
    for(auto it : nums)
    {   
        if(it == 0)
            continue;
        if(index.find(it) != index.end())
            return false;
        else
            index.insert(it);
        if(min > it)
            min = it;
        if(max < it)
            max = it;
    }
    return (max - min) <= 4;
}