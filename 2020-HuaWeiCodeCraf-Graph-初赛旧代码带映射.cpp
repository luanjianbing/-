#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cstring>
//mmap需要用到的头文件
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
//计时
//#include <time.h>

#define INFILEPATH  "/data/test_data.txt"
#define OUTFILEPATH "/projects/student/result.txt"
#define MAXLINE 280000
typedef unsigned int u32;

int result3[3*500000], result4[4*500000], result5[5*1000000], result6[6*2000000], result7[7*3000000];
int *result[]={result3, result4, result5, result6, result7};
int Graph[280000][50]; // 邻接表
int GraphInv[280000][50]; // 逆邻接表
int *G[280000]; // 记录邻接表的尾指针
int *GInv[280000]; // 记录逆邻接表的尾指针
u32 inputData[MAXLINE*2]; 
u32 dataOrdered[MAXLINE*2];
int maxNumber = 0;

class MySolver
{
public:
	//void CountingSort(u32 array[], int nLength_, int nMaxNumber_)
	//{
	//	// 统计待排序数组中每一个元素的个数
	//	int* ArrayCount = new int[nMaxNumber_ + 1]{ 0 };
	//	for (int i = 0; i < nLength_; ++i) {
	//		++ArrayCount[array[i]];
	//	}
	//	// 此处计算待排序数组中小于等于第i个元素的个数. 
	//	for (int i = 1; i < nMaxNumber_ + 1; ++i) {
	//		ArrayCount[i] += ArrayCount[i - 1];
	//	}
	//	// 把待排序的数组放到输出数组中, 为了保持排序的稳定性，从后向前添加元素
	//	int* ArrayResult = new int[nLength_];
	//	for (int i = nLength_ - 1; i >= 0; --i) {
	//		int _nIndex = ArrayCount[array[i]] - 1; // 元素array[i]在输出数组中的下标
	//		ArrayResult[_nIndex] = array[i];

	//		// 因为可能有重复的元素，所以要减1,为下一个重复的元素计算正确的下标;
	//		--ArrayCount[array[i]];
	//	}

	//	// 交换数据并释放内存空间
	//	memcpy(array, ArrayResult, sizeof(int) * nLength_);
	//	//delete[] ArrayCount;
	//	//ArrayCount = nullptr;
	//	//delete[] ArrayResult;
	//	//ArrayResult = nullptr;
	//}
	// 加载数据
	void mmapLoadTxt()
	{
		int fd = open(INFILEPATH, O_RDONLY);
        if (fd == -1)
        {
            std::cout << "打开文件失败" << std::endl;
            exit(0);         
        }
        int len = lseek(fd, 0, SEEK_END);
        char *mbuf = (char *)mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
        u32 transferID = 0, receiverID = 0;
        rowNum = 0;
        char *txtEnd = mbuf + len;
        while (mbuf < txtEnd)
        {
            transferID = 0;
            receiverID = 0;
            do
            {
                transferID = transferID * 10 + *mbuf - '0';
            }while(*++mbuf != ',');
            ++mbuf;
            do
            {  
                receiverID = receiverID*10 + *mbuf - '0';
            }while(*++mbuf != ',');
            while(*++mbuf != '\n');
            ++mbuf;

            inputData[rowNum++] = transferID;
            inputData[rowNum++] = receiverID;

			maxNumber = transferID > maxNumber ? transferID : maxNumber;
			maxNumber = receiverID > maxNumber ? receiverID : maxNumber;
        }
	}
	// 构图
	void establishAdjacencyTable()
	{
		int i = 0;
		// 1.映射
		memcpy(dataOrdered, inputData, rowNum*sizeof(u32));
		//std::sort(dataOrdered, dataOrdered+rowNum);
		//CountingSort(dataOrdered, rowNum, maxNumber);

		int nMaxNumber_ = maxNumber + 1;		int ArrayCount[nMaxNumber_] = { 0 };		for (int i = 0; i < rowNum; ++i) {			++ArrayCount[dataOrdered[i]];		}		for (int i = 1; i < nMaxNumber_ + 1; ++i) {			ArrayCount[i] += ArrayCount[i - 1];		}		int ArrayResult[rowNum] = { 0 };		for (int i = rowNum - 1; i >= 0; --i) {			int _nIndex = ArrayCount[dataOrdered[i]] - 1; 			ArrayResult[_nIndex] = dataOrdered[i];			--ArrayCount[dataOrdered[i]];		}		memcpy(dataOrdered, ArrayResult, sizeof(int) * rowNum);

		vertexNum = std::unique(dataOrdered, dataOrdered+rowNum) - dataOrdered;
		for (i = 0; i < vertexNum; i++)
		{			
			G[i] = Graph[i];
			GInv[i] = GraphInv[i];
			idMap[dataOrdered[i]] = i;
		}
		// 2.连接表
		inDegree = std::vector<int>(vertexNum, 0);
		int transfer, receiver;
		for (i = 0; i < rowNum; i += 2)
		{
			transfer = idMap[inputData[i]];
			receiver = idMap[inputData[i+1]]; //这里可以用位运算改进试试
			*G[transfer]++ = receiver;
			*GInv[receiver]++ = transfer;
			++inDegree[receiver];
		}

		//数据预处理
		//1 将度（入度加出度）为1的点去除<由于删除出度为0的点需要记录G[v][u],这里先仅删除入度为0的点试试
		std::queue<int> inZeroQue;
		int cnt = 0;
		for (i = 0; i < vertexNum; i++)
		{
			if (inDegree[i] == 0)
			{
				for (int *p = Graph[i]; p < G[i]; p++)
				{
					int &v = *p;
					if (--inDegree[v]==0 && v < i)
						inZeroQue.push(v);
				}
				G[i] = Graph[i];
				cnt++;
			}
		}
		while (!inZeroQue.empty())
		{
			transfer = inZeroQue.front();
			inZeroQue.pop();
			for (int *p = Graph[transfer]; p < G[transfer]; p++)
			{
				int &v = *p;
				if (--inDegree[v] == 0)
					inZeroQue.push(v);
			}
			G[transfer] = Graph[transfer];
			cnt++;
		}
		//std::cout << "一共删除入度为0的点数为：" << cnt << std::endl;
		//数据预处理2.将每个顶点指向顶点大小排序
		for (i = 0; i < vertexNum; i++)
		{
			std::sort(Graph[i], G[i]);
		}
	}
	//找环 
	void searchForLoop()
	{
		visited = new bool[vertexNum]();
		int vis[vertexNum]; // 数组长度可以是变量？，至少g++编译可以通过，可能是编译器自己做了调整
		memset(vis, -1, vertexNum*sizeof(int));
		visited1 = vis;
		loop = new int[7];
		resTotalNum=resNum[0]=resNum[1]=resNum[2]=resNum[3]=resNum[4]=0;
		loop3=result3, loop4=result4, loop5=result5, loop6=result6, loop7=result7;
		
		// 递归找环
		for (int i = 0; i < vertexNum; i++)
		{
			if (Graph[i] < G[i])
			{
				// 3邻域减枝
				for (int *p1=GraphInv[i]; p1<GInv[i]; p1++)
				{
					//visited1[x1] = -2;
					int &x1 = *p1;
					if (x1 < i || visited[x1])
						continue;
					visited[x1] = true;
					for (int *p2=GraphInv[x1]; p2<GInv[x1]; p2++)
					{
						int &x2 = *p2;
						if (x2 < i || visited[x2])
							continue;
						visited1[x2] = i;
						visited[x2] = true;
						for (int *p3=GraphInv[x2]; p3<GInv[x2]; p3++)
						{
							int &x3 = *p3;
							if (x3 < i || visited[x3])
								continue;
							visited1[x3] = i;
						}
						visited[x2] = false;
					}
					visited[x1] = false;
				}
				for (int *p=GraphInv[i]; p<GInv[i]; p++)
					visited1[*p] = -2;
				dfs(i);
				for (int *p=GraphInv[i]; p<GInv[i]; p++)
					visited1[*p] = i;
			}
		}
		resTotalNum = resNum[0]+resNum[1]+resNum[2]+resNum[3]+resNum[4];
	}
	// 循环找环
	void dfs(int &head)
	{
		int *p1, *p2, *p3, *p4, *p5, *p6;
		visited[head] = true;
		*loop++ = head;
		for (p1=Graph[head]; p1<G[head]; p1++) // depth=1
			if (*p1 > head)
				break;
		for (;p1<G[head]; p1++)
		{
			int &v1 = *p1;
			visited[v1] = true;
			*loop++ = v1;
			for (p2=Graph[v1]; p2<G[v1]; p2++) // depth=2
				if (*p2 > head)
					break;
			for (; p2<G[v1]; p2++)
			{
				int &v2 = *p2;
				if (visited[v2])
					continue;
				if (visited1[v2] == -2)
				{
					*loop3++ = dataOrdered[loop[-2]];
					*loop3++ = dataOrdered[loop[-1]];
					*loop3++ = dataOrdered[v2];
					resNum[0]++;
				}
				visited[v2] = true;
				*loop++ = v2;
				for (p3=Graph[v2]; p3<G[v2]; p3++) //depth=3
					if (*p3 > head)
						break;
				for (; p3<G[v2]; p3++)
				{
					int &v3 = *p3;
					if (visited[v3])
						continue;
					if (visited1[v3] == -2)
					{
						*loop4++ = dataOrdered[loop[-3]];
						*loop4++ = dataOrdered[loop[-2]];
						*loop4++ = dataOrdered[loop[-1]];
						*loop4++ = dataOrdered[v3];
						resNum[1]++;
					}
					visited[v3] = true;
					*loop++ = v3;
					for (p4=Graph[v3]; p4<G[v3]; p4++) //depth=4
						if (*p4 > head)
							break;
					for (; p4<G[v3]; p4++)
					{
						int &v4 = *p4;
						if (visited[v4])
							continue;
						if (visited1[v4] == -2)
						{
							*loop5++ = dataOrdered[loop[-4]];
							*loop5++ = dataOrdered[loop[-3]];
							*loop5++ = dataOrdered[loop[-2]];
							*loop5++ = dataOrdered[loop[-1]];
							*loop5++ = dataOrdered[v4];
							resNum[2]++;
						}
						else if (visited1[v4] != head)
							continue;
						visited[v4] = true;
						*loop++ = v4;
						for (p5=Graph[v4]; p5<G[v4]; p5++) //depth=5
							if (*p5 > head)
								break;
						for (; p5<G[v4]; p5++)
						{
							int &v5 = *p5;
							if (visited[v5])
								continue;
							if (visited1[v5] == -2)
							{
								*loop6++ = dataOrdered[loop[-5]];
								*loop6++ = dataOrdered[loop[-4]];
								*loop6++ = dataOrdered[loop[-3]];
								*loop6++ = dataOrdered[loop[-2]];
								*loop6++ = dataOrdered[loop[-1]];
								*loop6++ = dataOrdered[v5];
								resNum[3]++;
							}
							else if (visited1[v5] != head)
								continue;
							visited[v5] = true;
							*loop++ = v5;
							for (p6=Graph[v5]; p6<G[v5]; p6++) //depth=6
								if (*p6 > head)
									break;
							for(; p6<G[v5]; p6++)
							{
								int &v6 = *p6;
								if (visited1[v6] == -2 && !visited[v6])
								{
									*loop7++ = dataOrdered[loop[-6]];
									*loop7++ = dataOrdered[loop[-5]];
									*loop7++ = dataOrdered[loop[-4]];
									*loop7++ = dataOrdered[loop[-3]];
									*loop7++ = dataOrdered[loop[-2]];
									*loop7++ = dataOrdered[loop[-1]];
									*loop7++ = dataOrdered[v6];
									resNum[4]++;
								}
							}
							visited[v5] = false;
							--loop;
						}
						visited[v4] = false;
						--loop;
					}
					visited[v3] = false;
					--loop;
				}
				visited[v2] = false;
				--loop;
			}
			visited[v1] = false;
			--loop;
		}
		visited[head] = false;
		--loop;
	}
	//保存数据
	void save()
	{
		//保存文件
		off_t fileSize = 140*1024*1024; // 最大输出文件大小
		int fd = open(OUTFILEPATH, O_RDWR|O_CREAT, 0666);
		//int ret = fallocate(fd, 0, 0, fileSize);
		//if (ret != 0) { 
    		//printf("fallocate err %d\n", ret);
  		//}
		//int ret = fallocate(fd, 0, 0, fileSize);
		//lseek(fd, fileSize-1, SEEK_SET);
		ftruncate(fd, fileSize);
		//write(fd, "", 1);
		char *mbuf = (char *)mmap(NULL, fileSize, PROT_WRITE, MAP_SHARED, fd, 0);
		char ch, *p = mbuf, *p2, *tmp = mbuf;
		int num = resTotalNum;
		// 写结果个数
		do{
			*mbuf++ = (num % 10) + '0';
			num /= 10;
		}while(num != 0);
		p2 = mbuf - 1;
		while (p < p2) { ch = *p; *p++ = *p2; *p2-- = ch; }
		*mbuf++ = '\n';
		// 写结果内容
		for (int i = 0; i < 5; i++)
		{
			int k = i+3;
			resNum[i] *= k;
			for (int j = 0; j<resNum[i]; j++)
			{
				u32 x = result[i][j];
				p = mbuf;
				do 
				{
					*p++ = (x % 10) + '0';
					x /= 10;
				}while(x != 0);
				p2 = p--;
				while (mbuf < p) {ch = *p; *p-- = *mbuf; *mbuf++ = ch;}
				mbuf = p2;
				if (j != 0 && (j+1) % k == 0)
					*mbuf++ = '\n';			
				else
					*mbuf++ = ',';
			}
		}
		ftruncate(fd, mbuf-tmp);
		//close(fd);
		exit(0);
	}
private:
	std::unordered_map<u32,int> idMap; //将数据中的id映射到0-n,离散化后续优化可以尝试哈希表或者红黑树
	std::vector<int> inDegree; //每个顶点入度个数
	int rowNum; // 输入数据行数
	int vertexNum; // 顶点数
	bool *visited;
	int *visited1;
	int *loop;
	int *loop3, *loop4, *loop5, *loop6, *loop7;
	int resNum[5];
	int resTotalNum;
};

int main()
{
	MySolver solver;
	solver.mmapLoadTxt();
	solver.establishAdjacencyTable();
	solver.searchForLoop();
	solver.save();
}
