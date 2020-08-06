#include <iostream>

using namespace std;

// 是一个可以在O(n)的复杂度中返回字符串s中最长回文子串长度的算法

// 在原字符串中插入一个未出现的字符如"#"
// 回文分为奇回文(adcacda)和偶回文(abba)，这样插入之后变成了（#a#d#c#a#c#d#a#）
// 和（#a#d#d#a#）两个奇回文

// 字符串中找到最长的回文字符串
// 1.当前位置i不在回文右边界内，暴力扩
// 2.当前位置i在回文右边界内，不用扩，回文半径一定跟关于回文中心对称的i'一样
// 3.2情况中i的位置关于回文中心对称的i'回文半径超出当前范围，则当前回文半径是i到回文右边界R

class Solution {
public:
	int manacher(string str) {
		// 字符串预处理
		string newStr = "#";
		for (auto c : str) {
			newStr = newStr + c + "#";
		}
		// 回文半径记录数组
		int *rIndex = new int[newStr.length()];
		int c = -1;	// 回文中心
		int R = -1;	// 回文右边界
		int maxL = INT_MIN;		// 记录最长回文字长
		for (int i = 0; i < newStr.length(); ++i) {
			if (R > i)
				rIndex[i] = rIndex[2 * c - i] < R - i ? rIndex[2 * c - i] : R - i;	// 判断当前i跟对称的i'的回文长度，取小的
			else
				rIndex[i] = 1;	// 回文右边界在当前i的左侧，即无回文

								//取最小值后开始从边界暴力匹配，匹配失败就直接退出
			while (i + rIndex[i] < newStr.length() && i - rIndex[i] > -1)
			{
				if (newStr[i + rIndex[i]] == newStr[i - rIndex[i]])//向两边扩展，找回文字母
					rIndex[i]++;
				else
					break;
			}
			//观察此时R和C是否能够更新
			if (i + rIndex[i] > R)
			{
				R = i + rIndex[i];
				c = i;
			}
			//更新最大回文半径的值
			maxL = maxL > rIndex[i] ? maxL : rIndex[i];
		}
		delete[] rIndex;
		//这里解释一下为什么返回值是maxn-1，因为manacherstring的长度和原字符串不同，
		//所以这里得到的最大回文半径其实是原字符串的最大回文子串长度加1，
		//有兴趣的可以自己验证试试,-1是为了将后面的‘#’去掉
		return maxL - 1;
	}
};

int main() {

	string str = "abcdcbe";
	Solution s;
	int res = s.manacher(str);
	cout << res << endl;

	return 0;
}

