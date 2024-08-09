// 给你 n 个二维平面上的点 points ，其中 points[i] = [xi, yi] ，请你返回两点之间内部不包含任何点的 最宽垂直区域 的宽度。

// 垂直区域 的定义是固定宽度，而 y 轴上无限延伸的一块区域（也就是高度为无穷大）。 最宽垂直区域 为宽度最大的一个垂直区域。

// 请注意，垂直区域 边上 的点 不在 区域内。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/widest-vertical-area-between-two-points-containing-no-points
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

//就是排个序找最大间隔嘛

#include <vector>
#include <iostream>

using namespace std;

void sort(vector<vector<int>>& points, int left, int right) {
    if(left >= right) {
        return;
    }
    int l = left;
    int r;
    int mid = (left + right)/2;
    r = points[left][0] > points[right][0]? (points[left][0] < points[mid][0]? left : 
            (points[right][0] > points[mid][0]? right : mid)) :
        (points[right][0] < points[mid][0]? right : 
            points[mid][0] > points[left][0]? mid : left);
    swap(points[right], points[r]);
    int index = points[right][0];
    r = right;
    while(l <= r) {
        if(l >= r) {
            break;
        }
        while(l < r && points[l][0] <= index) {
            l++;
        }
        while(l < r && points[r][0] >= index) {
            r--;
        }
        swap(points[l], points[r]);
    }
    swap(points[l], points[right]);
    sort(points, left, l-1);
    sort(points, l+1, right);
}

int maxWidthOfVerticalArea(vector<vector<int>>& points) {
    sort(points, 0, points.size() - 1);
    int max = 0;
    for(int i = 1; i < points.size(); i++) {
        max = points[i][0] - points[i-1][0] > max? (points[i][0] - points[i-1][0]) : max;
    }
    return max;
}