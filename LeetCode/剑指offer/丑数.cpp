// 我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。
// 求按从小到大的顺序的第 n 个丑数。
#include <vector>
#include <numeric>
using namespace std;

int nthUglyNumber(int n) {
    vector<int> res;
    int min;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            res.push_back(1);
        }  
        else {
            min = res[i - 1] * 2;
            for(int j = 0; j < i; j++) {
                int temp2 = res[j] * 2;
                int temp3 = res[j] * 3;
                int temp5 = res[j] * 5;
                if(temp2 > res[i - 1] && temp2 < min) {
                    min = temp2;
                }
                else if(temp3 > res[i - 1] && temp3 < min) {
                    min = temp3;
                }
                else if(temp5 > res[i - 1] && temp5 < min){
                    min = temp5;
                }
            }
            res.push_back(min);
        }
    }  
    return res[n - 1];  
}

//动态规划
int nthUglyNumber(int n) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        int p2 = 1, p3 = 1, p5 = 1;
        for (int i = 2; i <= n; i++) {
            int num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5;
            dp[i] = min(min(num2, num3), num5);
            if (dp[i] == num2) {
                p2++;
            }
            if (dp[i] == num3) {
                p3++;
            }
            if (dp[i] == num5) {
                p5++;
            }
        }
        return dp[n];
    }