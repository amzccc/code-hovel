#include <vector>
//#include <queue>
#include <string>
#include <queue>
#include <cstdlib>
using std::vector;
//using std::queue;
using std::string;
using std::queue;

struct TreeNode {     
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* buildtree(vector<string> &vec) {
    if(vec.empty())
        return nullptr;
    TreeNode* root = new TreeNode(atoi(vec[0].c_str()));
    int size = vec.size();
    int index = 1;
    queue<TreeNode*> stk;
    stk.push(root);
    while(!stk.empty()) {
        queue<TreeNode*> temp;
        while(!stk.empty()) {
            TreeNode* cur = stk.front();
            stk.pop();
            if(index < size) {
                if(vec[index] != "null") {
                    TreeNode* left = new TreeNode(atoi(vec[index].c_str()));
                    cur->left = left;
                    temp.push(left);
                }  
                index++;
            }
            if(index < size) {
                if(vec[index] != "null") {
                    TreeNode* right = new TreeNode(atoi(vec[index].c_str()));
                    cur->right = right;
                    temp.push(right);
                }
                index++;
            }
            else {
                break;
            }
        }
        stk = std::move(temp);
    }
    return root;
}