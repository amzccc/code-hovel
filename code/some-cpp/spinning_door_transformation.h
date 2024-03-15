/******************************************
 * @file:			spinning_door_transformation.cpp
 * @brief:          旋转门压缩算法			
 * @author:			cheng wentao
 * @version:		v1.0.0
 * @date:			2023-10-19 21:42:42
 ******************************************/
#ifndef __SPINNING_DOOR_TRANSFORMATION_H__
#define __SPINNING_DOOR_TRANSFORMATION_H__

#include <numeric>
#include <vector>

using namespace std;

struct Point {
    unsigned long long x{0}; 
    float y{0};
};

struct Data
{
    Point value{0, 0.0};
    float slope{0.0};
};


class SDT {
public:
    SDT() = default;
    explicit SDT(Point x);
    SDT(Point x, float delta);
    virtual ~SDT() = default;

    SDT operator<<(Point p);

    void read(Point p);
    void setDelta(float limit) { m_delta  = limit; }
    float getDelta() { return m_delta; }
    vector<Data> uncompress();
private:

private:
    float m_upLimit{std::numeric_limits<float>::min()};
    float m_downLimit{std::numeric_limits<float>::max()};
    Point m_cur{0, 0.0};
    float m_delta{0.0};
    vector<Data> m_compressData{};
};

SDT::SDT(Point x): m_cur{x} {

}

SDT::SDT(Point x, float delta): m_cur{x}, m_delta{delta} {

} 

SDT SDT::operator<<(Point p) {
    this->read(p);
    return *this;
}

void SDT::read(Point p) {
    float up_slope = (p.y - m_cur.y - m_delta) / (p.x - m_cur.x);
    float down_slope = (p.y - m_cur.y + m_delta) / (p.x - m_cur.x);
    m_upLimit = up_slope > m_upLimit? up_slope : m_upLimit;
    m_downLimit = down_slope < m_downLimit? down_slope : m_downLimit;
    if(m_upLimit >= m_downLimit) {
        Data d;
        d.value = m_cur;
        d.slope = (p.y - m_cur.y) / (p.x - m_cur.x);
        m_compressData.push_back(d);
        m_cur = p;
        m_upLimit = numeric_limits<float>::min();
        m_downLimit = numeric_limits<float>::max();
    }
}

vector<Data> SDT::uncompress() {
    Data d;
    d.value = m_cur;
    d.slope = 0;
    m_compressData.push_back(d);
    return m_compressData;
}

#endif // !spinning_door_transformation.hpp

#if 0

#include <iostream>
#include <chrono>
#include <cmath>

constexpr float PI = 3.14159265;

int main() {
    
    auto cur = chrono::system_clock::now();
    unsigned long long index = (cur.time_since_epoch().count() / duration_cast<chrono::milliseconds>(chrono::milliseconds(1)).count());
    unsigned long long interval = duration_cast<chrono::milliseconds>(chrono::seconds(10)).count();
    cout << interval << endl;
    int index2 = 1;
    SDT sdt(Point{index, 0.0}, 0);
    index += interval;
    int count = 360000;
    cout << index << endl;
    for(int i = 0; i < count; i++) {
        sdt.read({index, 10000 * sin((index2++) * PI / 180)});
        index += interval;
        if(i == count - 1) {
            cout << index << endl;
        }
    }
    vector<Data> vec = sdt.uncompress();
    cout << vec.size() << endl;
    cout << vec.size() * 1.0 / count << endl;

    return 0;
}

#endif
