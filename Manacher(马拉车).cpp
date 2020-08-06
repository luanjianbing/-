#include <iostream>

using namespace std;

// ��һ��������O(n)�ĸ��Ӷ��з����ַ���s��������Ӵ����ȵ��㷨

// ��ԭ�ַ����в���һ��δ���ֵ��ַ���"#"
// ���ķ�Ϊ�����(adcacda)��ż����(abba)����������֮�����ˣ�#a#d#c#a#c#d#a#��
// �ͣ�#a#d#d#a#�����������

// �ַ������ҵ���Ļ����ַ���
// 1.��ǰλ��i���ڻ����ұ߽��ڣ�������
// 2.��ǰλ��i�ڻ����ұ߽��ڣ������������İ뾶һ�������ڻ������ĶԳƵ�i'һ��
// 3.2�����i��λ�ù��ڻ������ĶԳƵ�i'���İ뾶������ǰ��Χ����ǰ���İ뾶��i�������ұ߽�R

class Solution {
public:
	int manacher(string str) {
		// �ַ���Ԥ����
		string newStr = "#";
		for (auto c : str) {
			newStr = newStr + c + "#";
		}
		// ���İ뾶��¼����
		int *rIndex = new int[newStr.length()];
		int c = -1;	// ��������
		int R = -1;	// �����ұ߽�
		int maxL = INT_MIN;		// ��¼������ֳ�
		for (int i = 0; i < newStr.length(); ++i) {
			if (R > i)
				rIndex[i] = rIndex[2 * c - i] < R - i ? rIndex[2 * c - i] : R - i;	// �жϵ�ǰi���ԳƵ�i'�Ļ��ĳ��ȣ�ȡС��
			else
				rIndex[i] = 1;	// �����ұ߽��ڵ�ǰi����࣬���޻���

								//ȡ��Сֵ��ʼ�ӱ߽籩��ƥ�䣬ƥ��ʧ�ܾ�ֱ���˳�
			while (i + rIndex[i] < newStr.length() && i - rIndex[i] > -1)
			{
				if (newStr[i + rIndex[i]] == newStr[i - rIndex[i]])//��������չ���һ�����ĸ
					rIndex[i]++;
				else
					break;
			}
			//�۲��ʱR��C�Ƿ��ܹ�����
			if (i + rIndex[i] > R)
			{
				R = i + rIndex[i];
				c = i;
			}
			//���������İ뾶��ֵ
			maxL = maxL > rIndex[i] ? maxL : rIndex[i];
		}
		delete[] rIndex;
		//�������һ��Ϊʲô����ֵ��maxn-1����Ϊmanacherstring�ĳ��Ⱥ�ԭ�ַ�����ͬ��
		//��������õ��������İ뾶��ʵ��ԭ�ַ������������Ӵ����ȼ�1��
		//����Ȥ�Ŀ����Լ���֤����,-1��Ϊ�˽�����ġ�#��ȥ��
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

