#include <iostream>

#define MAXHEAPSIZE 100
class MaxHeap
{
public:
	MaxHeap(int maxSize = MAXHEAPSIZE) 
	{
		if (maxSize < 1) throw "max size must be > 1";
		this->maxSize = maxSize;
		currentSize = 0;
		heapArray = new int[maxSize];

	}
	virtual ~MaxHeap() 
	{
		delete[] heapArray;
	}

	bool isEmpty() 
	{
		return currentSize == 0;
	}

	void trickleUp(int idx)
	{
		int parent = (idx - 1) / 2;	//父节点
		int bottom = heapArray[idx];	//取出最后的数值
		while (idx > 0 && heapArray[parent] < bottom)
		{
			heapArray[idx] = heapArray[parent];	// 小的向下
			idx = parent;
			parent = (parent - 1) / 2;	// 逐步向上跟父节点比较
		}
		heapArray[idx] = bottom;	// 找到终点赋值
	}

	void pushTreeNode(const int &e)
	{
		if (currentSize == maxSize) throw "maxHeap is full";

		heapArray[currentSize] = e;	// 对于大根堆来说，新压入的数据都是在最后
		trickleUp(currentSize++);	// 调整大根堆--大的往上升
	}

	void trickleDown(int idx)
	{
		int largerChild;
		int top = heapArray[idx];
		while (idx < currentSize / 2)	// 最后一层的上一层
		{
			int lChild = 2 * idx + 1;
			int rChild = lChild + 1;
			if (rChild < currentSize && heapArray[lChild] < heapArray[rChild])
				largerChild = rChild;
			else
				largerChild = lChild;
			if (top >= heapArray[largerChild])
				break;
			heapArray[idx] = heapArray[largerChild];
			idx = largerChild;
		}
		heapArray[idx] = top;	// 临时的根渗透到这个位置
	}
	// 弹出根节点，调整顺序，使其是大根堆
	void popTreeNode()
	{
		heapArray[0] = heapArray[--currentSize];
		trickleDown(0);
	}

	const int & getTop() const
	{
		return heapArray[0];
	}

private:
	int *heapArray;
	int maxSize;
	int currentSize;
};

int main() {
	MaxHeap mHeap(100);
	std::cout << mHeap.isEmpty() << std::endl;

	mHeap.pushTreeNode(20);
	mHeap.pushTreeNode(30);
	mHeap.pushTreeNode(15);
	std::cout << mHeap.getTop() << std::endl;
	mHeap.pushTreeNode(90);
	mHeap.pushTreeNode(35);
	std::cout << mHeap.getTop() << std::endl;
	mHeap.popTreeNode();
	std::cout << mHeap.getTop() << std::endl;

	return 0;
}