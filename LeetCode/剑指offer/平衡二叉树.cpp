// 输入一棵二叉树的根节点，判断该树是不是平衡二叉树。
// 如果某二叉树中任意节点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct TreeNode
{   
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(nullptr),right(nullptr){};
};

int depth(TreeNode* root)
{
    if(root == nullptr)
        return 0;
    return max(depth(root->left), depth(root->right)) + 1; 
}

bool isBalanced(TreeNode* root)
{
    if(root == nullptr)
        return true;
    int left = depth(root->left);
    int right = depth(root->right);
    if(left - right > 1 || left - right < -1 )
        return false;
    return isBalanced(root->left) && isBalanced(root->right);
}

//剪枝法更好
int recur(TreeNode* root)
{
    if(root == nullptr)
        return true;
    int left = recur(root->left);
    if(left ==  -1)
        return -1;
    int right = recur(root->right);
    if(right == -1)
        return -1;
    return abs(left - right) < 2? (max(left, right) + 1): -1;
}
bool isbalanced(TreeNode* root)
{
    if(root == nullptr)
        return false;
    return recur(root) != -1;
}

int main()
{
    //运算符规则
    cout << (false & false);    //只有两侧都是true才是true，与直觉有点不同
    cout << (false && false);   //因为false默认值是0，0并上0还是0
    cout << (true & false);     //&位运算符； &&逻辑运算符
}