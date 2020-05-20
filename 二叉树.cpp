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
		//先序遍历: 中->左->右
		// 先序遍历(递归)
		void printInPreOrdered(TreeNode *head) {
			if (head == nullptr) return;
			std::cout << head->value << " ";	// 中
			printInPreOrdered(head->left);		// 左
			printInPreOrdered(head->right);		// 右
		}
		// 先序遍历(迭代)
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
					if (cur->right != nullptr) {	 // 先压右边节点，再压左边节点
						sta->push(cur->right);
					}
					if (cur->left != nullptr) {		//出栈的时候就先出左树，再出右树
						sta->push(cur->left);
					}
				}
				std::cout << std::endl;
			}
		}

		//中序遍历: 左->中->右
		// 中序遍历(递归)
		void printInOrdered(TreeNode *head) {
			if (head == nullptr) return;
			printInOrdered(head->left);		// 左
			std::cout << head->value << " ";	// 中
			printInOrdered(head->right);		// 右
		}
		// 中序遍历(迭代)
		void printInOrderedIter(TreeNode *head) {
			std::cout << "In Order: ";
			if (head != nullptr) {
				std::stack<TreeNode *> *sta = new std::stack<TreeNode *>;
				TreeNode *cur = head;
				while (!sta->empty() || cur != nullptr) {	//栈不为空或当前指向不为空
					if (cur != nullptr) {	// 先把左边压进去
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

		//后序遍历: 左->右->中
		// 后序遍历(递归)
		void printInPostOrdered(TreeNode *head) {
			if (head == nullptr) return;
			printInPostOrdered(head->left);		// 左
			printInPostOrdered(head->right);		// 右
			std::cout << head->value << " ";	// 中
		}
		// 后序遍历(迭代)
		void printInPostOrderedIter(TreeNode *head) {
			std::cout << "Post Order: ";
			if (head != nullptr) {
				std::stack<TreeNode *> *sta1 = new std::stack<TreeNode *>;
				std::stack<TreeNode *> *sta2 = new std::stack<TreeNode *>;
				TreeNode *cur = head;
				sta1->push(cur);	//压入首地址
				while (!sta1->empty()) {
					cur = sta1->top();
					sta1->pop();
					sta2->push(cur);	//sta1弹出，sta2压入
					if (cur->left != nullptr) {		//按照中左右的顺序压入栈
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

		// 使用队列打印二叉树
		void printLayer(TreeNode* head) {
			std::cout << "Layer Order:" << std::endl;
			if (head == nullptr) {
				return;
			}
			std::queue<TreeNode*> q;		//队列q里存放二叉树型的指针
			q.push(head);		//压入首地址
			while (!q.empty()) {
				TreeNode* cur = q.front();		//cur指向第一位
				q.pop();					//弹出第一位
				std::cout << cur->value << " ";	//打印第一位的value
				if (cur->left != nullptr) {		//压入当前指向位置的左树的地址
					q.push(cur->left);
				}
				if (cur->right != nullptr) {	//压入当前指向位置的右数的地址
					q.push(cur->right);
				}
			}	//先左后右打印二叉树
			std::cout << std::endl;
		}
	private:

	};

	// 二叉查找树(BST)
	// 1.每个元素都有一个键值，而且不重复
	// 2.左子树的键值都小于根节点的键值
	// 3.右子树的键值都大于根节点的键值
	// 4.左右子树都是二叉查找树
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
			BstNode *q = 0;	// q指向p的父节点
			while (p)
			{
				q = p;
				if (x.key == p->data.key) return false;	// 重复
				if (x.key < p->data.key) p = p->lChild;
				else p = p->rChild;
			}
			// 找到的位置就是q
			p = new BstNode;
			p->lChild = p->rChild = 0;
			p->data = x;
			if (!root) root = p;	// 赋回原p
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
			if (head == nullptr) {		//空二叉树为平衡二叉树
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
		// 判断一个二叉树是否为平衡二叉树
		// BT:平衡二叉树->左子树和右子树的高度差不超过1
		bool isBalance(TreeNode* head) {
			return process(head)->isBalance;
		}
		/*********************************************************
		bool isBST_InOrder(TreeNode *head);
		判断二叉树是否是搜索二叉树(Morris方法)
		parameter:
		@head:起始地址
		return:
		判断结果(true/false)
		**********************************************************/
		bool isBST_Morris(TreeNode *head) {
			if (head == nullptr) {
				return true;
			}
			bool res = true;
			TreeNode *pre = nullptr;
			TreeNode *cur1 = head;		//cur1指向头节点
			TreeNode *cur2 = nullptr;
			while (cur1 != nullptr) {
				cur2 = cur1->left;		//cur2指向cur1左子树
				if (cur2 != nullptr) {
					//cur1左子树的最右节点
					while (cur2->right != nullptr && cur2->right != cur1) {
						cur2 = cur2->right;
					}
					if (cur2->right == nullptr) {
						cur2->right = cur1;	//最右节点指向cur1
						cur1 = cur1->left;
						continue;		//cur1指向cur1左子树，终止本次循环
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
		判断二叉树是否是搜索二叉树(中序遍历方法)
		parameter:
		@head:起始地址
		return:
		判断结果(true/false)
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
				if (cur != nullptr) {		//中序遍历左中右做差比较
					sta->push(cur);			//全都大于0则是搜索二叉树
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
		判断二叉树是否是完全二叉树(按层遍历)
		parameter:
		@head:起始地址
		return:
		判断结果(true/false)
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
			que->push(cur);		//压入首地址
			while (!que->empty()) {
				cur = que->front();		//指向队列que第一位
				que->pop();
				if (leaf && (cur->left != nullptr || cur->right != nullptr)	//只要遍历到叶节点，那么之后都是叶节点
					|| (cur->right != nullptr && cur->left == nullptr)) {	//左为空右不为空，一定不为CBT
					return false;											//如果到达叶节点，那么剩余节点必为叶节点
				}
				if (cur->left != nullptr) {
					que->push(cur->left);
				}
				if (cur->right != nullptr) {
					que->push(cur->right);
				}
				if (cur->left == nullptr || cur->right == nullptr) {	//找到叶节点
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

	// 递归
	pTree.printInPreOrdered(head);
	std::cout << std::endl;
	pTree.printInOrdered(head);
	std::cout << std::endl;
	pTree.printInPostOrdered(head);
	std::cout << std::endl;

	// 迭代
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