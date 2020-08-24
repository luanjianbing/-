#include <iostream>

using namespace std;

class KMP {	// 判断一个字符串中是否包含某个子字符串
public:
	void getNext(string &tar, int *next) {	// tar:目标串，next:存放
		int i = 0, j = -1;
		next[0] = -1;	//第一位赋值为-1
		while (i < tar.size() - 1) {
			if (j == -1 || tar[i] == tar[j]) {
				i++;	// i=1,j=0
				j++;
				if (tar[i] != tar[j]) {
					next[i] = j;	// next[1] = 0
				}
				//优化点，防止T串为aaaab这种类型，需要一个一个往前翻，利用下面两行，可以直接找到最初等价位置
				else {	// 遇到相等的字符，直接将前一个赋值给后一个
					next[i] = next[j];
				}
			}
			else {
				j = next[j];
			}
		}
	}

	int KMP_method(string &src, string &tar) {
		int *next = new int[tar.size()]; // 建立一张部分匹配表，部分比配表用于放置每次比较的部分匹配值，
										// 部分匹配值即本次匹配过程中"前缀"和"后缀"的最长的共有元素的长度
		getNext(tar, next);
		int i = 0, j = 0;
		while (i < src.size() && j < tar.size())
		{
			if (src[i] == tar[j])
			{
				i++;
				j++;
			}
			else if (next[j] == -1)
				i++;
			else
				j = next[j];
		}
		if (next)
		{
			delete[]next;
			next = NULL;
		}
		return (j == tar.size()) ? i - j : -1;
	}
};

int main() {
	string s = "abacbads";
	string t = "bad";
	KMP kmp;
	int	res = kmp.KMP_method(s, t);
	cout << res << endl;


	system("pause");
	return 0;
}
