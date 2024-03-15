//KMP算法，用于匹配字符串

//记录字符串的每个位置的相同前缀和后缀子字符串长度（不包括本身）
//利用next_arr[]记录，规定第一位置为-1，第二位置为0
//e.g.  "a a a b a a b"
//     [-1 0 1 2 0 1 2]

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getNextArray(string m);

int KMP (string s, string m) {
    //s是较长字符串，m是要匹配的字符串
    if(s.size() == 0 || m.size() == 0 || s.size() < m.size()){
        return -1;
    }
    vector<int> arr_s;
    vector<int> arr_m;
    vector<int> nextArr = getNextArray(m);    //记录匹配字符串对应的数组
    int index_s = 0;
    int index_m = 0;
    //O(N)
    while (index_s < s.size() && index_m < s.size()) {
        //对应位置匹配就同时++
        if(s[index_s] == m[index_m]) {
            index_s ++;
            index_m ++;
        }
        //m到头了也没匹配上，那么就只能s向后移动了
        else if (index_m == 0) {
            index_s ++;
        }
        //如果没匹配上，根据next_arr记录的位置向前跳
        else {
            index_m = nextArr[index_m];
        }
    }
    //最终是哪个下标先越界，index_m越界说明找到了子字符串，index_s越界了说明没找到
    return  index_m == m.size()?  index_s - index_m: -1;
}


/**
 *@brief 计算子串每个位置的最长匹配前后缀的长度
 * 
 * @param m     要计算的子串
 * @param next_arr 返回的长度数组,实际上也是记录了匹配到的最长前缀的后面一个元素下标
 * @param index     当前要计算的下标位置
 * @param cn        index的前一个字符最长匹配前后缀的长度，也就是index - 1位置对应的最长匹配前后缀的前缀的后面一个元素的下标
 * @return vector<int>
 */
vector<int> getNextArray(string m) {
    if(m.size() == 1) {
        return vector<int> {-1};
    }
    else if(m.size() == 2) {
        return vector<int> {-1, 0};
    }
    
    vector<int> next_arr{-1, 0};    //前两个位置规定为-1和0

    //next_arr数组可以用动态数组的方法
    //i-1位置记录的地址上的字符如果和i位置上的字符相同，第i位置记录的数值就应该是第i-1位置的数值加一；
    //如果不相同就继续往前跳,直到找到一个位置上的字符和第i-1位置上的相同，第i位置上的数值就等于该位置上的数值加一，如果到头了也不等，就等于零
    int index = 2;  //第i位置下标
    int cn = 0;     //哪个位置和i-1处的字符比较
    while (index < m.size()) {
        if (m[index - 1] == m[cn]) {    //如果相等
            next_arr.push_back(cn + 1);
            cn = next_arr.back();       //下个比较的位置
            ++index;    //开始下个位置
        }
        else if (cn > 0) {  //如果不相等，且没到头，cn向前跳
            cn = next_arr[cn];
        }
        else {  //到头了
            next_arr.push_back(0);
            ++index;
        }
    }
    return next_arr;
}

int main()
{
    string s = "abbabbskcabbabbskz";
    string m = "abbabbskz";
    cout << KMP(s, m) << endl;
}