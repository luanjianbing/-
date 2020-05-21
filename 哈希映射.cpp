#include <iostream>
#include <vector>

// ��ϣӳ��
// ʵ���Ͼ��ǽ�keyͨ��ĳһ��ϣ����������±꣬�������д����Ӧ��ֵ
// ���ҵ�ʱ�������key������±꣬���������ֵ
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
		const char *keyp = reinterpret_cast<const char *>(&k);	// string ת�����ַ�
		for (size_t i = 0; i < sizeof(Key); ++i)
			hashVal = 37 * hashVal + keyp[i];	// ASCII��ֵ����
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

