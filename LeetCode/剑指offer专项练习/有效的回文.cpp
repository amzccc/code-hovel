// 给定一个字符串 s ，验证 s 是否是 回文串 ，只考虑字母和数字字符，可以忽略字母的大小写。
// 本题中，将空字符串定义为有效的 回文串 。

#include <string>
#include <algorithm>
using namespace std;

bool isPalindrome(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    string str;
    for(auto &it: s) {
        if((it >= '0' && it <= '9') || (it >= 'a' && it <= 'z'))
            str.push_back(it);
    }
    string str2(str.rbegin(),str.rend());
    return str == str2;
}