// 请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
// 输入：s = "We are happy."
// 输出："We%20are%20happy."

#include <iostream>
#include <string>
#include <set>

using namespace std;

class Solution
{
public:
    string replaceSpace(string s)
    {
        string str;
        for(char& it: s)
        {
            if(it == ' ')
            {
                str.append("%20");
            }
            else
            {   
                
                str += it;
            }
        }
        return str;
    }
};

int main()
{
    string s = "hello world";
    Solution sol;
    cout << sol.replaceSpace(s);

}