// 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
// 最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，
// 最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大
// （一个节点也可以是它自己的祖先）。”

//二叉搜索树的最近公共祖先肯定比小的大，比大的小

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

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if(p == q)
        return p;
    while(!root)
    {
        if(root->val > p->val && root->val > q->val)
            root = root->left;
        else if(root->val < p->val && root->val < q->val)
            root = root->right;
        else
            break;
    }
    return root;
}


