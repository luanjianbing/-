#include <iostream>

namespace MyQueue {
#define QUEUECAP 10
	// 顺序队列
	class SequentialQueue
	{
	public:
		SequentialQueue(int queueCapcity = QUEUECAP) : capacity(queueCapcity)
		{
			if (queueCapcity < 1) throw"Queue capcity must be > 0";
			queue = new int[capacity];
			front = rear = 0;
		}
		~SequentialQueue() {}
		inline bool isEmpty() const {
			return front == rear;
		}

		int getFront() const{
			if (isEmpty()) throw"Queue is empty";
			return queue[(front + 1) % capacity];
		}

		int getRear() const {
			if (isEmpty()) throw"Queue is empty";
			return queue[rear];
		}

		void push(const int &item) {
			if ((rear + 1) % capacity == front) {
				// 队列满了
				int *newQueue = new int[2 * capacity];
				
				int start = (front + 1) % capacity;
				if (start < 2)	// 没有回转
					std::copy(queue + start, queue + start +capacity - 1, newQueue);
				else {
					std::copy(queue + start, queue + capacity, newQueue);
					std::copy(queue, queue + rear +1, newQueue + capacity - start);
				}
				front = 2 * capacity - 1;
				rear = capacity - 2;
				capacity *= 2;
				delete queue;
				queue = newQueue;
			}
			rear = (rear + 1) % capacity;
			queue[rear] = item;	// 队尾压进队列
		}

		void pop() {
			if (isEmpty()) throw"Queue is empty";
			front = (front + 1) % capacity;
			//queue[front] = 0;	
		}

	private:
		int *queue;
		int front;
		int rear;	// 队尾
		int capacity;
	};

	// 链式队列
	class LinkedQueue
	{
	public:
		LinkedQueue() {
			front = back = 0;
		}
		~LinkedQueue() {
			makeEmpty();
		}

		bool isEmpty() const {
			return front == 0;
		}

		const int &getFront() const {
			if (isEmpty()) throw "Queue is empty";
			return front->element;
		}

		void enQueue(const int &x) {
			if (isEmpty())
				back = front = new Node(x);
			else
				back = back->next = new Node(x);
		}

		int deQueue() {
			int frontItem = getFront();

			Node *old = front;
			front = front->next;
			delete old;

			return frontItem;
		}

		void makeEmpty() {
			while (!isEmpty())
				deQueue();
		}

	private:
		struct Node
		{
			int element;
			Node *next;
			Node(const int &element, Node *n = 0)
				:element(element), next(n) {}
		};
		Node *front;
		Node *back;
	};
}

int main() {
	// 顺序队列
	std::cout << "顺序队列" << std::endl;
	MyQueue::SequentialQueue sQueue;
	std::cout << sQueue.isEmpty() << std::endl;
	sQueue.push(5);
	sQueue.push(2);
	std::cout << sQueue.isEmpty() << std::endl;
	std::cout << sQueue.getFront() << std::endl;
	std::cout << sQueue.getRear() << std::endl;
	sQueue.push(4);
	sQueue.push(3);
	sQueue.pop();
	std::cout << sQueue.getFront() << std::endl;
	std::cout << sQueue.getRear() << std::endl;

	// 链式队列
	std::cout << "链式队列" << std::endl;
	MyQueue::LinkedQueue lQueue;
	std::cout << lQueue.isEmpty() << std::endl;
	lQueue.enQueue(5);
	lQueue.enQueue(2);
	std::cout << lQueue.isEmpty() << std::endl;
	std::cout << lQueue.getFront() << std::endl;
	lQueue.enQueue(4);
	lQueue.enQueue(3);
	std::cout << lQueue.deQueue() << std::endl;
	std::cout << lQueue.getFront() << std::endl;

	return 0;
}