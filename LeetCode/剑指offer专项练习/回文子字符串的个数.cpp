// 给定一个字符串 s ，请计算这个字符串中有多少个回文子字符串。
// 具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

#include <string>
#include <vector>
#include <iostream>
using namespace std;

//Manacher算法, 返回回文半径数组
vector<int> manacher(string s) {
    //先把字符串扩充
    string str = "#";
    for(auto &ch: s) {
        str += ch;
        str += '#';
    }
    int size = str.size();
    vector<int> radius(size, 0);   //回文半径数组
    int R = -1;     //最右回文右边界的下一个位置
    int center = -1; //最右回文右边界的对称中心
    int p = 0;
    int l; 
    int r;
    for(int i = 0; i < size; i++) {
        if(i >= R) {    //如果i不在最右回文右边界里面，只能暴力试
            l = r = i;
            while(l >= 0 && r < size && str[l] == str[r]) {
                l--;
                r++;
            }
            R = r;
            center = i;
            radius[i] = r - i;
        }
        else {      //如果在里面，有三种情况
            //如果对称点的回文半径正好和左边界重合，从右边界继续向外试
            if((2 * center - i) - radius[2 * center - i] + 1 == 2 * center - R + 1) {
                radius[i] = R - i;
                r = R;
                l = 2 * i - R;
                while(l >= 0 && r < size && str[l] == str[r]) {
                    l--;
                    r++;
                    radius[i]++;
                }
                R = r;
                center = i;
            }
            //对称点的回文半径大于或者小于左边界
            else {  
                radius[i] = min(radius[2 * center - i], R - i);
            }
        }
    }
    for(auto &it: radius)
        it /= 2;
    return radius;
}

int countSubstrings(string s) {
    string str = "#";
    for(auto &ch: s) {
        str += ch;
        str += '#';
    }
    int size = str.size();
    vector<int> radius(size, 0);   
    int R = -1;   
    int center = -1; 
    int p = 0;
    int l; 
    int r;
    int res = 0;
    for(int i = 0; i < size; i++) {
        if(i >= R) {
            l = r = i;
            while(l >= 0 && r < size && str[l] == str[r]) {
                l--;
                r++;
            }
            R = r;
            center = i;
            radius[i] = r - i;
        }
        else {
            if((2 * center - i) - radius[2 * center - i] + 1 == 2 * center - R + 1) {
                radius[i] = R - i;
                r = R;
                l = 2 * i - R;
                while(l >= 0 && r < size && str[l] == str[r]) {
                    l--;
                    r++;
                    radius[i]++;
                }
                R = r;
                center = i;
            }
            else {
                radius[i] = min(radius[2 * center - i], R - i);
            }
        }
    res += radius[i]/2;
    }
    return res;
}


int main()
{   
    string s = "aaa";
    vector<int> res = manacher(s);
    for(auto &it: res)
        cout << it << " ";
    cout << endl;
    int ress = countSubstrings(s);
    cout << ress;
}