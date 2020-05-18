#include <iostream>

namespace MyStack {
#define STACKCAP 10
	// 顺序栈
	class SequentialStack
	{
	public:
		SequentialStack(int stackCapacity = STACKCAP):capcity(stackCapacity) {
			if (capcity < 1) throw "stack capcity must be > 0";
			stack = new int[capcity];
			top = -1;
		}
		~SequentialStack() {
			delete[]stack;
		}

		bool isEmpty() const {
			return top == -1;
		}

		int getTop() const {
			if (this->isEmpty()) throw "stack is empty";
			return stack[top];
		}

		void push(const int &item) {
			stack[++top] = item;
		}

		void pop() {
			if (this->isEmpty()) throw "stack is empty";
			stack[top--];
		}

	private:
		int *stack;
		int top;
		int capcity;
	};

	// 链式栈(用链表做的堆栈)
	// 链式结构
	//class Node {
	//public:
	//	int value;
	//	Node *next = nullptr;
	//	Node(int value) {
	//		this->value = value;
	//	}
	//};
	class ChainNode 
	{
		friend class LinkedStack;
	private:
		ChainNode(const int &data, ChainNode *n = 0)
			: data(data), link(n) {}
		int data;
		ChainNode *link;
	};
	class LinkedStack
	{
	public:
		LinkedStack() :top(nullptr) {}
		~LinkedStack() { makeEmpty(); }

		bool isEmpty() const {
			return top == nullptr;
		}

		int getTop() const {
			if (this->isEmpty()) throw "stack is empty";
			return top->data;
		}

		void push(const int &e) {
			top = new ChainNode(e, top);
		}
		void pop() {
			if (this->isEmpty()) throw "stack is empty";
			ChainNode *delNode = top;
			top = top->link;
			delete delNode;
		}
		void makeEmpty() {
			while (!this->isEmpty()) {
				this->pop();
			}
		}

	private:
		ChainNode *top;
	};
	
}

int main() {

	MyStack::SequentialStack s(10);
	std::cout << "顺序栈" << std::endl;
	std::cout << s.isEmpty() << std::endl;
	s.push(2);
	s.push(5);
	std::cout << s.getTop() << std::endl;
	std::cout << s.isEmpty() << std::endl;
	s.pop();
	std::cout << s.getTop() << std::endl;

	std::cout << "链式栈" << std::endl;
	MyStack::LinkedStack ls;
	std::cout << ls.isEmpty() << std::endl;
	ls.push(2);
	ls.push(5);
	std::cout << ls.getTop() << std::endl;
	std::cout << ls.isEmpty() << std::endl;
	ls.pop();
	std::cout << ls.getTop() << std::endl;

	return 0;
}