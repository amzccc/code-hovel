#include <iostream>
#include <string>
#include <sys/time.h>
#include <map>
#include <unordered_map>
using namespace std;

const int kRunTime1 = 1000*1000;     // 循环次数
const int kRunTime2 = 1000*10000;
int main()
{
    std::map<int, int> mp;
    std::unordered_map<int, int> unordermp;

    timeval st, et;

    cout << "插入个数 = " << kRunTime1 << endl;
    gettimeofday(&st, NULL);
    for(int i = 0; i < kRunTime1; ++i)
    {
        mp.insert(make_pair(i, i));
    }
    gettimeofday(&et, NULL);
    cout << "1 有序map测试时间insert time:" << (et.tv_sec-st.tv_sec)*1000 + (et.tv_usec-st.tv_usec)/1000 << "ms" << endl;

    gettimeofday(&st, NULL);
    for(int i = 0; i < kRunTime1; ++i)
    {
        unordermp.insert(make_pair(i, i));
    }
    gettimeofday(&et, NULL);
    cout << "1 无序map测试时间insert time:" << (et.tv_sec-st.tv_sec)*1000 + (et.tv_usec-st.tv_usec)/1000 << "ms" << endl;

    cout << "\n插入个数 = " << kRunTime2 << endl;
    mp.clear();
    gettimeofday(&st, NULL);
    for(int i = 0; i < kRunTime2; ++i)
    {
        mp.insert(make_pair(i, i));
    }
    gettimeofday(&et, NULL);
    cout << "2 有序map测试时间insert  time:" << (et.tv_sec-st.tv_sec)*1000 + (et.tv_usec-st.tv_usec)/1000 << "ms" << endl;

    mp.clear();
    gettimeofday(&st, NULL);
    for(int i = 0; i < kRunTime2; ++i)
    {
        mp.emplace(make_pair(i, i));
    }
    gettimeofday(&et, NULL);
    cout << "2 有序map测试时间emplace time:" << (et.tv_sec-st.tv_sec)*1000 + (et.tv_usec-st.tv_usec)/1000 << "ms" << endl;

    unordermp.clear();
    gettimeofday(&st, NULL);
    for(int i = 0; i < kRunTime2; ++i)
    {
        unordermp.insert(make_pair(i, i));
    }
    gettimeofday(&et, NULL);
    cout << "2 无序map测试时间insert  time:" << (et.tv_sec-st.tv_sec)*1000 + (et.tv_usec-st.tv_usec)/1000 << "ms" << endl;

    unordermp.clear();
    gettimeofday(&st, NULL);
    for(int i = 0; i < kRunTime2; ++i)
    {
        unordermp.emplace(make_pair(i, i));
    }
    gettimeofday(&et, NULL);
    cout << "2 无序map测试时间emplace time:" << (et.tv_sec-st.tv_sec)*1000 + (et.tv_usec-st.tv_usec)/1000 << "ms" << endl;

    return 0;
}