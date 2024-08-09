#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @file        manacher算法.cpp
 * @brief       查找最长回文子串
 *
 * @details
 * 1. 先用一个不会出现的字符将所有字符隔开，规避了字符串单双数的影响
 * 2. 计算每个下标位置能得到最大回文子串的长度
 *
 *  情况1 : i >= maxright   ====>>  只能中心扩散暴力搜索
 *  情况2 : i < maxright    ====>>
 *      分类1: p[mirror] < maxright - i     ====>>  p[i] = p[mirror] < maxright - i
 *      分类2: p[mirror] == maxright - i    ====>>  p[i] 至少等于maxright - i，需要继续扩散
 *      分类3: p[mirror] > maxright - i     ====>>  p[i] = maxright - i
 *
 * @param center        中心对称点
 * @param cur             当前位置
 * @param maxright        最大右边界
 * @param mirror        cur关于中心的对称点
 */
string manacher(string s) {
    string str;
    for(int i = 0; i < s.size(); i++) {
        str.push_back('#');
        str.push_back(s[i]);
    }
    str.push_back('#');
    struct Bound{
        int center = 0;
        int maxright = 0;
    };
    Bound bound;
    vector<int> matchLen(s.size(), 1);
    int cur = 0;
    while(cur < str.size() - 1) {
        // 如果当前索引在右边界之外，暴力搜索
        if(cur > bound.maxright) {
            int l = cur;
            int r = cur;
            while(l >= 0 && r < str.size() && str[l] == str[r]) {
                l--;
                r++;
            }
            bound.center = cur;
            bound.maxright = r - 1;
            matchLen[cur] = (bound.maxright - bound.center) * 2 + 1;
        }
        else {
            int mirror = bound.center - cur + bound.center;
            int mirrorleft = mirror - matchLen[mirror] / 2;
            int maxleft = bound.center - bound.maxright + bound.center;
            // 如果对称点的回文长度在边界内，当前的回文长度只会等于对称点的回文长度
            if(mirrorleft > maxleft) {
                matchLen[cur] = matchLen[mirror];
            }
            // 如果对称点的回文长度超过了边界，当前的回文长度只会等于最大边界到当前位置
            else if(mirrorleft < maxleft) {
                matchLen[cur] = (bound.maxright - cur) * 2 + 1;
            }
            // 如果正好在边界上，就继续暴力搜索
            else {
                int r = bound.maxright + 1;
                int l = cur - bound.maxright + cur - 1;
                while(l >= 0 && r < str.size() && str[l] == str[r]) {
                    l--;
                    r++;
                }
                bound.center = cur;
                bound.maxright = r - 1;
                matchLen[cur] = (bound.maxright - bound.center) * 2 + 1;
            }
        }
        cur++;
    }
    int max = 0;
    for(int i = 0; i < matchLen.size(); i++) {
        if(matchLen[i] > matchLen[max]) {
            max = i;
        }
    }
    int left = max - matchLen[max] / 2;
    return s.substr(left / 2, (matchLen[max] - 1) / 2);
}

int main() {
    string str { "abcba" };
    cout << manacher(str) << endl;

    return 0;
}