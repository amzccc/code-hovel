#include <iostream>
#include <iomanip>
#include <codecvt>          //提供编码转换的库
#include <string>
#include <locale>           //本地
using namespace std;

wstring utf8_to_wstring(const string &str);
string wstring_to_utf8 (const wstring &str);

int main() 
{
    //控制器概览
    /* 
    ws                  读入并忽略空格
    skipws              执行>>时忽略前导空格
    noskipws            不忽略
    unitbuf             每次写操作后清空输出缓冲区
    nounitbuf           
    setiosflags(flags)  将flags设为格式标志
    resetiosflags(m)    清除m中所有flags
    setw(val)           设置下次输出和输入val时的栏宽
    serfill(c)          用字符c填充
    left                数值靠左
    right
    internal            正负号靠左，数值靠右
    boolalpha           bool值以文本输出
    noboolalpha     
    showpos             正值强制带加号
    noshowpos           
    uppercase           对于数值强制使用大写字母
    nouppercase         强制使用小写
    oct                 八进制
    dec                 十进制
    hex                 十六进制
    showbase            显示数值的基数
    noshowbase
    showpoint           总是为浮点数写出小数点
    noshowpoint         
    setprecision(val)   使用浮点数精度，将val改设新值
    fixed               浮点数使用十进制
    scientific          浮点数使用科学计数表示
    hexfloat            浮点数使用十六进制科学表示法
    defaultfloat        使用常规浮点数表示
    put_time(val, fmt)  使用格式fmt写入date/time值
    get_time(val, fmt)  使用格式fmt读time/date值
    put_money(val)
    put_money(val. intl)    根据intl的货币符号写出货币值
    get_money(val)
    get_money(val, intl)
    */
   //格式标志
   /*
    setf(flags)         添设flags flag，返回所有flag的先前状态
    serf(flags, grp)   添设分组grp中的flags flag，返回所有flag的先前状态
    unsetf(flags)       清除flags
    flags(flags)        返回所有目前设置的format flag
    flags(flags)        将flags设为新的flag，返回所有flag的先前状态
    copyfmt(stream)     复制stream中所有格式定义

    setiosflags(flags)  将flags设为format flag
    resetiosflags(mask) 清除mask所标示的一组flag
   */
    // width()          返回当前栏宽
    // width(val)       将栏宽设置为val，并返回之前栏宽

    string s = "你好";
    wstring s2 = utf8_to_wstring(s);
    wstring s3 = L"中国";
    cout << s << endl; 
    wcout << s2 << endl;        //???
}
//将utf-8编码格式的string转换为wstring
wstring utf8_to_wstring(const string &str) {
    wstring_convert<codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
}
//将wstring转换为utf-8编码格式
string wstring_to_utf8 (const wstring &str) {
    wstring_convert<codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
}

//编码格式不是utf-8时
// string wstring_to_string(const wstring &str, const string &locale)
// {
//     typedef codecvt_byname<wchar_t, char, mbstate_t> F;
//     std::wstring_convert<F> myconv(new F(locale));
 
//     return myconv.to_bytes(str);
// }
 
// wstring string_to_wstring(const string &str, const string &locale)
// {
//     typedef codecvt_byname<wchar_t, char, mbstate_t> F;
//     static wstring_convert<F> myconv(new F(locale));
 
//     return myconv.from_bytes(str);
// }
