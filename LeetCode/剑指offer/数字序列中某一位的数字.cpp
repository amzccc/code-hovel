// 数字以0123456789101112131415…的格式序列化到一个字符序列中。
// 在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。
// 请写一个函数，求任意第n位对应的数字。
#include <algorithm>
#include <numeric>
#include <string>
#include <iostream>
using namespace std;

int findNthDigit(int n) {
    if(n >= 0 && n <= 9)
        return n;
    int digit = 1;
    int start = 1;
    while(n > 9*start*digit) {
        n -= 9*start*digit;
        start *= 10;
        digit++;
    } 
    int num = start + (n - 1) / digit;   
    int count = (n- 1) % digit;
    string s = to_string(num);
    int res = s[count] - '0';   //要减‘0’，字符型转换成整型是取ASCII
    return res;
}

