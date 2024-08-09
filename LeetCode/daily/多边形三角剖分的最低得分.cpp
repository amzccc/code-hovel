// 你有一个凸的 n 边形，其每个顶点都有一个整数值。给定一个整数数组 values ，其中 values[i] 是第 i 个顶点的值（即 顺时针顺序 ）。

// 假设将多边形 剖分 为 n - 2 个三角形。对于每个三角形，该三角形的值是顶点标记的乘积，三角剖分的分数是进行三角剖分后所有 n - 2 个三角形的值之和。

// 返回 多边形进行三角剖分后可以得到的最低分 。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/minimum-score-triangulation-of-polygon
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。\

#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;


//动态规划+记忆化搜索
int minScoreTriangulation(vector<int>& values) {
    unordered_map<int, int> memo;   //记录搜索过的值
    int n = values.size();

    // i，j代表多边形上的两个顶点，然后再找到另一个顶点k就构成了一个三角型
    // 这样就把多边形分成了三个部分：
    // 1. i,k,j构成的三角型
    // 2. 左边的多边形
    // 3. 右边的多边形
    // 然后继续递归左边的多边形和右边的多边形
    function<int(int, int)> dp = [&](int i, int j) -> int { //捕获了数组values和n
            if (i + 2 > j) {
            return 0;
        }
        if (i + 2 == j) {
            return values[i] * values[i + 1] * values[j];
        }
        int key = i * n + j;    //key值类比二维数组下标
        if (!memo.count(key)) {
            int minScore = INT_MAX;
            for (int k = i + 1; k < j; k++) {
                minScore = min(minScore, values[i] * values[k] * values[j] + dp(i, k) + dp(k, j));
            }
            memo[key] = minScore;
        }
        return memo[key];   //等于return二维数组memo[0][j]
    };

    return dp(0, n - 1);
}
