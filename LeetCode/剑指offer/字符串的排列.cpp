// 输入一个字符串，打印出该字符串中字符的所有排列。
// 你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

vector<string> permutation(string s) {
    if(s.empty())
        return {};
    if(s.size() == 1)
        return vector{s};
    vector<string> res;
    dfs(s, 0, res);
    return res;
}
//全排列：做出操作后递归，然后再取消操作
void dfs(string s, int x, vector<string> &res) {
    if(x == s.size() -1){
        res.push_back(s);
        return;
    }
    unordered_set<char> st;
    for(int i = x; i < s.size(); i++) {
        if(st.find(s[i]) != st.end())
            continue;
        st.insert(s[i]);
        swap(s[i], s[x]);
        dfs(s, x + 1, res);
        swap(s[i], s[x]);
    }
}