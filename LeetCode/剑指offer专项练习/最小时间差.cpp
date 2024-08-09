// 给定一个 24 小时制（小时:分钟 "HH:MM"）的时间列表，找出列表中任意两个时间的最小时间差并以分钟数表示。

#include <vector>
#include <string>
using namespace std;


int findMinDifference(vector<string>& timePoints) {
    vector<int> minutes;
    int size = timePoints.size();
    int res;
    for (string &s: timePoints) {
        res = stoi(s.substr(0, 2)) * 60 + stoi(s.substr(3, 2));
        minutes.push_back(res);
    }
    const int day = 24 * 60;
    res = day;
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            int temp = abs(minutes[i] - minutes[j]);
            if(temp > day/2)
                temp = day - temp;
            if(temp < res)
                res = temp;
        }
        if(res == 0)
            return res;
    }
    return res;
}