# �����������Ĳ������ #
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
            if (val < pos->val) {	// ������ֵС�ڵ�ǰ�ڵ��ֵ������������ 
                if (pos->left == nullptr) {		// һֱ�ҵ��ڵ�Ϊ�յ����������һ���µĽڵ� 
                    pos->left = new TreeNode(val);
                    break;
                } else {
                    pos = pos->left;
                }
            } else {	// ������ֵ���ڵ��ڵ�ǰ�ڵ��ֵ������������ 
                if (pos->right == nullptr) {	// �ҵ��ڵ�Ϊ�յ����������һ���µĽڵ� 
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

