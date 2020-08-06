#include <iostream>

struct Node
{
	bool isEnd;	// 判断当前字母是否是最后一个字母标识
	Node *next[26];	// 26个字母分叉
	Node() {
		isEnd = false;
		for (int i = 0; i < 26; ++i)
		{
			next[i] = nullptr;// 清空26叉
		}
	}
};

class DicTree {
private:
	Node *root = new Node();	// 根节点
public:

	// 插入string字符串
	void insert(std::string str) {
		Node *tmpPtr = root;	// 定义一个临时节点指向根节点
		for (int i = 0; i < str.length(); ++i) {
			int numIdx = str[i] - 'a';	// 获取当前字母应该存储的位置
			if (tmpPtr->next[numIdx] == nullptr)
				tmpPtr->next[numIdx] = new Node();
			tmpPtr = tmpPtr->next[numIdx];
		}
		// 插入完毕后修改该节点的标识位
		tmpPtr->isEnd = true;
	}
	// 搜索string字符串判断是否存在
	bool search(std::string str) {
		Node *tmpPtr = root;	// 定义个临时节点指向根节点
		for (int i = 0; i < str.length(); ++i) {
			int numIdx = str[i] - 'a';	// 获取当前字母索引
			if (tmpPtr->next[numIdx] == nullptr)
				return false;
			else
				tmpPtr = tmpPtr->next[numIdx];
		}
		return tmpPtr->isEnd;
	}
};


int main() {
	std::string str1 = "abcd";
	std::string str2 = "cdefg";
	std::string str3 = "hijkl";

	DicTree dTree;
	dTree.insert(str1);
	dTree.insert(str2);
	dTree.insert(str3);

	bool res1 = dTree.search(str1);
	bool res2 = dTree.search(str2);
	bool res3 = dTree.search("cde");
	bool res4 = dTree.search(str3);
	bool res5 = dTree.search("jkl");

	std::cout << res1 << std::endl;
	std::cout << res2 << std::endl;
	std::cout << res3 << std::endl;
	std::cout << res4 << std::endl;
	std::cout << res5 << std::endl;

	return 0;
}
