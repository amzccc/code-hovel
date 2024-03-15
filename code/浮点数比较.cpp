#include <iostream>
#include <iomanip>
#include <bitset>

using namespace std;

int main() {
    float f = 1.23456789;
    cout << f << endl;
    bitset<32> fbits(*(unsigned*)&f);
    cout << fbits << endl;

    double d = 1.23456789;
    cout << d << endl;
    bitset<64> dbits(*(unsigned long long*) & d);
    cout << dbits << endl;
    unsigned long long dd = dbits.to_ullong();
    cout << *(double*)&dd << endl;

    cout << "*********************\n";
    cout << "double equal op\n";
    double num1 = 1.23456789;
    cout.setf(ios::fixed);
    cout << "num1 = " << setprecision(10) << num1 << endl;
    double num2 = 1.23456789;
    cout << "num2 = " << setprecision(10) << num2 << endl;
    bitset<64> num1_bit(*(unsigned long long*) & num1);
    bitset<64> num2_bit(*(unsigned long long*) & num2);
    cout << "num1 == num2: ";
    bitset<64> res = num1_bit ^ num2_bit;
    
    cout << boolalpha << res.none() << endl;
    return 0;
}