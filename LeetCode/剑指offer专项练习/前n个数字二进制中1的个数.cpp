// 给定一个非负整数 n ，请计算 0 到 n 之间的每个数字的二进制表示中 1 的个数，并输出一个数组。
#include <iostream>
#include <vector>
using namespace std;

vector<int> countBits(int n) {
    int index = 0;
    vector<int> res(n + 1);
    while(n > 0) {
        while((n >> index) > 0) {
            res[n] += ((n >> index) & 1);
            ++index;
        }
        index = 0;
        --n;
    }
    return res;
}

int main()
{
    for (auto it: countBits(2))
        cout << it << " ";
    cout << endl;
}