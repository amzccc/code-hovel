// 输入一棵二叉树的根节点，求该树的深度。
// 从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。

class TreeNode
{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

void preOrder(TreeNode* root, int &r)
{
    if(root == nullptr)
        return;
    r++;
    int cur = r;
    int max = 0;
    if(root->left != nullptr)
    {
        preOrder(root->left, r);
        max = r;
    }
    if(root->right != nullptr)
    {   
        r = cur;
        preOrder(root->right, r);
        if(max > r)
            r = max;
    }
    
}
int maxDepth(TreeNode* root)
{
    if(root == nullptr)
        return 0;
    int result = 0;
    preOrder(root, result);
    return result;
}


#include <algorithm>
using namespace std;
//后序深度遍历
int max_Depth(TreeNode* root)
{
    if(root == nullptr)
        return 0;
    return max(max_Depth(root->left), max_Depth(root->right)) + 1;
}