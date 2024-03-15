#include <iostream>
#include <limits>       //数值极值库 另一个c++数学库是numeric
#include <string>

using namespace std;

int main() {
    //输出true或false
    cout << boolalpha;

    //整型最大值  最小值min()
    cout << "max(short): " << numeric_limits<short>::max() << endl;
    cout << "max(int): " << numeric_limits<int>::max() << endl;
    cout << "max(long): " << numeric_limits<long>::max() << endl;
    cout << endl;

    //浮点型最大值
    cout << "max(float): " << numeric_limits<float>::max() << endl;
    cout << "max(doule): " << numeric_limits<double>::max() << endl;
    cout << "max(long double): " << numeric_limits<long double>::max() << endl;
    cout << endl;

    //是否有正负号
    cout << "whether char is_signed: " << numeric_limits<char>::is_signed << endl;
    //是否有极值
    cout << " is_specialized(string): " << numeric_limits<string>::is_specialized << endl;
    cout << endl;
    //最大负有限值
    cout << "lowest(int): " << numeric_limits<int>::lowest() << endl;
    cout <<"lowest(float): " << numeric_limits<float>::lowest() << endl;
    cout << endl;

    //无穷大    
    cout << "has_inifinity(int): " << numeric_limits<int>::has_infinity << endl;
    cout << "inifinity(int): " << numeric_limits<int>::infinity() << endl; 
    cout << "has_inifinity(double): " << numeric_limits<double>::has_infinity << endl;
    cout << "inifinity(double): " << numeric_limits<double>::infinity() << endl; 
}