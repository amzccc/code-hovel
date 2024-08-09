// 在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，
// 每一列都按照从上到下递增的顺序排序。
// 请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
#include <vector>

using namespace std;

bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;
    for(int i = 0; i < matrix.size(); i++) {
        if(matrix[i][0] <= target && matrix[i][matrix[i].size() - 1] >= target) {
            for(auto it: matrix[i]) {
                if(it == target)
                    return true;
            }
        }
    }
    return false;
}

//O(M+N)
bool findNumberIn2DArray_2(vector<vector<int>>& matrix, int target) {
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;
    int row = 0;
    int col = 0;
    while(row < matrix.size()) {
        if(matrix[row][0] <= target && matrix[row][matrix[0].size() - 1] >= target) {
            while(col < matrix[row].size()) {
                if(matrix[row][col] == target)
                    return true;
                else if(matrix[row][col] < target) {
                    col++;
                    if(matrix[row][col] > target) {
                        col--;
                        break;
                    }
                }
                else {
                    col--;
                    if(matrix[row][col] < target) {
                        break;
                    }
                }    
            }
        }
        row++;
    }
    return false;
}