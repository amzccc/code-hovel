#include <iostream>
#include <string>
#include <format>   // c++20 支持字符串的格式化
#include <cmath>

using namespace std;

int main() {
    string str {format("c++20 format int {}, char {}", 42, 'c')};
    cout << str << endl;
    string str2;
    format_to(back_inserter(str2), "init int[{}], float[{}]", 42, 3.14);
    cout << str2 << endl;

    // 可以手动指定下标, 但是不能混合使用自动和手动
    string str3 = format("fist =[{1}], second = [{0}]", 1, 0);
    cout << str3 << endl;

    string tmp_fmt{ "hello, {1}! there is number {0}" };
    string name{ "xiaoming" };
    int num = 42;
    string str4 = vformat(tmp_fmt, make_format_args(42, name));
    cout << str4 << endl;

    // format格式控制   :[[fill]align][sign][#][0][width][.precision][type] 都是可选的
    // width        ->      指定字段的最小宽度
    // [fill]align  ->      [fill]指定占位符的填充格式字符，align表示fill填充的字符的对齐方式, <左对齐，^居中，>右对齐
    str = format("fill_, align 左对齐, width = 9, string = |{:_<9}|", 42);
    cout << str << endl;
    str = format("fill~, align 居中, width = 9, string = |{:~^9}|", 42);
    cout << str << endl;
    str = format("fill+, align 右对齐, width = 9, string = |{:+>9}|", 42);
    cout << str << endl;
    // sign         ->      数值符号显示，+显示正负号，-只显示负号（默认）,空格表示正数显示空格，负数显示负号
    // #            ->      显示前缀 0b、0x等，浮点数显示小数点
    // 0            ->      补零，若指定对齐方式则失效
    // [type]       ->      指定输出类型，b/B（二进制），x/X（小写16进制），o（8进制），
    //                      e/E（浮点型科学计数），f/F（固定精度）,g/G（指数的通用表示法），a/A（16进制表示法）
    // .precision   ->      指定浮点数小数位数，和字符串输出字符数
    double pi = 3.14159265354;
    cout << format("int type, sign +, type x, with 0 |{:+010x}|", 42) << endl;
    cout << format("int type, sign +, type X, with # |{:+#10X}|", 42) << endl;
    cout << format("double type,  type e, precision = 3, |{:^#10.3e}|", pi) << endl;

    // 格式的参数也可以动态指定
    cout << "动态指定格式参数\n";
    string fmt{"double type |{0:^{2}.{1}}|"};
    str = vformat(fmt, make_format_args(pi, 10, 20));
    cout << str << endl;
    return 0;
}