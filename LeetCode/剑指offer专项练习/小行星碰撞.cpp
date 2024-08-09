// 给定一个整数数组 asteroids，表示在同一行的小行星。

// 对于数组中的每一个元素，其绝对值表示小行星的大小，正负表示小行星的移动方向（正表示向右移动，负表示向左移动）。每一颗小行星以相同的速度移动。

// 找出碰撞后剩下的所有小行星。碰撞规则：两个行星相互碰撞，较小的行星会爆炸。如果两颗行星大小相同，则两颗行星都会爆炸。两颗移动方向相同的行星，永远不会发生碰撞。

//  

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/XagZNi
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <vector>
#include <stack>
using namespace std;

vector<int> asteroidCollision(vector<int>& asteroids) {
    deque<int> plante;
    vector<int> res;
    int size = asteroids.size();
    int index = 0;
    while(index < size) {
        if(plante.empty()) {
            plante.push_back(asteroids[index]);
            index++;
            continue;
        }
        if(asteroids[index] < 0 && plante.back() > 0) {
            if(abs(asteroids[index]) > abs(plante.back())) {
                plante.pop_back();
            }
            else if(abs(asteroids[index]) == abs(plante.back())) {
                plante.pop_back();
                index++;
            }
            else {
                index++;
            }
        }
        else {
            plante.push_back(asteroids[index]);
            index++;
        }
    }
    if(plante.empty())
        return {};
    for(int &it: plante) {
        res.push_back(it);
    }
    return res;
}