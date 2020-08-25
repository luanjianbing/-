#include <iostream>

using namespace std;

//Rabin - Karp 字符串编码是一种将字符串映射成整数的编码方式，可以看成是一种哈希算法。
//具体地，假设字符串包含的字符种类不超过 ∣Σ∣（其中 Σ 表示字符集），
//那么我们选一个大于等于 ∣Σ∣ 的整数 base，
//就可以将字符串看成 base 进制的整数，
//将其转换成十进制数后，就得到了字符串对应的编码。
//
//例如给定字符串 s = abca，其包含的字符种类为 3（即 abc 三种）。
//我们取base = 9，将字符串 s 看成九进制数(0120)_9
//​
//，转换为十进制为 90，也就是说字符串 abc 的编码为 90


// 结论：两个字符串 ss 和 tt 相等，当且仅当它们的长度相等且编码值相等。

//对于算法题而言，我们只需要选择一个模数即可，并且它最好是一个质数，例如 10 ^ 9 + 7
//。如有需要，还可以选择第二个模数 10 ^ 9 + 9
// 对于前文提到的 base，一般也选择一个质数


class RABIN_KARP {
public:
	// 这里假设字符串全由小写字母组成，那么共有26种情况最多，取base = 31
	int getHash(string str, const int base = 31 ,const int mod = (1E9) + 7) {
		int strLength = str.length();
		int ans = 0;
		for (int i = 0; i < strLength; ++i) {
			ans += (str[i] - 'a') * (long long)pow(base, strLength - i - 1) % mod;
		}
		return ans;
	}
};

int main() {
	RABIN_KARP bHash;

	string str = "abca";
	cout << bHash.getHash(str, 9) <<endl;

	return 0;
}
