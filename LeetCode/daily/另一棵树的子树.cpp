// 给你两棵二叉树 root 和 subRoot 。检验 root 中是否包含和 subRoot 具有相同结构和节点值的子树。如果存在，返回 true ；否则，返回 false 。
// 二叉树 tree 的一棵子树包括 tree 的某个节点和这个节点的所有后代节点。tree 也可以看做它自身的一棵子树。

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) { }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) { }

};

bool isSameTree(TreeNode* root, TreeNode* subRoot) {
    if(root == nullptr && subRoot == nullptr) {
        return true;
    }
    if(root && subRoot && root->val == subRoot->val) {
        return isSameTree(root->left, subRoot->left) && isSameTree(root->right, subRoot->right);
    }
    return false;
}

bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if(root == nullptr) {
        return false;
    }
    bool flag = false;
    if(root->val == subRoot->val) {
        flag = isSameTree(root, subRoot);
    }
    return flag || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(1);

    TreeNode* subroot = new TreeNode(1);

    cout << boolalpha << isSubtree(root, subroot) << endl;

    return 0;
}