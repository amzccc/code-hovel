#include <iostream>
#include <chrono>       //处理时间和日期的库
#include <iomanip>
#include <ratio>        //分数运算的库
#include <ctime>
#include <string>

using namespace std;

//时间段duration 第一个参数类型，第二个参数以秒计的单位类型
chrono::duration<int> twentySeconds(20);
chrono::duration<double, ratio<60>> halfAminute(0.5);   //以60秒为单位
chrono::duration<long, ratio<1, 1000>> oneMillisecond(1);   //以1/1000秒为单位

template<typename T>
void printClockData();

string asString(const chrono::system_clock::time_point& tp);

int main()
{
    chrono::seconds twentySeconds(20);  //秒
    chrono::hours aDay(24);     //24小时
    chrono::milliseconds ms;    //毫秒 默认为0
    ms += twentySeconds + aDay;     
    cout << ms.count() << " ms" << endl;
    cout << chrono::nanoseconds(ms).count() << " ns" << endl;
    cout << endl;

    cout << "system_clock: " <<endl;
    printClockData<chrono::system_clock>();
    cout << "\nhigh_resolution_clock: " << endl;
    printClockData<chrono::high_resolution_clock>();
    cout << "\nsteady_clock: " << endl;
    printClockData<chrono::steady_clock>();

    // chrono::duration<float, ratio<1, 10>>::rep t1(10);  //获得时间段数据的类型
    // chrono::duration<int, ratio<1,100>>::period t2;     //获得时间单位
    // cout << t1 << endl;
    // cout << t2.num << endl;
    // cout << t2.den << endl;
    
    //打印系统时钟的起始点epoch
    chrono::system_clock::time_point tp;
    cout << "epoch: " << asString(tp) << endl;
    //打印当前时间
    tp = chrono::system_clock::now();
    cout << "now: " << asString(tp) << endl;
    //打印系统时钟的最大时间
    tp = chrono::system_clock::time_point::max();
    cout << "max: " << asString(tp) << endl;
    //打印这个系统时钟的最小时间
    tp = chrono::system_clock::time_point::min();
    cout << "min: " << asString(tp) << endl;
}

template<typename T>
void printClockData() {
    cout << "- precision: ";
    typedef typename T::period P;    //时间单位
    if(ratio_less_equal<P, milli>::value) {
        //转换成以毫秒为单位打印
        typedef typename ratio_multiply<P, kilo>::type TT;
        cout << fixed << double(TT::num)/TT::den << " milliseconds" << endl;
    }
    else {
        //以秒为单位
        cout << fixed << double(P::num)/P::den << " seconds" << endl;
    }
    cout << "-is_steady: " << boolalpha << T::is_steady << endl;
}

string asString(const chrono::system_clock::time_point& tp) {
    //转换成系统时间
    time_t t = chrono::system_clock::to_time_t(tp);
    string ts = ctime(&t);      //转换成日历时间
    ts.resize(ts.size() - 1);   //去掉尾标识符
    return ts;
}
