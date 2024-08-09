// 在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。
#include <string>
#include <unordered_map>
using namespace std;

char firstUniqChar(string s)
{   
    if(s.empty())
        return ' ';
    unordered_map<char, int> mp;
    for(auto it: s)
    {
        if(mp.find(it) == mp.end())
        {
            mp.insert(make_pair(it, 1));
        }
        else
            mp[it]++;
    }
    for(auto it: s)
    {
        if(mp[it] == 1)
            return it;
    }
    return ' ';
}