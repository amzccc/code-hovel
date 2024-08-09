// 给定一个非空字符串 s，请判断如果 最多 从字符串中删除一个字符能否得到一个回文字符串。
#include <string>
#include <iostream>
using namespace std;

bool validPalindrome(string s) {
    int l = 0; 
    int r = s.size() - 1;
    while(l <= r) {
        if(s[l] == s[r]) {
            l++;
            r--;
        }
        else {
            return sub(s, l + 1, r) || sub(s, l, r - 1);
        }
    }
    return true;
}

bool sub(string &s, int l, int r) {
    while(l < r) {
        if(s[l] == s[r]) {
            l++;
            r--;
        }
        else return false;
    }
    return true;
}
