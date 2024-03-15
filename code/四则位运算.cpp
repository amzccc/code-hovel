#include <iostream>
using namespace std;

int main()
{
    // +运算：两数异或得到一个数，再两数与运算后进一位得到一个数，
    // 得到的两个数相加，也就是这两个数继续异或和与进位，直到与进位得到的数为0
  {
    cout << "7 + 11 = " << 18 << endl;
    int a = 7, b = 11;
    int temp;
    while(b != 0) {
        temp = a ^ b;   //等价于无进位相加结果
        b = (a & b) << 1;   //等价于进位结果
        a = temp;
    }
    cout << "位运算结果: " << a << endl;
  }

    //-运算：加上相反数    -a = ~a + 1  二进制中相反数等于补码取反加1
  {
    int a = 42, b = 11;
    cout << a << " - " << b << " = " << a - b << endl;
    int c = ~b;
    b = 1;
    int temp;
    while(b != 0) {
      temp = c ^ b;
      b = (c & b) << 1;
      c = temp;
    }
    while(c != 0) {
      temp = a ^ c;
      c = (a & c) << 1;
      a = temp;
    }
    cout << "位运算结果: " << a << endl;
  }

    //*运算：类似于列乘法竖式
  {
    int a = 13, b = 42;
    cout << a << " * " << b << " = " << a * b << endl;
    int res = 0;
    while(b != 0) {
        if((b & 1) != 0) {      //如果当前b最后一位是1，就把a全加到res里
            int temp;
            int aa = a;
            while(aa != 0) {    //加法位运算
                temp = res ^ aa; 
                aa = (res & aa) << 1; 
                res = temp;
            }
        }
        a <<= 1;   
        b >>= 1;
    }
    cout << "位运算结果: " << res << endl;
  }

    // /运算：将除数尽量左移，直至最大但不大于被除数，被除数减去这个数，再递归直至不能左移
    // 可以理解为乘法的逆运算，先得到和除数相乘等于被除数的那个数的最高位1的位置，再依次求下一个
  {
    int a = 42, b = 4;
    cout << a << " / " << b  << " = " << a/b << endl;
    int quotient = 0;     //商
    int remain = a;       //余数
    for(int i = 31; i > -1; i--) {    //除数左移等于被除数右移，还能避免溢出
        if((remain >> i) >= b) {
            int temp = 1 << i;    //1在商中的各位
            int temp2;
            while(temp != 0) {    //求商
                temp2 = quotient ^ temp;
                temp = (quotient & temp) << 1;
                quotient = temp2;
            }
            temp = ~(b << i);      //b左移i位后的相反数
            temp2 = 1;
            int temp3;
            while(temp2 != 0) {
                temp3 = temp ^ temp2;
                temp2 = (temp & temp2) << 1;
                temp = temp3;
            }
            while(temp != 0) {    //求余
                temp2 = remain ^ temp;
                temp = (remain & temp) << 1;
                remain = temp2;
            }
        }
    }
    //没有考虑负数情况，若引入负数需要标记结果的正负
    cout << "位运算结果: " << quotient << endl;
  }
}