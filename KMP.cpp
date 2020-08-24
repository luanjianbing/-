#include <iostream>

using namespace std;

class KMP {	// �ж�һ���ַ������Ƿ����ĳ�����ַ���
public:
	void getNext(string &tar, int *next) {	// tar:Ŀ�괮��next:���
		int i = 0, j = -1;
		next[0] = -1;	//��һλ��ֵΪ-1
		while (i < tar.size() - 1) {
			if (j == -1 || tar[i] == tar[j]) {
				i++;	// i=1,j=0
				j++;
				if (tar[i] != tar[j]) {
					next[i] = j;	// next[1] = 0
				}
				//�Ż��㣬��ֹT��Ϊaaaab�������ͣ���Ҫһ��һ����ǰ���������������У�����ֱ���ҵ�����ȼ�λ��
				else {	// ������ȵ��ַ���ֱ�ӽ�ǰһ����ֵ����һ��
					next[i] = next[j];
				}
			}
			else {
				j = next[j];
			}
		}
	}

	int KMP_method(string &src, string &tar) {
		int *next = new int[tar.size()]; // ����һ�Ų���ƥ������ֱ�������ڷ���ÿ�αȽϵĲ���ƥ��ֵ��
										// ����ƥ��ֵ������ƥ�������"ǰ׺"��"��׺"����Ĺ���Ԫ�صĳ���
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
