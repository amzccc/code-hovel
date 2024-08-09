// 给定两个字符串 s 和 p，找到 s 中所有 p 的 变位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

// 变位词 指字母相同，但排列不同的字符串。

#include <vector>
#include <string>
using namespace std;

vector<int> findAnagrams(string s, string p) {
    int size = p.size();
    int max = s.size();
    if(size > max)
        return {};
    vector<int> res;
    vector<int> base(26, 0);
    for(auto &it: p) {
        base[(int)(it - 'a')]++;
    }
    vector<int> comp = base;
    int sum = 0;
    for(int i = 0; i < max - size + 1; i++) {
        for(int j = i; j < i + size; j++) {
            comp[(int)(s[j] - 'a')]--;
        }
        for(auto &it: comp) {
            sum += it;
            if(sum != 0)
                break;
        }
        if(sum == 0)
            res.push_back(i);
        comp = base;
        sum = 0;
    }
    return res;
}