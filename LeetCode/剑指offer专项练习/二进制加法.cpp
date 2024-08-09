// 给定两个 01 字符串 a 和 b ，请计算它们的和，并以二进制字符串的形式输出。
// 输入为 非空 字符串且只包含数字 1 和 0。
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

string addBinary(string a, string b) {
    if(a == "0" && b == "0")
        return "0";
    int flag = 0;
    string res;
    string zero;
    if(a.size() > b.size()) {
        zero = string(a.size() - b.size(), '0');
        b = zero + b;
    }
    else if(a.size() < b.size()) {
        zero = string(b.size() - a.size(), '0');
        a = zero + a;
    }
    auto pa = a.rbegin();
    auto pb = b.rbegin();
    while(pa != a.rend() && pb != b.rend()) {
        if(flag == 0) {
            if(*pa != *pb) {
                res = "1" + res;
            }
            else {
                res = "0" + res;
                if(*pa == '1' && *pb == '1')
                    flag = 1;
            }
        }
        else {
            if(*pa != *pb) {
                res = "0" + res;
            }
            else {
                res = "1" + res;
                if(*pa == '0' && *pb == '0')
                    flag = 0;
            }
        }
        pa++;
        pb++;
    }
    
    return flag == 1? ("1"+res): res;
}

int main()
{
    string s1 = "111";
    string s2 = "1";
    cout << addBinary(s1, s2);
}