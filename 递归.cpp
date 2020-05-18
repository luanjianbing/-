#include <iostream>

class Solution
{
public:
	Solution();
	~Solution();

	// 这里以递归实现一个输入一个字符串，输出各种排列组合
	void recurPerm(char *s, const int start, const int end) {
		if (start == end) {
			for (int i = 0; i <= end; ++i)
				std::cout << s[i];
			std::cout << std::endl;
		}
		else {
			for (int i = start; i <= end; ++i) {
				std::swap(s[start], s[i]);
				recurPerm(s, start + 1, end);
				std::swap(s[start], s[i]);
			}
		}
	}
private:

};

Solution::Solution()
{
}

Solution::~Solution()
{
}

int main() {
	char c[] = "abc";

	Solution s;
	s.recurPerm(c, 0, 2);

	return 0;
}