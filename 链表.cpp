#include <iostream>

namespace MyListNode {
	template <class Type> class List;

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
			ListNode<Type> *previous = 0;	// 前一个
			ListNode<Type> *cur;
			for (cur = first;
				cur && cur->data != k;
				previous = cur, cur = cur->link)
			{
				// 什么都不做，空循环，找到要被删除的节点
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
				for (p = first; p->link; p = p->link);	// 空循环
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
}

int main() {
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

	return 0;
}