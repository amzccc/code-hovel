// 输入某二叉树的前序遍历和中序遍历的结果，请构建该二叉树并返回其根节点。
// 假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
// Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// Output: [3,9,20,null,null,15,7]
#include <vector>
#include <stack>
using namespace std;

struct TreeNode
{   
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(nullptr),right(nullptr){};
};

//先序数组的第一个肯定是根节点，然后在中序数组中找到根节点的位置，就确定了左右子树的个数，
//再分别递归左右子树的根节点
//可行，但是太慢了
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if(preorder.size() == 0)  
        return nullptr;
    TreeNode* root = new TreeNode (preorder[0]);
    int index  = 0;
    while(inorder[index] != preorder[0]) {
        index++;
    }
    if(index > 0) {
        vector<int> pre_lefttree (preorder.begin() + 1, preorder.begin() + index + 1);
        vector<int> in_lefttree (inorder.begin(), inorder.begin() + index);
        root->left = buildTree (pre_lefttree, in_lefttree);
    }
    if(index < inorder.size() - 1) {
        vector<int> pre_righttree (preorder.begin() + index + 1, preorder.end());
        vector<int> in_righttree(inorder.begin() + index + 1, inorder.end());
        root->right = buildTree(pre_righttree, in_righttree);
    } 
    return root;
}

TreeNode* buildTree2(vector<int>& preorder, vector<int>& inorder) {
    if (!preorder.size()) {
        return nullptr;
    }
    TreeNode* root = new TreeNode(preorder[0]);
    stack<TreeNode*> head;
    head.push(root);
    int inptr = 0;
    TreeNode* cur;
    for(int i = 1; i < preorder.size(); i++) {
        if(head.top()->val != inorder[inptr]) {
            head.top()->left = new TreeNode(preorder[i]);
            head.push(head.top()->left);
        }
        else {
            while(!head.empty() && head.top()->val == inorder[inptr]) {
                cur = head.top();
                head.pop();
                inptr++;
            }
            cur->right = new TreeNode(preorder[i]);
            head.push(cur->right);
        }
    }
    return root;
}                        

