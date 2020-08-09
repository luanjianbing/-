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
		//Morris�����㷨�Ĳ������£�
		//1�� ���ݵ�ǰ�ڵ㣬�ҵ���ǰ��ڵ㣬���ǰ��ڵ���Һ����ǿգ�
		//	��ô��ǰ��ڵ���Һ���ָ��ǰ�ڵ㣬Ȼ����뵱ǰ�ڵ�����ӡ�
		//2�� �����ǰ�ڵ������Ϊ�գ���ӡ��ǰ�ڵ㣬Ȼ������Һ��ӡ�
		//3�������ǰ�ڵ��ǰ��ڵ����Һ���ָ����������
		//	��ô��ǰ��ڵ���Һ�������Ϊ�գ���ӡ��ǰ�ڵ㣬Ȼ������Һ��ӡ�
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

	// ����õ�ǰ��ڵ�
	TreeNode *getPredecessor(TreeNode *node) {
		// ǰ��ڵ����(ǰ��ڵ����ָ��һ����)
		// 1. �����ǰ�ڵ������ӣ�
		//		����ô������������һֱ�ߵ��׵õ��ľ���ǰ��ڵ�
		//		��������ӵ��ҽڵ�ָ��Ϊ�գ���ô���Ӿ��ǵ�ǰ�ڵ��ǰ��ڵ�
		// 2. �����ǰ�ڵ�û�����ӣ�
		//		�����Ǹ��ڵ���Һ��ӣ���ôǰ��ڵ���Ǹ��ڵ�
		//		�����Ǹ��ڵ�����ӣ���ô��û��ǰ��ڵ㣬�����Լ����׽ڵ�
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
