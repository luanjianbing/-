//先序遍历: 中->左->右
//中序遍历: 左->中->右
//后序遍历: 左->右->中
#include<iostream>
#include<queue>
#include<stack>

using namespace std;

//二叉树
class TreeNode {
public:
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int value):value(value), left(nullptr), right(nullptr){}
};

/********************************************************
***********************递归遍历↓***********************
********************************************************/

/*********************************************************
void printPreorder1(TreeNode *head);
	先序(中->左->右)遍历打印二叉树(递归)
parameter:
	@head:二叉树的起始地址
return:
	None
**********************************************************/
void printPreorder1(TreeNode *head) {
	if (head == nullptr) {
		return;
	}
	cout << head->value << " ";
	printPreorder1(head->left);
	printPreorder1(head->right);
}
/*********************************************************
void printInorder1(TreeNode *head);
	中序(左->中->右)遍历打印二叉树(递归)
parameter:
	@head:二叉树的起始地址
return:
	None
**********************************************************/
void printInorder1(TreeNode *head) {
	if (head == nullptr) {
		return;
	}
	printInorder1(head->left);
	cout << head->value << " ";
	printInorder1(head->right);
}
/*********************************************************
void printInorder1(TreeNode *head);
	后序(左->右->中)遍历打印二叉树(递归)
parameter:
	@head:二叉树的起始地址
return:
	None
**********************************************************/
void printPostorder1(TreeNode *head) {
	if (head == nullptr) {
		return;
	}
	printPostorder1(head->left);
	printPostorder1(head->right);
	cout << head->value << " ";
}

/********************************************************
***********************迭代遍历↓***********************
********************************************************/

/*********************************************************
void printPreorder2(TreeNode *head);
	先序(中->左->右)遍历打印二叉树(迭代)
parameter:
	@head:二叉树的起始地址
return:
	None
**********************************************************/
void printPreorder2(TreeNode *head) {
	cout << "Pre Order: ";
	if (head != nullptr) {
		stack<TreeNode *> *sta = new stack<TreeNode *>;
		sta->push(head);
		TreeNode *cur = head;
		while (!sta->empty()) {
			cur = sta->top();
			sta->pop();
			cout << cur->value << " ";
			if (cur->right != nullptr) {	 // 先压右边节点，再压左边节点
				sta->push(cur->right);
			}
			if (cur->left != nullptr) {		//出栈的时候就先出左树，再出右树
				sta->push(cur->left);
			}
		}
	}
}
/*********************************************************
void printInorder2(TreeNode *head);
	中序(左->中->右)遍历打印二叉树(迭代)
parameter:
	@head:二叉树的起始地址
return:
	None
**********************************************************/
void printInorder2(TreeNode *head) {
	cout << "In Order: ";
	if (head != nullptr) {
		stack<TreeNode *> *sta = new stack<TreeNode *>;
		TreeNode *cur = head;
		while (!sta->empty() || cur !=nullptr) {	//栈不为空或当前指向不为空
			if (cur != nullptr) {
				sta->push(cur);
				cur = cur->left;
			}
			else {
				cur = sta->top();
				sta->pop();
				cout << cur->value << " ";
				cur = cur->right;
			}
		}
	}
}
/*********************************************************
void printPostorder2(TreeNode *head);
	后序(左->右->中)遍历打印二叉树(迭代)
parameter:
	@head:二叉树的起始地址
return:
	None
**********************************************************/
void printPostorder2(TreeNode *head) {
	cout << "Post Order: ";
	if (head != nullptr) {
		stack<TreeNode *> *sta1 = new stack<TreeNode *>;
		stack<TreeNode *> *sta2 = new stack<TreeNode *>;
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
			cout << cur->value << " ";
		}
	}
}

/*********************************************************
void printLayer(TreeNode* head);
	打印二叉树(使用队列queue)
parameter:
	@head:二叉树的起始地址
return:
	None
**********************************************************/
void printLayer(TreeNode* head) {
	cout << "Layer Order:" << endl;
	if (head == nullptr) {
		return;
	}
	queue<TreeNode*> q;		//队列q里存放二叉树型的指针
	q.push(head);		//压入首地址
	while (!q.empty()) {		
		TreeNode* cur = q.front();		//cur指向第一位
		q.pop();					//弹出第一位
		cout << cur->value << " ";	//打印第一位的value
		if (cur->left != nullptr) {		//压入当前指向位置的左树的地址
			q.push(cur->left);
		}
		if (cur->right != nullptr) {	//压入当前指向位置的右数的地址
			q.push(cur->right);
		}
	}	//先左后右打印二叉树
	cout << endl;
}

int main() {
	TreeNode *head = new TreeNode(0);
	head->left = new TreeNode(1);
	head->right = new TreeNode(2);
	head->left->left = new TreeNode(3);
	head->left->right = new TreeNode(4);
	head->right->left = new TreeNode(5);
	head->right->right = new TreeNode(6);
	head->left->left->left = new TreeNode(7);
	head->left->left->right = new TreeNode(8);

	printLayer(head);
	cout << endl;

	//递归
	printPreorder1(head);
	cout << endl;
	printInorder1(head);
	cout << endl;
	printPostorder1(head);
	cout << endl;

	//迭代
	printPreorder2(head);
	cout << endl;
	printInorder2(head);
	cout << endl;
	printPostorder2(head);
	cout << endl;

	system("pause");
	return 0;
}
