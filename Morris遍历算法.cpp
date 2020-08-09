#include <iostream>

using namespace std;

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
	void Morris(TreeNode *root) {
		//Morris遍历算法的步骤如下：
		//1， 根据当前节点，找到其前序节点，如果前序节点的右孩子是空，
		//	那么把前序节点的右孩子指向当前节点，然后进入当前节点的左孩子。
		//2， 如果当前节点的左孩子为空，打印当前节点，然后进入右孩子。
		//3，如果当前节点的前序节点其右孩子指向了它本身，
		//	那么把前序节点的右孩子设置为空，打印当前节点，然后进入右孩子。
		if (root == nullptr)
			return;
		TreeNode *node = root;
		while (node != nullptr) {
			if (node->left == nullptr) {
				cout << node->val << endl;
				node = node->right;
			}
			else {
				TreeNode *pre = getPredecessor(node);

				if (pre->right == nullptr) {
					pre->right = node;
					node = node->left;
				}
				else if (pre->right == node){
					pre->right = nullptr;
					cout << node->val << endl;
					node = node->right;
				}
			}
		}
	}

	// 计算得到前序节点
	TreeNode *getPredecessor(TreeNode *node) {
		// 前序节点规则(前序节点的右指针一定空)
		// 1. 如果当前节点有左孩子，
		//		①那么沿着左孩子向右一直走到底得到的就是前序节点
		//		②如果左孩子的右节点指针为空，那么左孩子就是当前节点的前序节点
		// 2. 如果当前节点没有左孩子，
		//		①他是父节点的右孩子，那么前序节点就是父节点
		//		②他是父节点的左孩子，那么他没有前序节点，并且自己是首节点
		TreeNode *pre = node;
		if (node->left != nullptr) {
			pre = pre->left;
			while (pre->right != nullptr && pre->right != node)
				pre = pre->right;
		}
		return pre;
	}
};

int main() {
	TreeNode *root = new TreeNode(6);
	root->left = new TreeNode(4);
	root->right = new TreeNode(9);
	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(5);
	root->left->left->left = new TreeNode(1);
	root->left->left->right = new TreeNode(3);
	root->right->left = new TreeNode(7);
	root->right->right = new TreeNode(10);
	root->right->left->right = new TreeNode(8);

	Solution s;
	s.Morris(root);

	return 0;
}
