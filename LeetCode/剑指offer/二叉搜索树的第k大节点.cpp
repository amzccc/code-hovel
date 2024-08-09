// 给定一棵二叉搜索树，请找出其中第 k 大的节点的值。
//二叉搜索树：若子节点不为空，则左儿子小于父，右儿子大于父

//依次搜索右儿子，有就先压入当前节点，再压入右儿子，若无右儿子，打印当前节点，如有左儿子就压入栈

#include <iostream>
#include<queue>
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

int kthLargest(TreeNode* root, int k)
{  
    if(root ==nullptr || k <= 0)
        return -1;
    TreeNode* cur = root;
    stack<int> result;
    stack<TreeNode*> path;
    path.push(root);
    while(result.size() < k && path.size() != 0)
    {
        cur = path.top();
        path.pop();
        if(cur->right != nullptr)
        {
            path.push(cur);
            cur = cur->right;
            path.push(cur);
        }
        else
        {
            result.push(cur->val);
            if(path.size() != 0)
            {
                TreeNode* temp = path.top();
                temp->right = nullptr;
            }
            if(cur->left != nullptr)
            {
                path.push(cur->left);
            }
        }
    } 
    return result.top();
}


//中序遍历
void inOrder(TreeNode* root, vector<int> &arr)
{
    if(root == nullptr)
        return;
    inOrder(root->right, arr);
    arr.push_back(root->val);
    inOrder(root->left, arr);
}

int kth_Largest(TreeNode* root, int k)
{   
    vector<int> res;
    inOrder(root, res);
    return res[k - 1];
}


//test
int main()
{
    TreeNode tree5(5);
    TreeNode* t5 = &tree5;
    TreeNode tree3(3);
    TreeNode* t3 = &tree3;
    TreeNode tree7(7);
    TreeNode* t7 = &tree7;
    TreeNode tree1(1);
    TreeNode* t1 = &tree1;
    TreeNode tree4(4);
    TreeNode* t4 = &tree4;
    TreeNode tree6(6);
    TreeNode* t6 = &tree6;
    TreeNode tree8(8);
    TreeNode* t8 = &tree8;
    t5->left = t3;
    t5->right = t7;
    t3->left = t1;
    t3->right = t4;
    t7->left = t6;
    t7->right = t8;

    cout << kthLargest(t5, 3);

}