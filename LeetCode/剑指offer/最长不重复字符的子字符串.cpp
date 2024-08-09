// 请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。
#include <string>
#include <unordered_set>
using namespace std;

int lengthOfLongestSubstring(string s) {
    if(s.empty())
        return 0;
    int right = -1;
    int count = 1;
    unordered_set<char> index;
    for(int left = 0; left < s.size(); left++) {
        if(left != 0)
            index.erase(s[left - 1]);
        while(right + 1 < s.size() && index.find(s[right + 1]) == index.end()) {
            right++;
            index.insert(s[right]);
        }
        count = max(count, right - left + 1);
    }
    return count;
}