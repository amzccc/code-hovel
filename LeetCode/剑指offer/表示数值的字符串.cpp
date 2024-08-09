// 数值（按顺序）可以分成以下几个部分：
// 若干空格
// 一个 小数 或者 整数
// （可选）一个 'e' 或 'E' ，后面跟着一个 整数
// 若干空格
// 小数（按顺序）可以分成以下几个部分：
// （可选）一个符号字符（'+' 或 '-'）
// 下述格式之一：
// 至少一位数字，后面跟着一个点 '.'
// 至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
// 一个点 '.' ，后面跟着至少一位数字
// 整数（按顺序）可以分成以下几个部分：
// （可选）一个符号字符（'+' 或 '-'）
// 至少一位数字
// 部分数值列举如下：
// ["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]
// 部分非数值列举如下：
// ["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]

#include <string>
#include <regex>
#include <iostream>

using namespace std;
//正则表达式这样太慢了
bool isNumber(string s) {
    smatch m;
    if(regex_search(s, m, regex("[eE]"))) {
        if(regex_match(m.prefix().str(), regex("[[:blank:]]*[+-]?[0-9]+"))) {
            if(regex_match(m.suffix().str(), regex("[+-]?[0-9]+[[:blank:]]*")))
                return true;   
        }
        else if((regex_match(m.prefix().str(), regex("[[:blank:]]*[+-]?[0-9]+[.][0-9]*")) || 
            (regex_match(m.prefix().str(), regex("[[:blank:]]*[+-]?[0-9]*[.][0-9]+"))))) {
                if(regex_match(m.suffix().str(), regex("[+-]?[0-9]+[[:blank:]]*")))
                    return true;
            }     
    }
    else if(regex_search(s, m, regex("[.]"))) {
        if(regex_match(m.prefix().str(), regex("[[:blank:]]*[+-]?[0-9]*"))) {
            if(regex_match(m.prefix().str(), regex("[[:blank:]]*[+-]?[0-9]+"))) {
                if(m.suffix().str().empty() || regex_match(m.suffix().str(), regex("[0-9]*[[:blank:]]*")))
                    return true;
            }
            if(regex_match(m.suffix().str(), regex("[0-9]+[[:blank:]]*")))
                return true;
        }
    }
    else {
        if(regex_match(s, regex("[[:blank:]]*[+-]?[0-9]+[[:blank:]]*")))
            return true;
    }
    return false;
}

bool isnumber(string s) {
    if(s.empty() || s[0] == 'e' || s[0] == 'E')
        return false;
    int pre = 0;
    int suf = 0;
    int index = 0;
    int end = s.size();
    while(s[index] == ' ') {
        index++;
    }
    while(end > index && s[end - 1] == ' ')
        end--;
    while(index < end && s[index] != 'e' && s[index] != 'E' && s[index] != '.') {
        if(s[index] == '+' || s[index] == '-') {
            if(pre != 0)
                return false;
            index++;
        }
        else if(s[index] >= '0' && s[index] <= '9') {
            pre++;
            index++;
        }
        else if(s[index] == ' ') 
            break;
        else return false;
    }
    if(index == end) {
        if(pre == 0)
            return false;
        return true;
    }
    if(s[index] == 'e' || s[index] == 'E') {
        index++;
        while(index < end) {
            if(s[index] == '+' || s[index] == '-') {
                if(suf != 0)    return false;
                index++;
            }
            else if(s[index] >= '0' && s[index] <= '9') {
                suf++;
                index++;
            }
            else if(s[index] == ' ') 
                break;
            else return false;
        }
        if(index == end) {
            if(suf == 0)
                return false;
            return true;
        }
    }
    if(s[index] == '.') {
        index++;
        while(index < end && s[index] != 'e' && s[index] != 'E') {
            if(s[index] >= '0' && s[index] <= '9') {
                suf++;
                index++;
            }
            else if(s[index] == ' ') 
                break;
            else return false;
        }
        if(index == end) {
            if(pre == 0 && suf == 0)
                return false;
            return true;
        }
        if(s[index] == 'e' || s[index] == 'E') {
            pre += suf;
            suf = 0;
            if(pre == 0)    return false;
            index++;
            while(index < end) {
                if(s[index] == '+' || s[index] == '-') {
                    index++;
                }
                else if(s[index] >= '0' && s[index] <= '9') {
                    suf++;
                    index++;
                }
                else if(s[index] == ' ')
                    break;
                else return false;
            }
        }
    }
    return suf > 0? true:false;
}

int main()
{
    string s = ".2e81";
    cout << isnumber(s);
}