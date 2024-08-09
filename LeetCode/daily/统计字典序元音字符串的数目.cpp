// 给你一个整数 n，请返回长度为 n 、仅由元音 (a, e, i, o, u) 组成且按 字典序排列 的字符串数量。

// 字符串 s 按 字典序排列 需要满足：对于所有有效的 i，s[i] 在字母表中的位置总是与 s[i+1] 相同或在 s[i+1] 之前。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/count-sorted-vowel-strings
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/*
 * 动态规划（从小到大）
 * 1.穷举
 * 2.确定边界条件
 * 3.确定递归表达式 （最难的一步）
 * 4.写出状态转移方程 
*/
#include <iostream>
#include <vector>
using namespace std;

int countVowelStrings(int n) {
    vector<int> dp(5, 1);
    //字符串元音个数为k 对应数组下标+1
    
    //n = 1时，k = 1: 1种取法; K=2:2种取法；k=3：3种取法；k=4：4种取法；k=5：5种取法
    for(int i = 1; i < 5; i++) {
        dp[i] += dp[i - 1];
    }    
    
    //n的情况总是基于n-1的状态
    //F(i, k) = F(i-1, 0) + F(i-1, 1) + ... + F(i-1, k)
    for(int i = 1; i < n; i++) {
        for(int k = 4; k >= 0; k--) {
            for(int j = k - 1; j >= 0; j--) {
                dp[k] += dp[j];
            }
        }
    }

    //对应有5个元音，长度为n的情况
    return dp[4];
}

int main()
{
    cout << countVowelStrings(3) << endl;
}