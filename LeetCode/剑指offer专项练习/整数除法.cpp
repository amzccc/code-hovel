// 给定两个整数 a 和 b ，求它们的除法的商 a/b ，要求不得使用乘号 '*'、除号 '/' 以及求余符号 '%' 。
#include <algorithm>
#include <iostream>
#include <limits>
using namespace std;

int divide(int a, int b) {
    if(a == numeric_limits<int>::min()) {   //需要讨论被除数是整型极限的情况
        if(b == -1)
            return numeric_limits<int>::max();
        else if(b == 1)
            return a;
    }
    bool sign = false;
    if((a < 0 && b > 0) || (a > 0 && b < 0))
        sign = true;
    int res = 0;
    a = abs(a);
    b = abs(b);
    for(int i = 31; i > -1; i--) {
        if((a >> i) >= b) {
            res += (1 << i);
            a = a - (b << i);
        }
    }
    return sign? ~res + 1: res; 
}

int main()
{
    //cout << divide(-2147483648, -1);
    int a = abs(-2147483648);
    cout << a;
}