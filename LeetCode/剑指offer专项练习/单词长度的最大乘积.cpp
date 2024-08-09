// 给定一个字符串数组 words，请计算当两个字符串 words[i] 和 words[j] 不包含相同字符时，它们长度的乘积的最大值。
// 假设字符串中只包含英语的小写字母。
// 如果没有不包含相同字符的一对字符串，返回 0。
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

int maxProduct(vector<string>& words) {
    int max = 0;
    int size = 0;
    unordered_set<char> set;
    for(int i = 0; i < words.size(); i++) {
        for(auto it: words[i])
            set.insert(it);
        for(int j = i + 1; j < words.size(); j++) {
            size = words[j].size();
            for(auto it: words[j]) {
                if(set.find(it) != set.end()) {
                    size = 0;
                    break;
                }
            }
            max = (max > size * words[i].size()? max:size * words[i].size());
        }
        set.clear();
    }
    return max;
}

int main()
{
    vector<string> words = {"eae","ea","aaf","bda","fcf","dc","ac","ce","cefde","dabae"};
    cout << maxProduct(words);
}