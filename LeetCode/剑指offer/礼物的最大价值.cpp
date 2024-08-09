// 在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。
// 你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。
// 给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

#include <vector>
using namespace std;

int maxValue(vector<vector<int>>& grid) {
    for(int row  = 0; row < grid.size(); row++) {
        for(int col = 0; col < grid[0].size(); col++) {
            if(row == 0 && col == 0)
                continue;
            else if(row == 0 && col != 0)
                grid[row][col] += grid[row][col - 1];
            else if(col == 0 && row != 0)
                grid[row][col] += grid[row -1][col];
            else {
                grid[row][col] = max(grid[row - 1][col], grid[row][col - 1]);
            }
        }
    }
    return grid[grid.size() - 1][grid[0].size() - 1];
}

