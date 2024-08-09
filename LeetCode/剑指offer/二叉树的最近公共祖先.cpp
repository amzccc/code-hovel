// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
#include <stack>
#include <queue>
using namespace std;

struct TreeNode
{   
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(nullptr),right(nullptr){};
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if(root == nullptr || root == p || root == q) return root;  //判断终止条件
    TreeNode *left = lowestCommonAncestor(root->left, p, q);    //当前节点的左子树会返回一个至少是一个节点祖先的节点，如果为nullptr表示左子树没有这两个节点
    TreeNode *right = lowestCommonAncestor(root->right, p, q);  //同理右子树
    if(left == nullptr) return right;   //左子树没有就说明在右子树
    if(right == nullptr) return left;   //右子树同理
    //运行到这表示左子树和右子树都不为空，说明这两个节点正好分别在左子树和右子树上，那当前节点就是最近公共祖先
    return root;    
}

