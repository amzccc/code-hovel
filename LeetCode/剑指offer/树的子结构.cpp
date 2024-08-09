// 输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
// B是A的子结构， 即 A中有出现和B相同的结构和节点值。
#include <stack>
using namespace std;

struct TreeNode
{   
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(nullptr),right(nullptr){};
};

bool isSubStructure(TreeNode* A, TreeNode* B) {
    if(A == nullptr || B == nullptr)
        return false;
    stack<TreeNode*> head_A;
    stack<TreeNode*> head_B;
    head_A.push(A);
    head_B.push(B);
    TreeNode* cur_A = A;
    TreeNode* cur_B = B;
    while(!head_A.empty() && !head_B.empty()) {
        //如果栈中头节点不相等，说明可能是儿子，把A的左右儿子放入栈中
        while(!head_A.empty() && head_A.top()->val != head_B.top()->val) {
            while (!head_B.empty())
            {
                head_B.pop();
            }
            head_B.push(B);
            cur_A = head_A.top();
            head_A.pop();
            if (cur_A->right != nullptr)
                head_A.push(cur_A->right);
            if(cur_A->left != nullptr)
                head_A.push(cur_A->left); 
        }
        //此时栈中头节点相等了
        //再判断A和B的子树是否相等，弹出头节点，按右左放入栈中
        if(!head_A.empty() && head_A.top()->right != nullptr && head_B.top()->right != nullptr) {
            cur_A = head_A.top();
            head_A.pop();
            head_A.push(cur_A->right);
            cur_B = head_B.top();
            head_B.pop();
            head_B.push(cur_B->right);
            if(cur_A->left != nullptr && cur_B->left != nullptr) {
                head_A.push(cur_A->left);
                head_B.push(cur_B->left);
            }
        }
        //如果没有右节点，只有左节点
        else if(!head_A.empty() && head_A.top()->left != nullptr && head_B.top()->left != nullptr 
                && head_B.top()->right == nullptr){
            cur_A = head_A.top();
            head_A.pop();
            head_A.push(cur_A->left);
            cur_B = head_B.top();
            head_B.pop();
            head_B.push(cur_B->left);
        }
        //如果是叶节点，直接弹出
        else if(!head_A.empty() && head_B.top()->left == nullptr && head_B.top()->right == nullptr) {
            head_A.pop();
            head_B.pop();
        }
        else return false;
    }
    return head_B.empty()? true: false;
}

