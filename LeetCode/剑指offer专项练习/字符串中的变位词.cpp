// 给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的某个变位词。

// 换句话说，第一个字符串的排列之一是第二个字符串的 子串 。
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

bool checkInclusion(string s1, string s2) {
    if(s1.size() > s2.size())
        return false;
    int size = s1.size();
    for(auto it = s2.begin(); it != s2.end() - size + 1; it++) {
        if(is_permutation(it, it + size, s1.begin()))
            return true;
    }
    return false;
}
