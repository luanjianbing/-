#include <iostream>
#include <vector>
#include <random>

class Solution
{
public:
	Solution();
	~Solution();
	// ����
	// ð������(����)
	void bubbleSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		for (int end = vect.size() - 1; end > 0; --end) {
			for (int i = 0; i < end; ++i) {
				if (vect[i] > vect[i + 1])
					std::swap(vect[i], vect[i + 1]);	// ���ڱȽϣ�����������
			}
		}
	}
	// ð������(����)
	void bubbleSort(int *a, int length) {
		// a[5] = *(a + 5)
		if (length < 2) return;
		for (int end = length - 1; end > 0; --end) {
			for (int i = 0; i < end; ++i) {
				if (a[i] > a[i + 1])
					std::swap(a[i], a[i + 1]);	// ���ڱȽϣ�����������
			}
		}
	}

	// ѡ������(����)
	void selectionSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		int minIdx = 0;
		for (unsigned int i = 0; i < vect.size(); ++i) {
			minIdx = i;
			for (unsigned int j = i + 1; j < vect.size(); ++j) {
				minIdx = vect[j] < vect[minIdx] ? j : minIdx;	// ����ҵ���С����ֵ��Ӧ��������
			}
			std::swap(vect[i], vect[minIdx]);
		}
	}
	// ѡ������(����)
	void selectionSort(int *a, int length) {
		if (length < 2) return;
		int minIdx = 0;
		for (int i = 0; i < length; ++i) {
			minIdx = i;
			for (int j = i + 1; j < length; ++j) {
				minIdx = a[j] < a[minIdx] ? j : minIdx;	// ����ҵ���С����ֵ��Ӧ��������
			}
			std::swap(a[i], a[minIdx]);
		}
	}

	// ��������(����)
	void insertSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		for (unsigned int i = 1; i < vect.size(); ++i) {
			for (int j = i - 1; j >= 0 && vect[j] > vect[j + 1]; --j) {
				std::swap(vect[j], vect[j + 1]);	// ��ǰ���������ڱȽ�ǰ����ں�����н���
			}
		}
	}
	// ��������(����)
	void insertSort(int *a, int length) {
		if (length < 2) return;
		for (int i = 1; i < length; ++i) {
			for (int j = i - 1; j >= 0 && a[j] > a[j + 1]; --j) {
				std::swap(a[j], a[j + 1]);		// ��ǰ���������ڱȽ�ǰ����ں�����н���
			}
		}
	}

	// �鲢����ʵ���߼���
	// ����������Ƚϣ��ֱ��и�ָ��ָ�����������һλ���Ƚϣ�
	// С�ķ������ԭ�����飬ֱ����һ��������Χ������һ��û�г�����Χ�Ĳ��䵽����ԭ���������
	// **�鲢������Ҫ���鲢���������鶼���ź���ģ��������һ�����䵽���������
	// �鲢����(����)
	void merge(std::vector<int> &vect, int L, int mid, int R) {
		std::vector<int> help(R - L + 1);
		unsigned int i = 0;
		int p1 = L;
		int p2 = mid + 1;
		//��������Ƚ�
		while (p1 <= mid && p2 <= R) {
			help[i++] = vect[p1] < vect[p2] ? vect[p1++] : vect[p2++];	// ��������Ƚϣ�С�Ĵ����������
		}
		//���������ֻ��һ��Խ�磬��������whileֻ������һ��
		//��������δԽ���������������
		while (p1 <= mid) {
			help[i++] = vect[p1++];
		}
		while (p2 <= R) {
			help[i++] = vect[p2++];
		}
		//�������鸳ֵ��ԭ����
		for (i = 0; i < help.size(); ++i) {
			vect[L + i] = help[i];
		}
	}
	void sortProcess(std::vector<int> &vect, int L, int R) {
		if (L == R) return;
		// mid = L + (R - L) >> 1	����һλ���ڳ���2		
		int mid = L + (R - L) / 2;		//��ֹ���
		sortProcess(vect, L, mid);		// T(N/2) 
		sortProcess(vect, mid + 1, R);		//T(N/2)
		merge(vect, L, mid, R);		//O(N)
									//T(N) = 2 T(N/2) + O(N)		O(N*logN)��O(N^2)Ч�ʸ�
	}
	void mergeSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		sortProcess(vect, 0, vect.size() - 1);
	}
	// �鲢����(����)
	void merge(int *a, int L, int mid, int R) {
		//std::vector<int> help(R - L + 1);
		//int help[R - L + 1];	// windows���ر������������ñ�����ʼ������
		int length = R - L + 1;
		int *help = new int[length]();
		int i = 0;
		int p1 = L;
		int p2 = mid + 1;
		//��������Ƚ�
		while (p1 <= mid && p2 <= R) {
			help[i++] = a[p1] < a[p2] ? a[p1++] : a[p2++];	// ��������Ƚϣ�С�Ĵ����������
		}
		//���������ֻ��һ��Խ�磬��������whileֻ������һ��
		//��������δԽ���������������
		while (p1 <= mid) {
			help[i++] = a[p1++];
		}
		while (p2 <= R) {
			help[i++] = a[p2++];
		}
		//�������鸳ֵ��ԭ����
		for (i = 0; i < length; ++i) {
			a[L + i] = help[i];
		}
		delete[]help;
	}
	void sortProcess(int *a, int L, int R) {
		if (L == R) return;
		// mid = L + (R - L) >> 1	����һλ���ڳ���2		
		int mid = L + (R - L) / 2;		//��ֹ���
		sortProcess(a, L, mid);		// T(N/2) 
		sortProcess(a, mid + 1, R);		//T(N/2)
		merge(a, L, mid, R);		//O(N)
									//T(N) = 2 T(N/2) + O(N)		O(N*logN)��O(N^2)Ч�ʸ�
	}
	void mergeSort(int *a, int length) {
		if (length < 2) return;
		sortProcess(a, 0, length - 1);
	}

	// ���ŵ�ʵ���߼���
	// 1.�ȴ�������ȡ��һ������Ϊ��׼��(ͨ��ȡ��һ����)��
	// 2.�������̣���������������ȫ�ŵ������ұߣ�С�ڻ����������ȫ�ŵ�������ߡ�
	// 3.�ٶ����������ظ��ڶ�����ֱ��������ֻ��һ����
	// ��������(����)	������(>60)һ���ÿ���
	std::vector<int> qs_partition(std::vector<int> &list, int L, int R) {
		int less = L - 1;
		int more = R;
		int cur = L;
		std::vector<int> res(2);
		while (cur < more) {
			if (list[cur] < list[R])
				std::swap(list[++less], list[cur++]);
			else if (list[cur] > list[R])
				std::swap(list[--more], list[cur]);
			else {
				cur++;
			}
		}
		std::swap(list[more], list[R]);
		res[0] = cur;
		res[1] = more;
		return res;
	}
	void quickSort(std::vector<int> &list, int L, int R) {
		std::default_random_engine e;		// ��õ����������ͬ�ģ�ͨ�����ò�ͬ�����ӻ�ȡ��ͬ�������
		if (L < R) {
			std::swap(list[L + e() % (R - L + 1)], list[R]);
			std::vector<int> p = qs_partition(list, L, R);
			quickSort(list, L, p[0] - 1);
			quickSort(list, p[1] + 1, R);
		}
	}
	// ��������(����)
	int *qs_partition(int *a, int L, int R, int *res) {
		int less = L - 1;
		int more = R;
		int cur = L;
		//static int res[2];	// ��Ҫ����static���Σ��ı�����������
		while (cur < more) {
			if (a[cur] < a[R])
				std::swap(a[++less], a[cur++]);
			else if (a[cur] > a[R])
				std::swap(a[--more], a[cur]);
			else {
				cur++;
			}
		}
		std::swap(a[more], a[R]);
		res[0] = cur;
		res[1] = more;
		return res;
	}
	void quickSort(int *a, int L, int R) {
		std::default_random_engine e;		// ��õ����������ͬ�ģ�ͨ�����ò�ͬ�����ӻ�ȡ��ͬ�������
		if (L < R) {
			std::swap(a[L + e() % (R - L + 1)], a[R]);
			int *p = qs_partition(a, L, R, res);
			quickSort(a, L, *p - 1);
			quickSort(a, *p++ + 1, R);
		}
	}

	// ������(����)
	void heapInsert(std::vector<int> &vect, int index) {
		while (vect[index] > vect[(index - 1) / 2]) {	// i>(i-1)/2 -> ������ڸ���
			std::swap(vect[index], vect[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
	}
	// �ı�һ��ֵ��ʹ�������Ǵ����
	void heapify(std::vector<int> &vect, int index, int heapSize) {
		int left = index * 2 + 1;	//index = (left - 1) / 2 -> left:����
		while (left < heapSize) {
			int largest = left + 1 < heapSize && vect[left + 1] > vect[left]	// left+1Ϊ�Һ��ӵ�����
				? left + 1 : left;		//ѡȡ��������ֵ�����ظ�λ�õ�����
			largest = vect[largest] > vect[index] ? largest : index;	//���ֵ������Ƚϣ���������
			if (largest == index) {		//������ֵ��Ϊ���࣬�򲻽���������ѭ��
				break;
			}
			std::swap(vect[index], vect[largest]);		//���ҳ������ֵ�븸�ཻ��
			index = largest;
			left = index * 2 + 1;
		}
	}
	void heapSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		for (unsigned int i = 0; i < vect.size(); i++) {		//���������е����ݣ�ת���ɴ����
			heapInsert(vect, i);
		}
		int heapSize = vect.size();
		while (heapSize > 0) {
			std::swap(vect[0], vect[--heapSize]);	//����������ֵ���������
			heapify(vect, 0, heapSize);		//ʣ�µļ�������Ϊ�����
		}
	}
	// ������(����)
	void heapInsert(int *a, int index) {
		while (a[index] > a[(index - 1) / 2]) {	// i>(i-1)/2 -> ������ڸ���
			std::swap(a[index], a[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
	}
	// �ı�һ��ֵ��ʹ�������Ǵ����
	void heapify(int *a, int index, int heapSize) {
		int left = index * 2 + 1;	//index = (left - 1) / 2 -> left:����
		while (left < heapSize) {
			int largest = left + 1 < heapSize && a[left + 1] > a[left]	// left+1Ϊ�Һ��ӵ�����
				? left + 1 : left;		//ѡȡ��������ֵ�����ظ�λ�õ�����
			largest = a[largest] > a[index] ? largest : index;	//���ֵ������Ƚϣ���������
			if (largest == index) {		//������ֵ��Ϊ���࣬�򲻽���������ѭ��
				break;
			}
			std::swap(a[index], a[largest]);		//���ҳ������ֵ�븸�ཻ��
			index = largest;
			left = index * 2 + 1;
		}
	}
	void heapSort(int *a, int length) {
		if (length < 2) return;
		for (int i = 0; i < length; i++) {		//���������е����ݣ�ת���ɴ����
			heapInsert(a, i);
		}
		int heapSize = length;
		while (heapSize > 0) {
			std::swap(a[0], a[--heapSize]);	//����������ֵ���������
			heapify(a, 0, heapSize);		//ʣ�µļ�������Ϊ�����
		}
	}

	// Ͱ����ʵ���߼���
	// ��Сֵ�����ֵ����ΪͰ����ֵ����Ͱ�ķ�Χ���룬ÿ��Ͱ��������
	// ��˳��ȡ��
	// ����Ͱ����д����ȥ���ظ�����ֵ
	// Ͱ����(����)
	void bucketSort(std::vector<int> &vect) {
		int vSize = vect.size();
		if (vSize < 2) return;
		int max = INT_MIN;
		int min = INT_MAX;
		for (int i = 0; i < vSize; ++i) {
			min = min < vect[i] ? min : vect[i];
			max = max > vect[i] ? max : vect[i];
		}
		int diff = max - min;
		int bLength = diff + 2;	// ������ diff + 2 ��Ͱ
		std::vector<int> buckets(bLength, 0);
		std::vector<bool> bucketsHasNum(bLength, false);
		int bIdx = 0;	// ȥ����Ͱ
		for (int i = 0; i < vSize; ++i) {
			bIdx = (vect[i] - min)*vSize / diff;
			buckets[bIdx] = vect[i];
			bucketsHasNum[bIdx] = true;
		}

		for (int i = 0, j = 0; i < bLength; ++i) {
			if (bucketsHasNum[i])
				vect[j++] = buckets[i];
		}
	}
	// Ͱ����(����)
	void bucketSort(int *a, int length) {
		if (length < 2) return;
		int max = INT_MIN;
		int min = INT_MAX;
		for (int i = 0; i < length; ++i){
			min = min < a[i] ? min : a[i];
			max = max > a[i] ? max : a[i];
		}
		int diff = max - min;
		int bLength = diff + 2;	// ������ diff + 2 ��Ͱ
		int *buckets = new int[bLength]();	
		bool *bucketsHasNum = new bool[bLength]();	// ���ڱ�Ǹ�Ͱ�Ƿ�������
		int bIdx = 0;	// ȥ����Ͱ
		for (int i = 0; i < length; ++i) {
			bIdx = (a[i] - min)*length / diff;
			buckets[bIdx] = a[i];
			bucketsHasNum[bIdx] = true;
		}
		
		for (int i = 0; i < bLength; ++i) {
			if (bucketsHasNum[i])
				*a++ = buckets[i];
		}
		delete[]buckets;
		delete[]bucketsHasNum;
	}

	// flashSort���Ľ��˶�Ҫʹ�õ�Ͱ��Ԥ��,����˵,����������Ͱ�������Ӷ���ʡ�˿ռ�,����
	// ��������[6 2 4 1 5 9 100]Ͱ����Ҫ100��Ͱ, ��flash sort�����ڿ���Ԥ��Ͱ��ֻ��Ҫ7��Ͱ
	// flashSort(����)
	void flashSort(std::vector<int> &vect) {
		int vSize = vect.size();
		if (vSize < 2) return;
		int max = INT_MIN;
		int min = INT_MAX;
		for (int i = 0; i < vSize; ++i) {
			min = min < vect[i] ? min : vect[i];
			max = max > vect[i] ? max : vect[i];
		}
		int diff = max - min;
		// ������ vSize ��Ͱ
		std::vector<int> buckets(vSize, 0);
		int bIdx = 0;	// ȥ����Ͱ
		for (int i = 0; i < vSize; ++i) {
			// ����Ԥ���޸�(��Ͱ�������)
			bIdx = (vSize - 1) * (vect[i] - min) / diff;
			buckets[bIdx] = vect[i];
		}

		for (int i = 0; i < vSize; ++i) {
				vect[i] = buckets[i];
		}
	}
	// flashSort(����)
	void flashSort(int *a, int length) {
		if (length < 2) return;
		int max = INT_MIN;
		int min = INT_MAX;
		for (int i = 0; i < length; ++i) {
			min = min < a[i] ? min : a[i];
			max = max > a[i] ? max : a[i];
		}
		int diff = max - min;
		int *buckets = new int[length]();
		int bIdx = 0;	// ȥ����Ͱ
		for (int i = 0; i < length; ++i) {
			// ����Ԥ���޸�(��Ͱ�������)
			bIdx = (length - 1) * (a[i] - min) / diff;
			buckets[bIdx] = a[i];
		}

		for (int i = 0; i < length; ++i) {
				*a++ = buckets[i];
		}
		delete[]buckets;
	}

	// ��������(����)
	void countSort(std::vector<int> &vect)
	{
		if (vect.size() < 2) return;

		//ȷ���������ֵ
		int max = vect[0];
		for (unsigned int i = 1; i < vect.size(); ++i){
			if (vect[i] > max)
				max = vect[i];
		}

		// ȷ��ͳ�����鳤�Ȳ����г�ʼ��
		std::vector<int> countData(max + 1, 0);
		// �������飬ͳ��ÿ�������ֵĴ���
		for (unsigned int i = 0; i < vect.size(); ++i)
			++countData[vect[i]];
		// �������飬ĳ���������˼��Σ�����data���ۼ��������
		int index = 0;
		for (int i = 0; i <= max; ++i)
		{
			for (int j = 0; j < countData[i]; ++j)
			{
				vect[index++] = i;
			}
		}
	}
	// ��������(����)
	void countSort(int *a, int length)
	{
		if (a == nullptr || length <= 0)
			return;

		//ȷ���������ֵ
		int max = a[0];
		for (int i = 1; i < length; ++i)
		{
			if (a[i] > max)
				max = a[i];
		}

		// ȷ��ͳ�����鳤�Ȳ����г�ʼ��
		int* countData = new int[max + 1];
		for (int i = 0; i <= max; ++i)
			countData[i] = 0;
		// �������飬ͳ��ÿ�������ֵĴ���
		for (int i = 0; i < length; ++i)
			++countData[a[i]];
		// �������飬ĳ���������˼��Σ�����data���ۼ��������
		int index = 0;
		for (int i = 0; i <= max; ++i)
		{
			for (int j = 0; j < countData[i]; ++j)
			{
				a[index++] = i;
			}
		}
		delete[]countData;
	}

private:
	int res[2];	// ������
};

Solution::Solution()
{
}

Solution::~Solution()
{
}

int main() {
	int a[6] = {1, 5, 6, 2, 4, 3};
	int length = sizeof(a) / sizeof(a[1]);

	std::vector<int> vect = { 1, 5, 6, 2, 4, 3 };

	Solution s;

	//s.bubbleSort(vect);
	//s.bubbleSort(a, length);

	//s.selectionSort(vect);
	//s.selectionSort(a, length);

	//s.insertSort(vect);
	//s.insertSort(a, length);

	//s.mergeSort(vect);
	//s.mergeSort(a, length);

	//s.quickSort(vect, 0, vect.size() - 1);
	//s.quickSort(a, 0, length - 1);

	//s.heapSort(vect);
	//s.heapSort(a, length);

	//s.countSort(vect);
	//s.countSort(a, length);

	//s.bucketSort(vect);
	//s.bucketSort(a, length);

	s.flashSort(vect);
	s.bucketSort(a, length);

	for (unsigned int i = 0; i < vect.size(); ++i) {
		std::cout << vect[i] << " ";
	}
	std::cout << std::endl;
	
	for (int i = 0; i < length; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}