// 输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
// 为简单起见，标点符号和普通字母一样处理。
// 例如输入字符串"I am a student. "，则输出"student. a am I"。

#include <string>
#include <iterator>
#include <iostream>
using namespace std;

string reverseWords(string s)
{   
    string res;
    int begin = s.size() - 1;
    if(begin < 0)
        return res;
    int num = 0;
    while(begin >= 0)
    {
        while(begin >= 0 && s[begin] == ' ')
        {
            begin--;
        }
        if(begin < 0)
            break;
        while(begin >= 0 && s[begin] != ' ')
        {
            begin--;
            num++;
        }
        res += s.substr(begin + 1, num);
        res += ' ';
        num = 0;
    }
    if(!res.empty())
        res.pop_back();
    return res;
}


//test
int main()
{
    string s= "a";
    cout << reverseWords(s);
}