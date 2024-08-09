// 给定一个二维矩阵 matrix，以下类型的多个请求：
// 计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1) ，右下角为 (row2, col2) 。
// 实现 NumMatrix 类：
// NumMatrix(int[][] matrix) 给定整数矩阵 matrix 进行初始化
// int sumRegion(int row1, int col1, int row2, int col2) 返回左上角 (row1, col1) 、右下角 (row2, col2) 的子矩阵的元素总和。
#include <vector>
using namespace std;

class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        swap(sum, matrix);
        for(int i = 1; i < col; i++)
            sum[0][i] += sum[0][i - 1];
        for(int i = 1; i < row; i++)
            sum[i][0] += sum[i - 1][0];
        for(int i = 1; i < row; i++) {
            for(int j = 1; j < col; j++)
                sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int res = 0;
        if(row1 != 0 && col1 != 0) {
            res = sum[row2][col2] - sum[row1 - 1][col2] - sum[row2][col1 - 1] + sum[row1 - 1][col1 - 1];
        } 
        else {
            if(row1 != 0 && col1 == 0)
                res = sum[row2][col2] - sum[row1 - 1][col2];
            else if(row1 == 0 && col1 != 0)
                res = sum[row2][col2] - sum[row2][col1 - 1];
            else    
                res = sum[row2][col2];
        }
        return res;
    }

private:
    vector<vector<int>> sum;
};