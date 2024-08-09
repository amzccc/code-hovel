// 从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<int> levelOrder(TreeNode* root) {
    if(!root)
        return {};
    vector<int> res;
    TreeNode* cur;
    queue<TreeNode*> head;
    head.push(root);
    while(!head.empty()) {
        cur = head.front();
        head.pop();
        res.push_back(cur->val);
        if(cur->left != nullptr)
            head.push(cur->left);
        if(cur->right != nullptr)
            head.push(cur->right);
    }
    return res;
}