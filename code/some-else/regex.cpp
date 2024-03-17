#include <regex>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void out (bool b) {
    cout << (b? "found": "not found") << endl;
}

int main()
{   
    regex reg1("<.*>.*</.*>");      //.表示换行外的任意字符  *表示前面一个字符不限制出现次数
    bool found = regex_match ("<tag>value</tag>", reg1);
    out(found);

    regex reg2("<(.*)>.*</\\1>");       // (...)括号内看作一个整体group， \1表示第一个group
    found = regex_match ("<tag>value</tag>", reg2);
    out(found);

    regex reg3 ("<\\(.*\\)>.*</\\1>", regex_constants::grep);   //第二个参数表示选择的文法， 这里选择的grep文法必须以额外的反斜线将group包裹起来
    found = regex_match ("<tag>value</tag>", reg3);
    out(found);

    found = regex_match ("<tag>value</tag>", regex("<(.*)>.*</\\1>"));
    out(found);
    cout << endl;

    //regex_match()和regex_search()对比
    //regex_match() ：是否整个字符序列匹配正则表达式
    //regex_search(): 是否部分字符序列匹配正则表达式
    found = regex_match ("XML tag: <tag>value</tag>", regex("<(.*)>.*</\\1>"));     //false
    out(found);

    found = regex_match ("XML tag: <tag>value</tag>", regex(".*<(.*)>.*</\\1>.*"));     //true
    out(found);

    found = regex_search ("XML tag: <tag>value</tag>", regex("<(.*)>.*</\\1>"));        //true
    out(found);

    found = regex_search ("XML tag: <tag>value</tag>", regex("<(.*)>.*</\\1>"));        //true
    out(found);
    cout << "------------------------------------------------------------\n";

    string data = "XML tag: <tag-name>the value</tag-name>.";
    cout << "data:\t\t\t" << data << "\n\n";
    smatch  m;  //返回匹配的细节 
    bool found1 = regex_search(data, m, regex("<(.*)>(.*)</(\\1)>"));   //匹配到的结果传递给m
    //输出匹配的细节
    cout << "m.empty():\t\t" << boolalpha << m.empty() << endl;
    cout << "m.size():\t\t" << m.size() << endl;
    if(found1) {
        cout << "m.str():\t\t" << m.str() << endl;
        cout << "m.length():\t\t" << m.length() << endl;
        cout << "m.position():\t\t" << m.position() << endl;
        cout << "m.prefix().str():\t" << m.prefix().str() << endl;
        cout << "m.suffix().str():\t" << m.suffix().str() << endl;

        //遍历所有的匹配(使用匹配索引)
        for(int i = 0; i < m.size(); i++) {
            cout << "m[" << i << "].str()\t\t" << m[i].str() << endl;
            cout << "m.str(" << i << "):\t\t" << m.str(i) << endl;
            cout << "m.positon(" << i <<"):\t\t" << m.position(i) << endl;
        }
        cout << endl;
        //使用迭代器遍历
        cout << "matches:" << endl;
        for(auto pos = m.begin(); pos != m.end(); pos++) {
            cout << " " << *pos << " ";
            cout << "(length: " << pos->length() << ")" << endl;
        }
    }
    cout << "------------------------------------------------------\n";
    string data2 = "<person>\n"" <first>Nico</first>\n"" <last>Josuttis</last>\n""</person>\n";
    regex reg("<(.*)>(.*)</(\\1)>");

    //迭代器遍历所有匹配
    sregex_iterator pos(data2.cbegin(), data2.cend(), reg);
    sregex_iterator end;
    for(; pos != end; pos++) {
        cout << "match:\t " << pos->str() << endl;
        cout << "tag:\t " << pos->str(1) << endl;
        cout << "value:\t " << pos->str(2) << endl;
    }

    //使用正则迭代器在算法中将每个匹配的子串作为元素处理
    sregex_iterator beg(data.cbegin(), data.cend(), reg);
    for_each(beg, end, [](const smatch &m) {
        cout << "match:\t " << m.str() << endl;
        cout << "tag:\t " << m.str(1) << endl;
        cout << "value:\t " << m.str(2) << endl;
        });
    cout << "---------------------------------------\n";

    //使用regex_token_iterator处理不在子序列的内容
    //-1表示对匹配之间的子序列感兴趣；0表示对每个匹配子序列感兴趣；n表示对第n个匹配子序列感兴趣
    sregex_token_iterator pos2(data2.cbegin(), data2.cend(), reg, {0,2}); //{0,2}表示在意整个匹配段和第二个子序列
    sregex_token_iterator end2;
    for(; pos2 != end2; pos2++) {
        cout << "match:\t " << pos2->str() << endl;
    }
    cout << endl;
    string names = "nico, jim, helmut, paul, tim, john paul, rita";
    regex sep("[ \t\n]*[,;.][ \t\n]*");
    sregex_token_iterator p (names.cbegin(), names.cend(), sep, -1);
    sregex_token_iterator e;
    for(; p != e; p++) {
        cout << "name:\t " << *p << endl;
    }
    cout << "--------------------------------------\n";
    //用于替换的正则表达式
    //替换匹配段并打印
    cout << regex_replace(data2, reg, "<$1 value =\"$2\"/>") << endl;   //$表示匹配的子序列
    //use sed syntax
    cout << regex_replace(data2, reg, "<\\1 value =\"\\2\"/>", regex_constants::format_sed) << endl;;
    string res2;
    regex_replace(back_inserter(res2), data2.begin(), data.end(), reg, "<$1 value=\"$2\"/>", 
                    regex_constants::format_no_copy | regex_constants::format_first_only);
    cout << res2 << endl;
}