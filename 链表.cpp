#include <iostream>

namespace MyListNode {
	// ��������
	template <class Type> class List;	// ����

	template <class Type>
	class ListNode
	{
		friend class List<Type>;
	private:
		Type data;
		ListNode *link;
		ListNode(Type element) {
			data = element;
			link = 0;
		}
	};

	template <class Type>
	class List
	{
	public:
		List() 
		{
			first = 0;
		}

		void insertNode(Type k) {
			ListNode<Type> *newNode = new ListNode<Type>(k);
			newNode->link = first;
			first = newNode;
		}

		void deleteNode(Type k) {
			ListNode<Type> *previous = 0;	// ǰһ��
			ListNode<Type> *cur;
			for (cur = first;
				cur && cur->data != k;
				previous = cur, cur = cur->link)
			{
				// ʲô����������ѭ�����ҵ�Ҫ��ɾ���Ľڵ�
			}
			if (cur) {
				if (previous) previous->link = cur->link;
				else first = first->link;
				delete cur;
			}
		}

		void invertNode() 
		{
			ListNode<Type> *p = first, *q = 0;
			while (p)
			{
				ListNode<Type> *r = q;
				q = p;
				p = p->link;
				q->link = r;
			}
			first = q;
		}

		void concatenateNode(List<Type> b)
		{
			if (!first)
			{
				first = b.first;
				return;
			}
			else
			{
				ListNode<Type> *p;
				for (p = first; p->link; p = p->link);	// ��ѭ��
				p->link = b.first;
			}
		}

		void show() {
			for (ListNode<Type> *cur = first; cur; cur = cur->link)
			{
				std::cout << cur->data;
				if (cur->link) std::cout << "->";
			}
			std::cout << std::endl;
		}
	private:
		ListNode<Type> *first;
	};

	// ˫������(������)
	template <class Type> class DoubleList;		// ����

	template <class Type>
	class DoubleListNode
	{
		friend class DoubleList<Type>;
	private:
		Type data;
		DoubleListNode *lLink, *rLink;
	};

	template <class Type>
	class DoubleList
	{
	public:
		DoubleList()
		{
			first = new DoubleListNode<Type>();
			first->lLink = first->rLink = first;
		}

		void insertNode(DoubleListNode<Type> *p, DoubleListNode<Type> *x)
		{
			p->lLink = x;
			p->rLink = x->rLink;
			x->rLink->lLink = p;
			x->rLink = p;
		}

		void deleteNode(DoubleListNode<Type> *x)
		{
			if (x == first)
				// һ��cerr������ʾ������Ϣ
				std::cerr << "Deletion of head node not permitted" << std::endl;
			else
			{
				x->lLink->rLink = x->rLink;
				x->rLink->lLink = x->lLink;
				delete x;
			}
		}
	private:
		DoubleListNode<Type> *first;	// ָ���ͷ�ṹ
	};
}

int main() {
	std::cout << "��������" << std::endl;
	MyListNode::List<int> intList;
	intList.insertNode(5);
	intList.insertNode(15);
	intList.insertNode(25);
	intList.insertNode(35);
	intList.show();

	intList.deleteNode(15);
	intList.show();

	intList.invertNode();
	intList.show();
	
	MyListNode::List<int> intListForCat;
	intListForCat.insertNode(6);
	intListForCat.insertNode(7);
	intListForCat.insertNode(8);
	intListForCat.show();

	intList.concatenateNode(intListForCat);
	intList.show();

	std::cout << "˫������" << std::endl;
	MyListNode::DoubleList<int> intDoubleList;
	MyListNode::DoubleListNode<int> *node1, *node2, *node3;
	node1 = new MyListNode::DoubleListNode<int>();
	node2 = new MyListNode::DoubleListNode<int>();
	node3 = new MyListNode::DoubleListNode<int>();

	// ����data�������private���������ڴ˴���node1->data����

	delete node1;
	delete node2;
	delete node3;

	return 0;
}