// 一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。
// 求该青蛙跳上一个 n 级的台阶总共有多少种跳法。

#include <iostream>
 
using namespace std;

//结果和斐波那契数列是一样的，很神奇，两者联系是什么呢？
/*
    这样理解：最后一步总可以分为跳1阶或者2阶两种，
    所以f(n) = f(n - 1) + f(n - 2)
    n-1就是最后跳一阶，n-2就是最后跳2阶，然后可以继续递归！
    本质是斐波那契数列！
*/
int numWays(int n)
{
     if(n == 0)
            return 1;
        else if(n == 1)
            return 1;
        else
        {     
            int prepre = 1; 
            int pre = 1;
            int result = 0;
            for(int i = 2; i <= n; i++)
            {
                result = prepre + pre;
                prepre = pre;
                pre = result;
            }
            return result;
        }
}

//test
int main()
{
    cout << numWays(20);
    int i =0;   
}