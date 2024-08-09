// 某种外星语也使用英文小写字母，但可能顺序 order 不同。字母表的顺序（order）是一些小写字母的排列。

// 给定一组用外星语书写的单词 words，以及其字母表的顺序 order，只有当给定的单词在这种外星语中按字典序排列时，返回 true；否则，返回 false。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/lwyVBB
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

bool isAlienSorted(vector<string>& words, string order) {
    unordered_map<char, int> ump;
    for(int i = 0; i < 26; i++) {
        ump.insert(make_pair(order[i], i));
    }
    int i = 1;
    while(i < words.size()) {
        if(words[i - 1].size() > words[i].size()) {
            int j = 0;
            for(; j < words[i].size(); j++) {
                if(ump[words[i - 1][j]] < ump[words[i][j]])
                    break;
                else if(ump[words[i - 1][j]] > ump[words[i][j]])
                    return false;
            }
            if(j == words[i].size())
                return false;
        }
        else {
            int j = 0;
            for(; j < words[i - 1].size(); j++) {
                if(ump[words[i - 1][j]] < ump[words[i][j]])
                    break;
                else if(ump[words[i - 1][j]] > ump[words[i][j]])
                    return false;

            }
        }
        i++;
    }
    return true;
}