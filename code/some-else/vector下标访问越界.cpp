#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
using namespace std;

int main()
{
    vector<int> vec;
    for(int i = 0; i < 5; i++) {
        vec.push_back(i);
    }
    try {
        cout << vec.at(5) << endl;  //.at会进行越界检查，如果越界会报错，且不会输出
        throw(exception());
    }
    catch (exception &e){
        cout << ".at error: " << e.what() << endl;
    }
    try {
        cout << vec[5] << endl;     //用下标访问没有越界检查，会输出一个非法地址上的随机值，没有意义
        throw(exception());
    }
    catch (exception &e){
        cout << "[] error: " << e.what() << endl;
    }
    return 0;
}