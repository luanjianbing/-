#include <iostream>
#include <vector>

// 哈希映射
// 实际上就是将key通过某一哈希函数计算出下标，在数组中存入对应键值
// 查找的时候继续将key计算出下标，读出数组的值
template <class Key, class Value>
class HashMap
{	
public:
	HashMap(int size = 101) : arr(size)
	{
		currentSize = 0;
	}
	~HashMap() {}

	void Put(const Key &k, const Value &v)
	{
		int position = myHash(k);
		arr[position] = DataEntry(k, v);
		++currentSize;
	}

	void Get(const Key &k)
	{
		int position = myHash(k);
		if (arr[position].key == k)
			return arr[position].value;
		else
			return Value();
	}

	unsigned hash(const Key &k) const
	{
		unsigned int hashVal = 0;
		const char *keyp = reinterpret_cast<const char *>(&k);	// string 转换成字符
		for (size_t i = 0; i < sizeof(Key); ++i)
			hashVal = 37 * hashVal + keyp[i];	// ASCII码值运算
		return hashVal;
	}

	int myHash(const Key &k) const
	{
		unsigned hashVal = hash(k);
		hashVal %= arr.size();
		return hashVal;
	}

private:
	struct DataEntry
	{
		Key key;
		Value value;
		DataEntry(const Key &k = key(), const Value &v = Value())
			: key(k), value(v);
	};
	int currentSize;
	std::vector<DataEntry> arr;
};

