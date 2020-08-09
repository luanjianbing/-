//�������: ��->��->��
//�������: ��->��->��
//�������: ��->��->��
#include<iostream>
#include<queue>
#include<stack>

using namespace std;

//������
class TreeNode {
public:
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int value):value(value), left(nullptr), right(nullptr){}
};

/********************************************************
***********************�ݹ������***********************
********************************************************/

/*********************************************************
void printPreorder1(TreeNode *head);
	����(��->��->��)������ӡ������(�ݹ�)
parameter:
	@head:����������ʼ��ַ
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
	����(��->��->��)������ӡ������(�ݹ�)
parameter:
	@head:����������ʼ��ַ
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
	����(��->��->��)������ӡ������(�ݹ�)
parameter:
	@head:����������ʼ��ַ
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
***********************����������***********************
********************************************************/

/*********************************************************
void printPreorder2(TreeNode *head);
	����(��->��->��)������ӡ������(����)
parameter:
	@head:����������ʼ��ַ
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
			if (cur->right != nullptr) {	 // ��ѹ�ұ߽ڵ㣬��ѹ��߽ڵ�
				sta->push(cur->right);
			}
			if (cur->left != nullptr) {		//��ջ��ʱ����ȳ��������ٳ�����
				sta->push(cur->left);
			}
		}
	}
}
/*********************************************************
void printInorder2(TreeNode *head);
	����(��->��->��)������ӡ������(����)
parameter:
	@head:����������ʼ��ַ
return:
	None
**********************************************************/
void printInorder2(TreeNode *head) {
	cout << "In Order: ";
	if (head != nullptr) {
		stack<TreeNode *> *sta = new stack<TreeNode *>;
		TreeNode *cur = head;
		while (!sta->empty() || cur !=nullptr) {	//ջ��Ϊ�ջ�ǰָ��Ϊ��
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
	����(��->��->��)������ӡ������(����)
parameter:
	@head:����������ʼ��ַ
return:
	None
**********************************************************/
void printPostorder2(TreeNode *head) {
	cout << "Post Order: ";
	if (head != nullptr) {
		stack<TreeNode *> *sta1 = new stack<TreeNode *>;
		stack<TreeNode *> *sta2 = new stack<TreeNode *>;
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
			cout << cur->value << " ";
		}
	}
}

/*********************************************************
void printLayer(TreeNode* head);
	��ӡ������(ʹ�ö���queue)
parameter:
	@head:����������ʼ��ַ
return:
	None
**********************************************************/
void printLayer(TreeNode* head) {
	cout << "Layer Order:" << endl;
	if (head == nullptr) {
		return;
	}
	queue<TreeNode*> q;		//����q���Ŷ������͵�ָ��
	q.push(head);		//ѹ���׵�ַ
	while (!q.empty()) {		
		TreeNode* cur = q.front();		//curָ���һλ
		q.pop();					//������һλ
		cout << cur->value << " ";	//��ӡ��һλ��value
		if (cur->left != nullptr) {		//ѹ�뵱ǰָ��λ�õ������ĵ�ַ
			q.push(cur->left);
		}
		if (cur->right != nullptr) {	//ѹ�뵱ǰָ��λ�õ������ĵ�ַ
			q.push(cur->right);
		}
	}	//������Ҵ�ӡ������
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

	//�ݹ�
	printPreorder1(head);
	cout << endl;
	printInorder1(head);
	cout << endl;
	printPostorder1(head);
	cout << endl;

	//����
	printPreorder2(head);
	cout << endl;
	printInorder2(head);
	cout << endl;
	printPostorder2(head);
	cout << endl;

	system("pause");
	return 0;
}
