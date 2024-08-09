// 请实现一个函数按照之字形顺序打印二叉树，
// 即第一行按照从左到右的顺序打印，
// 第二层按照从右到左的顺序打印，
// 第三行再按照从左到右的顺序打印，其他行以此类推。

#include <vector>
#include <deque>
using namespace std;

struct TreeNode
{   
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(nullptr),right(nullptr){};
};

vector<vector<int>> levelOrder(TreeNode* root) {
    if(!root)
        return {};
    vector<int> layer;
    vector<vector<int>> res;
    deque<TreeNode*> oddlay;
    deque<TreeNode*> doulay;
    oddlay.push_back(root);
    while(!oddlay.empty() || !doulay.empty()) {
        while(!oddlay.empty()) {
            layer.push_back(oddlay.front()->val);
            if(oddlay.front()->left)
                doulay.push_back(oddlay.front()->left);
            if(oddlay.front()->right)
                doulay.push_back(oddlay.front()->right);
            oddlay.pop_front();
        }
        if(!layer.empty())
            res.push_back(layer);
        layer.clear();
        while(!doulay.empty()) {
            layer.push_back(doulay.back()->val);
            if(doulay.back()->right)
                oddlay.push_front(doulay.back()->right);
            if(doulay.back()->left)
                oddlay.push_front(doulay.back()->left);
            doulay.pop_back();
        }
        if(!layer.empty())
            res.push_back(layer);
        layer.clear();
    }
    return res;
}