// 请实现一个函数，用来判断一棵二叉树是不是对称的。
// 如果一棵二叉树和它的镜像一样，那么它是对称的。

//递归的思想：取左右子树是否为对称二叉树的交集
#include <deque>
using namespace std;

struct TreeNode
{   
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(nullptr),right(nullptr){};
};

bool isSymmetric(TreeNode* root)
{   
    if(!root)
        return true;
    return isSym(root->left, root->right);
}

bool isSym(TreeNode* left, TreeNode* right)
{   
    if(left == nullptr && right == nullptr)
        return true;
    if(((left == nullptr)&& (right != nullptr))
        || ((left !=nullptr) && (right == nullptr)))
        return false;
    if(left->val != right->val)
        return false;
    return isSym(left->left,right->right) && isSym(left->right, right->left);
}