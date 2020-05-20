#include <iostream>
#include <string>
// �����: �߼��Ķ��������(������С��������������ȼ�ֵ)
// �ڵ㶼����ɫ�������ɾ���ڵ�ʱҪ���غ�ڹ���
// 1.ÿ���ڵ㲻�Ǻ�ɫ���Ǻ�ɫ
// 2.���Ǻ�ɫ
// 3.�ڵ��Ǻ�ɫ���ӽڵ�����ɫ
// 4.�Ӹ��ڵ㵽Ҷ�ڵ��ÿ��·�������������ͬ��Ŀ�ĺ�ɫ�ڵ�

namespace MyRedAndBlackTree {
	class DSException 
	{
	public:
		DSException(const std::string &msg = "") : message(msg) {}
		virtual ~DSException() {}
		virtual std::string toString() const
		{
			return "Exception " + std::string(": ") + what();
		}
		virtual std::string what() const
		{
			return message;
		}
	private:
		std::string message;
	};

	class DuplicateItemException : public DSException
	{
	public:
		// ���û��๹�캯��
		DuplicateItemException(const std::string &msg = "") : DSException(msg) {}
	};

	template <class Comparable>
	class RedBlackTree;

	template <class Comparable>
	class RedBlackNode;

	template <class Comparable>
	class RedBlackTree
	{
	public:
		typedef RedBlackNode<Comparable> Node;

		enum {RED, BLACK};

		RedBlackTree(const Comparable &negInf) 
		{
			nullNode = new Node();
			nullNode->lChild = nullNode->rChild = nullNode;
			header = new Node(negInf);
			header->lChild = header->rChild = nullNode;
		}

		~RedBlackTree()
		{
			delete nullNode;
			delete header;
		}

		void insertNode(const Comparable &x)
		{
			currentNode = paraentNode = grandNode = header;
			nullNode->element = x;

			while (currentNode->element != x)
			{
				greatNode = grandNode;
				grandNode = paraentNode;
				paraentNode = currentNode;
				currentNode = x < currentNode->element ? currentNode->lChild : currentNode->rChild;

				if (currentNode->lChild->color == RED && currentNode->rChild->color == RED)
					handleReorient(x);
			}

			if (currentNode != nullNode)
				throw DuplicateItemException();
			currentNode = new Node(x, nullNode, nullNode);
			if (x < paraentNode->element)
				paraentNode->lChild = currentNode;
			else
				paraentNode->rChild = currentNode;
			//// �Զ�ƽ�� -> �����
			//handleReorient(x);
		}

		// Cerf<Comparable>�Լ�������������
		Cerf<Comparable> find(const Comparable &x) const
		{

		}

		Cerf<Comparable> findMin() const
		{

		}

		bool isEmpty() const
		{
			return header->rChild == nullNode;
		}

		void makeEmpty()
		{
			reclaimMemory(header->rChild);
			header->rChild = nullNode;
		}

	//// Ϊ�˷�����ԣ���ʱ��ɹ���
	//public:
	private:
		Node *header;
		Node *nullNode;

		Node *currentNode;
		Node *paraentNode;	// ���ڵ�
		Node *grandNode;	// �游�ڵ�
		Node *greatNode;	// ���游�ڵ�

		// ���ҵ�ת
		void rotateWithLeftChild(Node * &k2) const
		{
			Node *k1 = k2->lChild;
			k2->lChild = k1->rChild;
			k1->rChild = k2;
			k2 = k1;	// k1���k2��Ϊ���ڵ�
		}
		// ����ת
		void rotateWithRightChild(Node * &k1) const
		{
			Node *k2 = k1->rChild;
			k1->rChild = k2->lChild;
			k2->lChild = k1;
			k1 = k2;	// k2���k1��Ϊ���ڵ�
		}
		// ����˫ת
		void doubleRotateWithLeftChild(Node * &k3) const
		{
			rotateWithRightChild(k3->lChild);
			rotateWithLeftChild(k3);
		}
		// ����˫ת
		void doubleRotateWithRightChild(Node * &k1) const
		{
			rotateWithLeftChild(k1->rChild);
			rotateWithRightChild(k1);
		}

		RedBlackNode<Comparable> *rotate(const Comparable &item, Node *theParaent) const
		{
			if (item < theParaent->element)
			{
				item < theParaent->lChild->element ?
					rotateWithLeftChild(theParaent->lChild) :
					rotateWithRightChild(theParaent->lChild);
				return theParaent->lChild;
			}
			else
			{
				item < theParaent->rChild->element ?
					rotateWithLeftChild(theParaent->rChild) :
					rotateWithRightChild(theParaent->rChild);
				return theParaent->rChild;
			}
		}

		void handleReorient(const Comparable &item)
		{
			currentNode->color = RED;
			currentNode->lChild->color = BLACK;
			currentNode->rChild->color = BLACK;

			if (paraentNode->color == RED)
			{
				grandNode->color = RED;
				if (item < grandNode->element != item < paraentNode->element)
					// �ڲ����ӽڵ��һ����ת
					paraentNode = rotate(item, grandNode);
				currentNode = rotate(item, greatNode);
				currentNode->color = BLACK;
			}
			header->rChild->color = BLACK;
		}

		void reclaimMemory(Node *t) const
		{
			if (t != t->lChild) 
			{
				reclaimMemory(t->lChild);
				reclaimMemory(t->rChild);
				delete t;
			}
		}
	};

	template <class Comparable>
	class RedBlackNode
	{
		friend class RedBlackTree<Comparable>;	// ��Ԫ�����˽��
	//// Ϊ�˷�����ԣ���ʱ��ɹ���
	//public:
	private:
		Comparable element;
		RedBlackNode *lChild;
		RedBlackNode *rChild;
		int color;

		RedBlackNode(const Comparable &element = Comparable(),
			RedBlackNode *lChild = NULL,
			RedBlackNode *rCild = NULL,
			int color = RedBlackTree<Comparable>::BLACK)
			: element(element), lChild(lChild), rChild(rChild), color(color) {}
	};
}

int main() {
	// �����д�������⣬���԰����õ�������class��::func������д������
	const int NEG_INF = -99999;
	MyRedAndBlackTree::RedBlackTree<int> rbt(NEG_INF);

	rbt.insertNode(50);
	rbt.insertNode(40);
	rbt.insertNode(30);

	//std::cout << rbt.header->rChild->element << std::endl;

	std::cout << rbt.isEmpty() << std::endl;

	//rbt.makeEmpty();

	//std::cout << rbt.isEmpty() << std::endl;

	return 0;
}