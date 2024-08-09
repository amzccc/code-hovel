// 从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

/*
用一个队列从左往右存储当前层的节点，从队列写入数组时判断是否有左右儿子，有则写入
*/
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<vector<int>> levelOrder(TreeNode* root) {
    if(root)
        return {};
    vector<vector<int>> result;
    vector<int> sub_res;
    queue<TreeNode*> node;
    TreeNode* temp;
    node.push(root);
    while(!node.empty()) {
        int count = node.size();
        for(int i = 0; i < count; i++) {
            sub_res.push_back(node.front()->val);
            if(node.front()->left != nullptr)
                node.push(node.front()->left);
            if(node.front()->right != nullptr)
                node.push(node.front()->right);
            node.pop();
        }
        result.push_back(sub_res);
        sub_res.clear();
    }
    return result;
}