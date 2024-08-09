// 请完成一个函数，输入一个二叉树，该函数输出它的镜像。

#include <iostream>
#include <queue>

using namespace std;

struct TreeNode
{   
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(nullptr),right(nullptr){};
};

//直接交换
TreeNode* mirrorTree(TreeNode* root) 
{
    if(root == nullptr)
        return root;
    TreeNode* temp = root->left;
    if((root->left != nullptr) || (root->right != nullptr))
    {
        root->left = mirrorTree(root->right);
        root->right = mirrorTree(temp);
    }
    return root;
}

