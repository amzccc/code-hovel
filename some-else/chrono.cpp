#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

int main() {
    cout << "system_clock precision: ";
    cout << chrono::system_clock::period::num << "/" << chrono::system_clock::period::den << endl;
    cout << "steady_clock precision: ";
    cout << chrono::steady_clock::period::num << "/" << chrono::steady_clock::period::den << endl;
    cout << "chrono::high_resolution_clock precision: ";
    cout << chrono::high_resolution_clock::period::num << "/" << chrono::high_resolution_clock::period::den << endl;
    // 获取当前时间
    chrono::time_point<chrono::steady_clock, chrono::nanoseconds> curTime = chrono::steady_clock::now();        // 是一个时间点
    // cout << "steady_clock now: " << curTime << endl; //error 时间点不能直接输出
    cout << "time_since_epoch (steady_clock): \t\t" << curTime.time_since_epoch().count() << endl;                  //输出当前到开始已经经历的时间数，count返回有多少个时间段
    
    chrono::time_point high_curTime = chrono::high_resolution_clock::now();                                     // 高精度时钟，不建议使用，因为实现方式不统一
    cout << "time_since_epoch (high_resolution_clock): \t" << high_curTime.time_since_epoch().count() << endl;                         
    
    chrono::time_point sys_curTime = chrono::system_clock::now();
    cout << "time_since_epoch (system_clock): \t\t" << sys_curTime.time_since_epoch().count() << endl;
    time_t time_c = chrono::system_clock::to_time_t(sys_curTime);                                                 // 系统时钟有这个接口能转换成c风格的时间戳
    cout << "system_clock::to_time_t: \t\t\t" << time_c << endl;
    cout << "ctime: \t\t\t\t\t\t" << ctime(&time_c) << endl;                                                                   // 转换成ctime的日历时间
    chrono::time_point<chrono::steady_clock, chrono::nanoseconds> timePoint;    // 默认构造出的时间点是多少？
    cout << "default timePoint<chrono::steady_clock, chrono::nanoseconds>: " << timePoint.time_since_epoch().count() << endl;
    chrono::time_point<chrono::system_clock, chrono::nanoseconds> sysTimePoint;
    cout << "default timePoint<chrono::system_clock, chrono::nanoseconds>: " << timePoint.time_since_epoch().count() << endl;

    cout << "-----------------------------------------------------------------------------\n";
    // 时间运算  chrono可以进行时间段的运算
    chrono::hours hour(1);
    chrono::minutes minute(1);
    auto diff = hour - minute;  //得到的结果单位取小
    cout << "1 hour - 1 minute = " << diff.count() << endl;
    
    chrono::steady_clock::time_point steadyTimePoint;   
    cout << "curTimePoint - defaultTimePoint = " << chrono::duration_cast<chrono::nanoseconds>(curTime - steadyTimePoint).count() << endl;  // 时间点和时间点相减得到时间段
    // auto addTimePoint = curTime + steadyTimePoint;               // 时间点之间不能相加
    auto nextTimePoint = curTime + chrono::minutes{1};              // 时间点可以加时间段，得到下个时间点
    cout << "当前时间点加一分钟: " << chrono::duration_cast<chrono::seconds>(nextTimePoint - steadyTimePoint).count() << endl;
    // 时间段之间允许算数运算
    chrono::minutes fourMinutes(4);
    chrono::seconds twoSeconds(2);
    cout << "4minutes + 2second = " << (fourMinutes + twoSeconds).count() << endl;
    cout << "4minutes - 2second = " << (fourMinutes - twoSeconds).count() << endl;
    // cout << "4minutes * 2second = " << (fourMinutes * twoSeconds).count() << endl;   // 不允许时间相乘，没有意义
    cout << "4minutes * 2 = " << (fourMinutes * 2).count() << endl;
    cout << "4minutes / 2second = " << (fourMinutes / twoSeconds) << endl;      // 时间段相除得到的是个值
    chrono::seconds sevenSeconds(7);
    cout << "4minutes % 7second = "s << (fourMinutes % sevenSeconds).count() << endl;

    cout << "-----------------------------------------------------------------------------\n";
    // 自定义时间段，第一个模板参数是数据类型，整数或者小数，第二个参数为比率
    chrono::duration<int, ratio<1, 16>> sevenOfSixteen(7);
    chrono::duration<int, ratio<1, 8>> OneOfEight(1);
    cout << "7/16 - 3/8 = " << (sevenOfSixteen - OneOfEight).count() << endl;   // 结果取小的单位 得到5个1/16
    cout << "两个自定义的时间段不是倍数关系的情况下:" << endl;
    chrono::duration<double, ratio<1, 11>> nineOfEleven(9.0);
    chrono::duration<double, ratio<1, 7>> fiveOfSeven(5.0);
    cout << "5.0/7 - 9.0/11 = " << (fiveOfSeven - nineOfEleven).count() << endl;    // res = -8, 结果是取公倍数为分母的结果，也就是-8个1/77
    
    cout << "-----------------------------------------------------------------------------\n";

    // steady_clock起点是哪里
    auto steadyNow = chrono::steady_clock::now();
    chrono::system_clock::time_point systemNow = chrono::system_clock::now();
    auto timeStamp = chrono::system_clock::to_time_t(systemNow);
    cout << timeStamp << endl;
    typedef ratio<1LL, 100000LL> tenMicro ;
    
    {
    using tenmicroseconds = chrono::duration<int64_t, tenMicro>;
    auto steadyCast = chrono::duration_cast<tenmicroseconds>(steadyNow - timePoint).count();
    cout << steadyCast << endl;
    cout << "system date:\t" << ctime(&timeStamp) << endl;
    cout << "steady date:\t" << ctime(&steadyCast) << endl;
    }

    cout << "-----------------------------------------------------------------------------\n";

    // 获取时间 c库
    time_t now_c = time(NULL);      // 返回从1900至今的秒数，入参不为NULL则也赋给time_t类型的入参
    cout << "now: " << now_c << endl;
    char *date = ctime(&now_c);
    cout << "ctime(&now): " << date << endl;    // 将时间戳转换成字符串

    // 转换utc时间
    tm *utcTime = gmtime(&now_c);
    cout << "tm struct {\n" << "  tm_year: " << utcTime->tm_year << " (since 1900)" << endl;
    cout << "  tm_month: " << utcTime->tm_mon << " (since 0)" << endl;
    cout << "  tm_yday: " << utcTime->tm_yday << endl;
    cout << "  tm_mday: " << utcTime->tm_mday << endl;
    cout << "  tm_wday: " << utcTime->tm_wday << endl;
    cout << "  tm_hour: " << utcTime->tm_hour << endl;
    cout << "  tm_minute: " << utcTime->tm_min << endl;
    cout << "  tm_second: " << utcTime->tm_sec << endl;
    cout << "};\n";
    // 转成字符串输出
    date = asctime(utcTime);
    cout << date << endl;
    chrono::system_clock::now().time_since_epoch().count();
    return 0;
}