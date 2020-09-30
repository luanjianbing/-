# 二叉搜索树的插入操作 #
#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }
        TreeNode* pos = root;
        while (pos != nullptr) {
            if (val < pos->val) {	// 待插入值小于当前节点的值，往左子树找 
                if (pos->left == nullptr) {		// 一直找到节点为空的情况，插入一个新的节点 
                    pos->left = new TreeNode(val);
                    break;
                } else {
                    pos = pos->left;
                }
            } else {	// 待插入值大于等于当前节点的值，往右子树找 
                if (pos->right == nullptr) {	// 找到节点为空的情况。插入一个新的节点 
                    pos->right = new TreeNode(val);
                    break;
                } else {
                    pos = pos->right;
                }
            }
        }
        return root;
    }
};

int main(){
	TreeNode *root = new TreeNode(4);
	root->left = new TreeNode(2);
	root->right = new TreeNode(7);
	root->left->left = new TreeNode(1);
	root->left->right = new TreeNode(3);
	
	const int val = 5;
	Solution s;
	TreeNode *res = s.insertIntoBST(root, val); 
	
	return 0;
} 

