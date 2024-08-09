// 给你二叉树的根节点 root 和一个整数目标和 targetSum ，
// 找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。
// 叶子节点 是指没有子节点的节点。
#include <vector>
#include <stack>
using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

vector<vector<int>> pathSum(TreeNode* root, int target) {
    vector<int> sub_res;
    vector<vector<int>> res;
    recur(root, target, sub_res, res);
    return res;
}

void recur(TreeNode* root, int target, vector<int> &sub, vector<vector<int>> &res) {
    if(root == nullptr)
        return ;
    sub.push_back(root->val);
    if(root->left == nullptr && root->right == nullptr) {
        if(target == 0) {
            res.push_back(sub);
        }
    }
    recur(root->left, target, sub, res);
    recur(root->right, target, sub, res);
    sub.pop_back();
}