#include <iostream>
#include <string>
// 红黑树: 高级的二叉查找树(左子树小，右子树大，无相等键值)
// 节点都有颜色，插入和删除节点时要遵守红黑规则
// 1.每个节点不是红色就是黑色
// 2.根是黑色
// 3.节点是红色，子节点必须黑色
// 4.从根节点到叶节点的每条路径，必须包含相同数目的黑色节点

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
		// 调用基类构造函数
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
			//// 自动平衡 -> 红黑树
			//handleReorient(x);
		}

		// Cerf<Comparable>自己做的引用类型
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

	//// 为了方便测试，暂时变成公有
	//public:
	private:
		Node *header;
		Node *nullNode;

		Node *currentNode;
		Node *paraentNode;	// 父节点
		Node *grandNode;	// 祖父节点
		Node *greatNode;	// 曾祖父节点

		// 向右单转
		void rotateWithLeftChild(Node * &k2) const
		{
			Node *k1 = k2->lChild;
			k2->lChild = k1->rChild;
			k1->rChild = k2;
			k2 = k1;	// k1替代k2称为根节点
		}
		// 向左单转
		void rotateWithRightChild(Node * &k1) const
		{
			Node *k2 = k1->rChild;
			k1->rChild = k2->lChild;
			k2->lChild = k1;
			k1 = k2;	// k2替代k1称为根节点
		}
		// 向右双转
		void doubleRotateWithLeftChild(Node * &k3) const
		{
			rotateWithRightChild(k3->lChild);
			rotateWithLeftChild(k3);
		}
		// 向左双转
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
					// 内部孙子节点多一次旋转
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
		friend class RedBlackTree<Comparable>;	// 友元类调用私有
	//// 为了方便测试，暂时变成公有
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
	// 这个类写的有问题，可以把他拿到外面用class名::func名这种写法试试
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