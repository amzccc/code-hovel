// 给定一个数字，我们按照如下规则把它翻译为字符串：
// 0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。
// 一个数字可能有多个翻译。
// 请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

#include <string>
#include <iostream>
using namespace std;

//动态规划，找到递推公式
int translateNum(int num) {
    string s = to_string(num);
    if(s.size() == 1)
        return 1;
    int prepre = 1;
    int pre = 1;
    int res = 0;
    for(int i = 1; i < s.size(); i++) {
        if(s.substr(i - 1, 2) >= "10" && (s.substr(i -1, 2) < "26")) {  //字符串是按位比较的。不能用>"9"
            res += prepre + pre;
        }
        else
            res += pre;
        prepre = pre;
        pre = res;
    }
    return res;
}

int main()
{
    cout << translateNum(25);
}