#include <iostream>
#include <queue>
#include <stack>

namespace MyTree {
	class TreeNode {
	public:
		int value;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int value) :value(value), left(nullptr), right(nullptr) {}
	};

	class printTree
	{
	public:
		printTree() {}
		~printTree() {}
		//�������: ��->��->��
		// �������(�ݹ�)
		void printInPreOrdered(TreeNode *head) {
			if (head == nullptr) return;
			std::cout << head->value << " ";	// ��
			printInPreOrdered(head->left);		// ��
			printInPreOrdered(head->right);		// ��
		}
		// �������(����)
		void printInPreOrderedIter(TreeNode *head) {
			std::cout << "Pre Order: ";
			if (head != nullptr) {
				std::stack<TreeNode *> *sta = new std::stack<TreeNode *>;
				sta->push(head);
				TreeNode *cur = head;
				while (!sta->empty()) {
					cur = sta->top();
					sta->pop();
					std::cout << cur->value << " ";
					if (cur->right != nullptr) {	 // ��ѹ�ұ߽ڵ㣬��ѹ��߽ڵ�
						sta->push(cur->right);
					}
					if (cur->left != nullptr) {		//��ջ��ʱ����ȳ��������ٳ�����
						sta->push(cur->left);
					}
				}
				std::cout << std::endl;
			}
		}

		//�������: ��->��->��
		// �������(�ݹ�)
		void printInOrdered(TreeNode *head) {
			if (head == nullptr) return;
			printInOrdered(head->left);		// ��
			std::cout << head->value << " ";	// ��
			printInOrdered(head->right);		// ��
		}
		// �������(����)
		void printInOrderedIter(TreeNode *head) {
			std::cout << "In Order: ";
			if (head != nullptr) {
				std::stack<TreeNode *> *sta = new std::stack<TreeNode *>;
				TreeNode *cur = head;
				while (!sta->empty() || cur != nullptr) {	//ջ��Ϊ�ջ�ǰָ��Ϊ��
					if (cur != nullptr) {	// �Ȱ����ѹ��ȥ
						sta->push(cur);
						cur = cur->left;
					}
					else {
						cur = sta->top();
						sta->pop();
						std::cout << cur->value << " ";
						cur = cur->right;
					}
				}
				std::cout << std::endl;
			}
		}

		//�������: ��->��->��
		// �������(�ݹ�)
		void printInPostOrdered(TreeNode *head) {
			if (head == nullptr) return;
			printInPostOrdered(head->left);		// ��
			printInPostOrdered(head->right);		// ��
			std::cout << head->value << " ";	// ��
		}
		// �������(����)
		void printInPostOrderedIter(TreeNode *head) {
			std::cout << "Post Order: ";
			if (head != nullptr) {
				std::stack<TreeNode *> *sta1 = new std::stack<TreeNode *>;
				std::stack<TreeNode *> *sta2 = new std::stack<TreeNode *>;
				TreeNode *cur = head;
				sta1->push(cur);	//ѹ���׵�ַ
				while (!sta1->empty()) {
					cur = sta1->top();
					sta1->pop();
					sta2->push(cur);	//sta1������sta2ѹ��
					if (cur->left != nullptr) {		//���������ҵ�˳��ѹ��ջ
						sta1->push(cur->left);
					}
					if (cur->right != nullptr) {
						sta1->push(cur->right);
					}
				}
				while (!sta2->empty()) {
					cur = sta2->top();
					sta2->pop();
					std::cout << cur->value << " ";
				}
				std::cout << std::endl;
			}
		}

		// ʹ�ö��д�ӡ������
		void printLayer(TreeNode* head) {
			std::cout << "Layer Order:" << std::endl;
			if (head == nullptr) {
				return;
			}
			std::queue<TreeNode*> q;		//����q���Ŷ������͵�ָ��
			q.push(head);		//ѹ���׵�ַ
			while (!q.empty()) {
				TreeNode* cur = q.front();		//curָ���һλ
				q.pop();					//������һλ
				std::cout << cur->value << " ";	//��ӡ��һλ��value
				if (cur->left != nullptr) {		//ѹ�뵱ǰָ��λ�õ������ĵ�ַ
					q.push(cur->left);
				}
				if (cur->right != nullptr) {	//ѹ�뵱ǰָ��λ�õ������ĵ�ַ
					q.push(cur->right);
				}
			}	//������Ҵ�ӡ������
			std::cout << std::endl;
		}
	private:

	};

	// ���������(BST)
	// 1.ÿ��Ԫ�ض���һ����ֵ�����Ҳ��ظ�
	// 2.�������ļ�ֵ��С�ڸ��ڵ�ļ�ֵ
	// 3.�������ļ�ֵ�����ڸ��ڵ�ļ�ֵ
	// 4.�����������Ƕ��������
	class BST
	{
	public:
		class Element
		{
		public:
			int key;
		};
		class BstNode
		{
		public:
			Element data;
			BstNode *lChild;
			BstNode *rChild;
			void display(int i)
			{
				std::cout << "Position : " << i << " , data.key : " << data.key << std::endl;
				if (lChild) lChild->display(i * 2);
				if (rChild) rChild->display(i * 2 + 1);
			}
		};

		BST(BstNode *init = 0) 
		{
			root = init;
		}
		~BST() {}

		bool insertNode(const Element &x) 
		{
			BstNode *p = root;
			BstNode *q = 0;	// qָ��p�ĸ��ڵ�
			while (p)
			{
				q = p;
				if (x.key == p->data.key) return false;	// �ظ�
				if (x.key < p->data.key) p = p->lChild;
				else p = p->rChild;
			}
			// �ҵ���λ�þ���q
			p = new BstNode;
			p->lChild = p->rChild = 0;
			p->data = x;
			if (!root) root = p;	// ����ԭp
			else if (x.key < q->data.key) q->lChild = p;
			else q->rChild = p;
			return true;
		}

		BstNode *searchNode(const Element &x)
		{
			return searchNode(root, x);
		}

		BstNode *searchNode(BstNode *b, const Element &x)
		{
			if (!b) return 0;
			if (x.key == b->data.key) return b;
			if (x.key < b->data.key) return searchNode(b->lChild, x);
			return searchNode(b->rChild, x);
		}

		BstNode *searchNodeIter(const Element &x)
		{
			for (BstNode *t = root; t; )
			{
				if (x.key < t->data.key)
					t = t->lChild;
				else
					t = t->rChild;
			}
			return 0;
		}

		void displayTree() {
			if (root) root->display(1);
		}
	private:
		BstNode *root;
	};

	class isTree
	{
	public:
		isTree() {}
		~isTree() {}
		class ReturnData {
		public:
			bool isBalance;
			int h;
			ReturnData(bool isBalance, int h) : isBalance(isBalance), h(h) {}
		};

		ReturnData * process(TreeNode *head) {
			if (head == nullptr) {		//�ն�����Ϊƽ�������
				return new ReturnData(true, 0);
			}
			ReturnData *leftData = process(head->left);
			if (!leftData->isBalance) {
				return new ReturnData(false, 0);
			}
			ReturnData *rightData = process(head->right);
			if (!rightData->isBalance) {
				return new ReturnData(false, 0);
			}
			if (abs(leftData->h - rightData->h) > 1) {
				return new ReturnData(false, 0);
			}
			return new ReturnData(true, std::max(leftData->h, rightData->h) + 1);
		}
		// �ж�һ���������Ƿ�Ϊƽ�������
		// BT:ƽ�������->���������������ĸ߶Ȳ����1
		bool isBalance(TreeNode* head) {
			return process(head)->isBalance;
		}
		/*********************************************************
		bool isBST_InOrder(TreeNode *head);
		�ж϶������Ƿ�������������(Morris����)
		parameter:
		@head:��ʼ��ַ
		return:
		�жϽ��(true/false)
		**********************************************************/
		bool isBST_Morris(TreeNode *head) {
			if (head == nullptr) {
				return true;
			}
			bool res = true;
			TreeNode *pre = nullptr;
			TreeNode *cur1 = head;		//cur1ָ��ͷ�ڵ�
			TreeNode *cur2 = nullptr;
			while (cur1 != nullptr) {
				cur2 = cur1->left;		//cur2ָ��cur1������
				if (cur2 != nullptr) {
					//cur1�����������ҽڵ�
					while (cur2->right != nullptr && cur2->right != cur1) {
						cur2 = cur2->right;
					}
					if (cur2->right == nullptr) {
						cur2->right = cur1;	//���ҽڵ�ָ��cur1
						cur1 = cur1->left;
						continue;		//cur1ָ��cur1����������ֹ����ѭ��
					}
					else {
						cur2->right = nullptr;
					}
				}
				if (pre != nullptr && pre->value > cur1->value) {
					res = false;
				}
				pre = cur1;
				cur1 = cur1->right;
			}
			return res;
		}
		/*********************************************************
		bool isBST_InOrder(TreeNode *head);
		�ж϶������Ƿ�������������(�����������)
		parameter:
		@head:��ʼ��ַ
		return:
		�жϽ��(true/false)
		**********************************************************/
		bool isBST_InOrder(TreeNode *head) {
			if (head == nullptr) {
				return true;
			}
			std::cout << "In Order: ";
			std::stack<TreeNode *> *sta = new std::stack<TreeNode *>;
			TreeNode *cur = head;
			int min = INT16_MIN;
			while (!sta->empty() || cur != nullptr) {
				if (cur != nullptr) {		//�����������������Ƚ�
					sta->push(cur);			//ȫ������0��������������
					cur = cur->left;
				}
				else {
					cur = sta->top();
					sta->pop();
					//			cout << cur->value << " ";
					if ((cur->value - min) > 0) {
						min = cur->value;
					}
					else {
						return false;
					}
					cur = cur->right;
				}
			}
			std::cout << std::endl;
			return true;
		}
		/*********************************************************
		bool isCBT(TreeNode *head);
		�ж϶������Ƿ�����ȫ������(�������)
		parameter:
		@head:��ʼ��ַ
		return:
		�жϽ��(true/false)
		**********************************************************/
		bool isCBT(TreeNode *head) {
			if (head == nullptr) {
				return true;
			}
			std::queue<TreeNode *> *que = new std::queue<TreeNode *>;
			bool leaf = false;
			TreeNode *left = nullptr;
			TreeNode *right = nullptr;
			TreeNode *cur = head;
			que->push(cur);		//ѹ���׵�ַ
			while (!que->empty()) {
				cur = que->front();		//ָ�����que��һλ
				que->pop();
				if (leaf && (cur->left != nullptr || cur->right != nullptr)	//ֻҪ������Ҷ�ڵ㣬��ô֮����Ҷ�ڵ�
					|| (cur->right != nullptr && cur->left == nullptr)) {	//��Ϊ���Ҳ�Ϊ�գ�һ����ΪCBT
					return false;											//�������Ҷ�ڵ㣬��ôʣ��ڵ��ΪҶ�ڵ�
				}
				if (cur->left != nullptr) {
					que->push(cur->left);
				}
				if (cur->right != nullptr) {
					que->push(cur->right);
				}
				if (cur->left == nullptr || cur->right == nullptr) {	//�ҵ�Ҷ�ڵ�
					leaf = true;
				}
			}
			return true;
		}
	private:

	};
}

int main() {
	MyTree::TreeNode *head = new MyTree::TreeNode(0);
	head->left = new MyTree::TreeNode(1);
	head->right = new MyTree::TreeNode(2);
	head->left->left = new MyTree::TreeNode(3);
	head->left->right = new MyTree::TreeNode(4);
	head->right->left = new MyTree::TreeNode(5);
	head->right->right = new MyTree::TreeNode(6);
	head->left->left->left = new MyTree::TreeNode(7);
	head->left->left->right = new MyTree::TreeNode(8);

	MyTree::printTree pTree;
	pTree.printLayer(head);

	// �ݹ�
	pTree.printInPreOrdered(head);
	std::cout << std::endl;
	pTree.printInOrdered(head);
	std::cout << std::endl;
	pTree.printInPostOrdered(head);
	std::cout << std::endl;

	// ����
	pTree.printInPreOrderedIter(head);
	pTree.printInOrderedIter(head);
	pTree.printInPostOrderedIter(head);

	// BST
	MyTree::BST bst;
	MyTree::BST::Element a, b, c, d, e, f, g, h, i, j;
	a.key = 5;
	b.key = 3;
	c.key = 11;
	d.key = 3;
	e.key = 15;
	f.key = 2;
	g.key = 8;
	h.key = 22;
	i.key = 20;
	j.key = 9;
	std::cout << bst.insertNode(a) << std::endl;
	std::cout << bst.insertNode(b) << std::endl;
	std::cout << bst.insertNode(c) << std::endl;
	std::cout << bst.insertNode(d) << std::endl;
	std::cout << bst.insertNode(e) << std::endl;
	std::cout << bst.insertNode(f) << std::endl;
	std::cout << bst.insertNode(g) << std::endl;
	std::cout << bst.insertNode(h) << std::endl;
	bst.displayTree();

	return 0;
}