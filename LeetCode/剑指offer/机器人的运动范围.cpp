// 地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
// 一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），
// 也不能进入行坐标和列坐标的数位之和大于k的格子。
// 例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。
// 但它不能进入方格 [35, 38]，因为3+5+3+8=19。
// 请问该机器人能够到达多少个格子？

#include <vector>
#include <iostream>
using namespace std;

void dfs(int m, int n, int k, int &res, int cur_r, int cur_c, vector<vector<bool>> &vec) {
    if(cur_r < 0 || cur_c < 0 || cur_r >= m || cur_c >= n) return;
    if(vec[cur_r][cur_c] == true) return; 
    int sum = cur_r % 10 + cur_c % 10;
    int temp = cur_r / 10;
    while(temp > 0) {
        sum += temp % 10;
        temp /= 10;
    }
    temp = cur_c / 10;
    while(temp > 0) {
        sum += temp % 10;
        temp /= 10;
    }
    if(sum > k) return;
    vec[cur_r][cur_c] = true;
    res++;
    dfs(m, n, k, res, cur_r + 1, cur_c, vec);
    dfs(m, n, k, res, cur_r, cur_c + 1, vec);
}

int movingCount(int m, int n, int k) {
    if(k == 0)  return 1;
    vector<vector<bool>> vec(m, vector<bool>(n,false));
    int res = 0;
    dfs(m, n, k, res, 0, 0, vec);
    return res;
}

int main()
{
    cout << movingCount(21, 11, 11); //167
}