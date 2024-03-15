#include <bitset>
#include <iostream>
#include <string>
#include <limits>

int main() 
{   
    using namespace std;

    cout << "267 as binary short: "
        << bitset<numeric_limits<unsigned short>::digits>(267) << endl;
    cout << "267 as binary long: "
        << bitset<numeric_limits<unsigned long>::digits>(267) << endl;
    cout << "10,000,000 with 24 bits: "
        << bitset<24>(1e7) << endl;
    //写入string
    string s = bitset<42>(12345678).to_string();
    cout << "12,345,678 with 42 bits: " << s << endl;
    //二进制转换为整型
    cout << "\"1000101011\" as number: "
        << bitset<100>("1000101011").to_ullong() << endl;
    
}