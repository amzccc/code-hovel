// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长连续子字符串 的长度。

#include <string>
#include <unordered_map>
using namespace std;

int lengthOfLongestSubstring(string s) {
    int res = 0;
    int size = s.size();
    unordered_map<char,int> mp;
    int l_ptr = 0;
    int r_ptr = 0;
    while(r_ptr < size && l_ptr <= r_ptr) {
        if(mp.find(s[r_ptr]) == mp.end() || mp.find(s[r_ptr])->second < l_ptr) {
            mp[s[r_ptr]] = r_ptr;
            r_ptr++;
        }
        else {
            if(res < r_ptr - l_ptr)
                res = r_ptr - l_ptr;
            l_ptr = mp.find(s[r_ptr])->second + 1;
        }
    }
    return max(res, r_ptr - l_ptr);
}