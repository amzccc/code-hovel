// 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。
// 输入n，打印出s的所有可能的值出现的概率。
// 你需要用一个浮点数数组返回答案，
// 其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。
#include <vector>
#include <iostream>
using namespace std;

vector<double> dicesProbability(int n) {
    vector<vector<double>> res;
    vector<double> base (6, 1.0/6.0);
    res.push_back(base);
    int psb;
    for(int i = 1; i < n; i++) {        //i+1 表示骰子个数
        psb = 5 * (i + 1) + 1;
        res.push_back(vector<double> (psb, 0));
        for(int j = 0; j <= psb; j++) {     //j表示当前骰子数组的下标，j+i+1为对应的点数
            for(int k = 0; k < res[i - 1].size(); k++) {    //k表示i-1个骰子时，点数数组的下标
                if((j - k) >= 0 && (j - k) < 6) {
                    res[i][j] += (res[i - 1][k] * base[j - k]);
                }
            }
        }
    }
    return res[n - 1];
}


int main()
{
    vector<double> res = dicesProbability(1);
    for(auto it: res)
        cout << it <<" ";
}