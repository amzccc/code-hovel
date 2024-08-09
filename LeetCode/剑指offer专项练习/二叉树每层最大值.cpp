// 给定一棵二叉树的根节点 root ，请找出该二叉树中每一层的最大值。

#include <vector>
#include <deque>
#include <limits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

vector<int> largestValues(TreeNode* root) {
    if(root == nullptr) {
        return {};
    }
    vector<int> res;
    deque<TreeNode*> layer;
    layer.push_back(root);
    int max;
    while(!layer.empty()) {
        max = numeric_limits<int>::min();
        int index = 0;
        for(; index < layer.size(); index++) {
            if (max < layer[index]->val)
                max = layer[index]->val;
        }
        res.push_back(max);
        for(int i = 0; i < index; i++) {
            if(layer.front()) {
                if(layer.front()->left) {
                    layer.push_back(layer.front()->left);
                }
                if(layer.front()->right) {
                    layer.push_back(layer.front()->right);
                }
            }
            layer.pop_front();
        }
    }
    return res;
}