#include <iostream>
#include <vector>
#include <random>

class Solution
{
public:
	Solution();
	~Solution();
	// 升序
	// 冒泡排序(容器)
	void bubbleSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		for (int end = vect.size() - 1; end > 0; --end) {
			for (int i = 0; i < end; ++i) {
				if (vect[i] > vect[i + 1])
					std::swap(vect[i], vect[i + 1]);	// 相邻比较，最大的往后移
			}
		}
	}
	// 冒泡排序(数组)
	void bubbleSort(int *a, int length) {
		// a[5] = *(a + 5)
		if (length < 2) return;
		for (int end = length - 1; end > 0; --end) {
			for (int i = 0; i < end; ++i) {
				if (a[i] > a[i + 1])
					std::swap(a[i], a[i + 1]);	// 相邻比较，最大的往后移
			}
		}
	}

	// 选择排序(容器)
	void selectionSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		int minIdx = 0;
		for (unsigned int i = 0; i < vect.size(); ++i) {
			minIdx = i;
			for (unsigned int j = i + 1; j < vect.size(); ++j) {
				minIdx = vect[j] < vect[minIdx] ? j : minIdx;	// 向后找到最小的数值对应索引交换
			}
			std::swap(vect[i], vect[minIdx]);
		}
	}
	// 选择排序(数组)
	void selectionSort(int *a, int length) {
		if (length < 2) return;
		int minIdx = 0;
		for (int i = 0; i < length; ++i) {
			minIdx = i;
			for (int j = i + 1; j < length; ++j) {
				minIdx = a[j] < a[minIdx] ? j : minIdx;	// 向后找到最小的数值对应索引交换
			}
			std::swap(a[i], a[minIdx]);
		}
	}

	// 插入排序(容器)
	void insertSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		for (unsigned int i = 1; i < vect.size(); ++i) {
			for (int j = i - 1; j >= 0 && vect[j] > vect[j + 1]; --j) {
				std::swap(vect[j], vect[j + 1]);	// 向前搜索，相邻比较前面大于后面进行交换
			}
		}
	}
	// 插入排序(数组)
	void insertSort(int *a, int length) {
		if (length < 2) return;
		for (int i = 1; i < length; ++i) {
			for (int j = i - 1; j >= 0 && a[j] > a[j + 1]; --j) {
				std::swap(a[j], a[j + 1]);		// 向前搜索，相邻比较前面大于后面进行交换
			}
		}
	}

	// 归并排序实现逻辑：
	// 分左右两块比较，分别有个指针指向左右两块第一位，比较，
	// 小的放入额外原长数组，直至有一个超出范围，将另一个没有超出范围的补充到额外原长数组后面
	// **归并条件需要待归并的两个数组都是排好序的，否则最后一步补充到后面会有误
	// 归并排序(容器)
	void merge(std::vector<int> &vect, int L, int mid, int R) {
		std::vector<int> help(R - L + 1);
		unsigned int i = 0;
		int p1 = L;
		int p2 = mid + 1;
		//左右两块比较
		while (p1 <= mid && p2 <= R) {
			help[i++] = vect[p1] < vect[p2] ? vect[p1++] : vect[p2++];	// 左右两块比较，小的存入帮助容器
		}
		//左右两块必只有一个越界，下面两个while只会运行一个
		//将已排序但未越界数组放入新数组
		while (p1 <= mid) {
			help[i++] = vect[p1++];
		}
		while (p2 <= R) {
			help[i++] = vect[p2++];
		}
		//将新数组赋值给原数组
		for (i = 0; i < help.size(); ++i) {
			vect[L + i] = help[i];
		}
	}
	void sortProcess(std::vector<int> &vect, int L, int R) {
		if (L == R) return;
		// mid = L + (R - L) >> 1	右移一位等于除以2		
		int mid = L + (R - L) / 2;		//防止溢出
		sortProcess(vect, L, mid);		// T(N/2) 
		sortProcess(vect, mid + 1, R);		//T(N/2)
		merge(vect, L, mid, R);		//O(N)
									//T(N) = 2 T(N/2) + O(N)		O(N*logN)比O(N^2)效率高
	}
	void mergeSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		sortProcess(vect, 0, vect.size() - 1);
	}
	// 归并排序(数组)
	void merge(int *a, int L, int mid, int R) {
		//std::vector<int> help(R - L + 1);
		//int help[R - L + 1];	// windows本地编译器不可以用变量初始化数组
		int length = R - L + 1;
		int *help = new int[length]();
		int i = 0;
		int p1 = L;
		int p2 = mid + 1;
		//左右两块比较
		while (p1 <= mid && p2 <= R) {
			help[i++] = a[p1] < a[p2] ? a[p1++] : a[p2++];	// 左右两块比较，小的存入帮助容器
		}
		//左右两块必只有一个越界，下面两个while只会运行一个
		//将已排序但未越界数组放入新数组
		while (p1 <= mid) {
			help[i++] = a[p1++];
		}
		while (p2 <= R) {
			help[i++] = a[p2++];
		}
		//将新数组赋值给原数组
		for (i = 0; i < length; ++i) {
			a[L + i] = help[i];
		}
		delete[]help;
	}
	void sortProcess(int *a, int L, int R) {
		if (L == R) return;
		// mid = L + (R - L) >> 1	右移一位等于除以2		
		int mid = L + (R - L) / 2;		//防止溢出
		sortProcess(a, L, mid);		// T(N/2) 
		sortProcess(a, mid + 1, R);		//T(N/2)
		merge(a, L, mid, R);		//O(N)
									//T(N) = 2 T(N/2) + O(N)		O(N*logN)比O(N^2)效率高
	}
	void mergeSort(int *a, int length) {
		if (length < 2) return;
		sortProcess(a, 0, length - 1);
	}

	// 快排的实现逻辑：
	// 1.先从数列中取出一个数作为基准数(通常取第一个数)。
	// 2.分区过程，将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边。
	// 3.再对左右区间重复第二步，直到各区间只有一个数
	// 快速排序(容器)	长数组(>60)一般用快排
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
		std::default_random_engine e;		// 获得的随机数是相同的，通过设置不同的种子获取不同的随机数
		if (L < R) {
			std::swap(list[L + e() % (R - L + 1)], list[R]);
			std::vector<int> p = qs_partition(list, L, R);
			quickSort(list, L, p[0] - 1);
			quickSort(list, p[1] + 1, R);
		}
	}
	// 快速排序(数组)
	int *qs_partition(int *a, int L, int R, int *res) {
		int less = L - 1;
		int more = R;
		int cur = L;
		//static int res[2];	// 需要加上static修饰，改变其生命周期
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
		std::default_random_engine e;		// 获得的随机数是相同的，通过设置不同的种子获取不同的随机数
		if (L < R) {
			std::swap(a[L + e() % (R - L + 1)], a[R]);
			int *p = qs_partition(a, L, R, res);
			quickSort(a, L, *p - 1);
			quickSort(a, *p++ + 1, R);
		}
	}

	// 堆排序(容器)
	void heapInsert(std::vector<int> &vect, int index) {
		while (vect[index] > vect[(index - 1) / 2]) {	// i>(i-1)/2 -> 子类大于父类
			std::swap(vect[index], vect[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
	}
	// 改变一个值，使其依旧是大根堆
	void heapify(std::vector<int> &vect, int index, int heapSize) {
		int left = index * 2 + 1;	//index = (left - 1) / 2 -> left:子类
		while (left < heapSize) {
			int largest = left + 1 < heapSize && vect[left + 1] > vect[left]	// left+1为右孩子的索引
				? left + 1 : left;		//选取子类的最大值，返回该位置的索引
			largest = vect[largest] > vect[index] ? largest : index;	//最大值跟父类比较，返回索引
			if (largest == index) {		//如果最大值就为父类，则不交换，跳出循环
				break;
			}
			std::swap(vect[index], vect[largest]);		//将找出的最大值与父类交换
			index = largest;
			left = index * 2 + 1;
		}
	}
	void heapSort(std::vector<int> &vect) {
		if (vect.size() < 2) return;
		for (unsigned int i = 0; i < vect.size(); i++) {		//对于数组中的数据，转换成大根堆
			heapInsert(vect, i);
		}
		int heapSize = vect.size();
		while (heapSize > 0) {
			std::swap(vect[0], vect[--heapSize]);	//将大根堆最大值交换到最后
			heapify(vect, 0, heapSize);		//剩下的继续调整为大根堆
		}
	}
	// 堆排序(数组)
	void heapInsert(int *a, int index) {
		while (a[index] > a[(index - 1) / 2]) {	// i>(i-1)/2 -> 子类大于父类
			std::swap(a[index], a[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
	}
	// 改变一个值，使其依旧是大根堆
	void heapify(int *a, int index, int heapSize) {
		int left = index * 2 + 1;	//index = (left - 1) / 2 -> left:子类
		while (left < heapSize) {
			int largest = left + 1 < heapSize && a[left + 1] > a[left]	// left+1为右孩子的索引
				? left + 1 : left;		//选取子类的最大值，返回该位置的索引
			largest = a[largest] > a[index] ? largest : index;	//最大值跟父类比较，返回索引
			if (largest == index) {		//如果最大值就为父类，则不交换，跳出循环
				break;
			}
			std::swap(a[index], a[largest]);		//将找出的最大值与父类交换
			index = largest;
			left = index * 2 + 1;
		}
	}
	void heapSort(int *a, int length) {
		if (length < 2) return;
		for (int i = 0; i < length; i++) {		//对于数组中的数据，转换成大根堆
			heapInsert(a, i);
		}
		int heapSize = length;
		while (heapSize > 0) {
			std::swap(a[0], a[--heapSize]);	//将大根堆最大值交换到最后
			heapify(a, 0, heapSize);		//剩下的继续调整为大根堆
		}
	}

	// 桶排序实现逻辑：
	// 最小值到最大值划分为桶，数值按照桶的范围放入，每个桶各自排序
	// 按顺序取出
	// 以下桶排序写法会去除重复的数值
	// 桶排序(容器)
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
		int bLength = diff + 2;	// 划分了 diff + 2 个桶
		std::vector<int> buckets(bLength, 0);
		std::vector<bool> bucketsHasNum(bLength, false);
		int bIdx = 0;	// 去几号桶
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
	// 桶排序(数组)
	void bucketSort(int *a, int length) {
		if (length < 2) return;
		int max = INT_MIN;
		int min = INT_MAX;
		for (int i = 0; i < length; ++i){
			min = min < a[i] ? min : a[i];
			max = max > a[i] ? max : a[i];
		}
		int diff = max - min;
		int bLength = diff + 2;	// 划分了 diff + 2 个桶
		int *buckets = new int[bLength]();	
		bool *bucketsHasNum = new bool[bLength]();	// 用于标记该桶是否有数字
		int bIdx = 0;	// 去几号桶
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

	// flashSort即改进了对要使用的桶的预测,或者说,减少了无用桶的数量从而节省了空间,例如
	// 待排数字[6 2 4 1 5 9 100]桶排需要100个桶, 而flash sort则由于可以预测桶则只需要7个桶
	// flashSort(容器)
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
		// 划分了 vSize 个桶
		std::vector<int> buckets(vSize, 0);
		int bIdx = 0;	// 去几号桶
		for (int i = 0; i < vSize; ++i) {
			// 索引预测修改(与桶排序相比)
			bIdx = (vSize - 1) * (vect[i] - min) / diff;
			buckets[bIdx] = vect[i];
		}

		for (int i = 0; i < vSize; ++i) {
				vect[i] = buckets[i];
		}
	}
	// flashSort(数组)
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
		int bIdx = 0;	// 去几号桶
		for (int i = 0; i < length; ++i) {
			// 索引预测修改(与桶排序相比)
			bIdx = (length - 1) * (a[i] - min) / diff;
			buckets[bIdx] = a[i];
		}

		for (int i = 0; i < length; ++i) {
				*a++ = buckets[i];
		}
		delete[]buckets;
	}

	// 计数排序(容器)
	void countSort(std::vector<int> &vect)
	{
		if (vect.size() < 2) return;

		//确定数列最大值
		int max = vect[0];
		for (unsigned int i = 1; i < vect.size(); ++i){
			if (vect[i] > max)
				max = vect[i];
		}

		// 确定统计数组长度并进行初始化
		std::vector<int> countData(max + 1, 0);
		// 遍历数组，统计每个数出现的次数
		for (unsigned int i = 0; i < vect.size(); ++i)
			++countData[vect[i]];
		// 排序数组，某个数出现了几次，便在data里累计输出几次
		int index = 0;
		for (int i = 0; i <= max; ++i)
		{
			for (int j = 0; j < countData[i]; ++j)
			{
				vect[index++] = i;
			}
		}
	}
	// 计数排序(数组)
	void countSort(int *a, int length)
	{
		if (a == nullptr || length <= 0)
			return;

		//确定数列最大值
		int max = a[0];
		for (int i = 1; i < length; ++i)
		{
			if (a[i] > max)
				max = a[i];
		}

		// 确定统计数组长度并进行初始化
		int* countData = new int[max + 1];
		for (int i = 0; i <= max; ++i)
			countData[i] = 0;
		// 遍历数组，统计每个数出现的次数
		for (int i = 0; i < length; ++i)
			++countData[a[i]];
		// 排序数组，某个数出现了几次，便在data里累计输出几次
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
	int res[2];	// 快排用
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