#include <iostream>

struct Node
{
	bool isEnd;	// �жϵ�ǰ��ĸ�Ƿ������һ����ĸ��ʶ
	Node *next[26];	// 26����ĸ�ֲ�
	Node() {
		isEnd = false;
		for (int i = 0; i < 26; ++i)
		{
			next[i] = nullptr;// ���26��
		}
	}
};

class DicTree {
private:
	Node *root = new Node();	// ���ڵ�
public:

	// ����string�ַ���
	void insert(std::string str) {
		Node *tmpPtr = root;	// ����һ����ʱ�ڵ�ָ����ڵ�
		for (int i = 0; i < str.length(); ++i) {
			int numIdx = str[i] - 'a';	// ��ȡ��ǰ��ĸӦ�ô洢��λ��
			if (tmpPtr->next[numIdx] == nullptr)
				tmpPtr->next[numIdx] = new Node();
			tmpPtr = tmpPtr->next[numIdx];
		}
		// ������Ϻ��޸ĸýڵ�ı�ʶλ
		tmpPtr->isEnd = true;
	}
	// ����string�ַ����ж��Ƿ����
	bool search(std::string str) {
		Node *tmpPtr = root;	// �������ʱ�ڵ�ָ����ڵ�
		for (int i = 0; i < str.length(); ++i) {
			int numIdx = str[i] - 'a';	// ��ȡ��ǰ��ĸ����
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
