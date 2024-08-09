// 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。
// 如果是则返回 true，否则返回 false。
// 假设输入的数组的任意两个数字都互不相同。
#include <vector>
using namespace std;


bool verifyPostorder(vector<int>& postorder) {
    return recur(postorder, 0, postorder.size() - 1);
}

bool recur(vector<int> &postorder, int left, int right) {
    if(left >= right)
        return true;
    int head = postorder[right];
    int lson = right - 1;
    for(int i = left; i <= right; i++) {
        if(postorder[i] > head) {
            lson = i - 1;
            break;
        }
    }
    for(int i = lson + 1; i <= right; i++) {
        if(postorder[i] < head)
            return false;
    }
    return recur(postorder, left, lson) && recur(postorder, lson + 1, right - 1);
}