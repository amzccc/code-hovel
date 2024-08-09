// 输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。
// 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
// 输出：[1,2,3,6,9,8,7,4,5]
#include <vector>
#include <iostream>
using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix)
{
    int rb = 0;
    int cb = -1;
    int re = matrix.size() - 1;
    int ce = matrix[0].size() - 1;
    vector<int> result;

    while(rb <= re && cb <= ce)
    {   
        cb += 1;
        for(int i = cb; i <= ce; i++)       //1
        {
            result.push_back(matrix[rb][i]);
        }
        // cout << rb << " " << cb << " " << re << " " << ce << endl;
        // cout << "vector:";
        // for(auto it: result)
        //     cout << it << " ";
        // cout << endl;
        if(rb > re || cb > ce)
            break;

        rb += 1;
        for(int i = rb; i <= re; i++)       //2
        {
            result.push_back(matrix[i][ce]);
        }
        // cout << rb << " " << cb << " " << re << " " << ce << endl;
        // cout << "vector:";
        // for(auto it: result)
        //     cout << it << " ";
        // cout << endl;
        if(rb > re || cb > ce)
            break;

        ce -= 1;
        for(int i = ce; i >= cb; i--)       //3
        {
            result.push_back(matrix[re][i]);
        }
        // cout << rb << " " << cb << " " << re << " " << ce << endl;
        // cout << "vector:";
        // for(auto it: result)
        //     cout << it << " ";
        // cout << endl;
        if(rb > re || cb > ce)
            break;

        re -= 1;
        for(int i = re; i >= rb; i--)       //4
        {
            result.push_back(matrix[i][cb]);
        }
        // cout << rb << " " << cb << " " << re << " " << ce << endl;
        // cout << "vector:";
        // for(auto it: result)
        //     cout << it << " ";
        // cout << endl;
        if(rb > re || cb > ce)
            break;
    }
    return result;
}

// test
int main()
{
    //vector<vector<int>> src1{};
    vector<vector<int>> src = {{1, 2 ,3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}; 
    vector<int> s = spiralOrder(src);
}