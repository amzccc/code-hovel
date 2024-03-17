#include <iostream>
#include <string>
#include <string_view>

using namespace std;

string gbk2utf8(string_view gbk);

string utf82gbk(string_view utf8);

int main() {
    char ch = 0x10;
    cout << (ch >> 1) << endl;
    cout << (int)ch << endl;

    return 0;
}

/**
 *@brief
 *  gbk编码：固定2字节
 *      第一个字节0xA1~0xF7(10100001 ~ 11110111)
 *      第二个字节0xA1~0xFE(10100001 ~ 11110111)
 *
 *  utf-8编码：一至四字节不定
 *      单字节 0xxxxxxx
 *      两字节 110xxxxx 10xxxxxx
 *      三字节 1110xxxx 10xxxxxx 10xxxxxx
 *      四字节 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 *  方法：将unicode码点作为gbk和utf-8的中介
 */

string gbk2utf8(string_view gbk) {
    string res;
    short unicode_point = 0;
    for(int i = 0; i < gbk.size();) {
        char high = gbk[i];
        if((high >> 7) == 0) {
            unicode_point = high;
            i++;
        }
        else {
            char low = gbk[i + 1];
            unicode_point = (high - 0xA1) * 94 + (low - 0xA1) + 0x4E00;
            i += 2;
        }
        if(unicode_point < 0x80) {
            
        }
        else if(unicode_point < 0x800) {

        }
        else if(unicode_point < 0x10000) {

        }
        else if(unicode_point < 0x110000) {

        }
        else {
            cout << "transform failed\n";
            return {};
        }
    }
    return res;
}

string utf82gbk(string_view utf8) {
    string res;

    return res;
}