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
#include <time.h>

#define INFILEPATH  "/data/test_data.txt"
#define OUTFILEPATH "/projects/student/result.txt"
#define MAXLINE 280000
typedef unsigned int u32;

u32 result3[3*500000], result4[4*500000], result5[5*1000000], result6[6*2000000], result7[7*3000000];
u32 *result[]={result3, result4, result5, result6, result7};
u32 Graph[50000][30]; // 邻接表
u32 GraphInv[50000][30]; // 逆邻接表
u32 *G[50000]; // 记录邻接表的尾指针
u32 *GInv[50000]; // 记录逆邻接表的尾指针
u32 inputData[MAXLINE*2]; 
int inDegree[50000];
int maxVertex = 50000;
//u32 dataOrdered[MAXLINE*2];
//char resString[140*1024*1024];

class MySolver
{
public:
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
        //maxVertex = 0;
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
            //if (maxVertex < transferID)
            	//maxVertex = transferID;
            //if (maxVertex < receiverID)
            	//maxVertex = receiverID;
        }
	}
	// 构图
	void establishAdjacencyTable()
	{
		int i = 0;
		// 1.映射
		//memcpy(dataOrdered, inputData, rowNum*sizeof(u32));
		//std::sort(dataOrdered, dataOrdered+rowNum);
		//vertexNum = std::unique(dataOrdered, dataOrdered+rowNum) - dataOrdered;
		//maxVertex = dataOrdered[vertexNum-1];
		//maxVertex++;
		for (i = 0; i < maxVertex; i++)
		{			
			G[i] = Graph[i];
			GInv[i] = GraphInv[i];
			//idMap[dataOrdered[i]] = i;
		}
		// 2.连接表
		//inDegree = std::vector<int>(280000, 0);
		//inDegree.resize(280000);
		int transfer, receiver;
		for (i = 0; i < rowNum; i += 2)
		{
			transfer = inputData[i];
			receiver = inputData[i+1]; //这里可以用位运算改进试试
			if (transfer > maxVertex || receiver > maxVertex)
				continue;
			*G[transfer]++ = receiver;
			*GInv[receiver]++ = transfer;
			++inDegree[receiver];
		}

		//数据预处理
		//1 将度（入度加出度）为1的点去除<由于删除出度为0的点需要记录G[v][u],这里先仅删除入度为0的点试试
		//std::queue<int> inZeroQue;

		int inZeroStack[50000], top=0;
		for (i = 0; i < maxVertex; i++)
		{
			if (inDegree[i] == 0)
			{
				for (u32 *p = Graph[i]; p < G[i]; p++)
				{
					u32 &v = *p;
					if (--inDegree[v] == 0 && v < i)
						inZeroStack[++top] = v;
				}
				G[i] = Graph[i];
			}
		}
		while (top > 0)
		{
			transfer = inZeroStack[top];
			--top;
			for (u32 *p = Graph[transfer]; p < G[transfer]; p++)
			{
				u32 &v = *p;
				if (--inDegree[v] == 0)
					inZeroStack[++top] = v;
			}
			G[transfer] = Graph[transfer];
		}
		//std::cout << "一共删除入度为0的点数为：" << cnt << std::endl;
		//数据预处理2.将每个顶点指向顶点大小排序
		for (i = 0; i < maxVertex; i++)
		{
			std::sort(Graph[i], G[i]);
		}
	}
	//找环 
	void searchForLoop()
	{
		bool visited[maxVertex]={false};
		int visited1[maxVertex]; // 数组长度可以是变量？，至少g++编译可以通过，可能是编译器自己做了调整
		memset(visited1, -1, maxVertex*sizeof(int));
		//visited1 = vis;
		//loop = new u32[7];
		resTotalNum=resNum[0]=resNum[1]=resNum[2]=resNum[3]=resNum[4]=0;
		loop3=result3, loop4=result4, loop5=result5, loop6=result6, loop7=result7;
		
		// 递归找环
		for (u32 i = 0; i < maxVertex; i++)
		{
			if (Graph[i] < G[i])
			{
				// 3邻域减枝
				for (u32 *p1=GraphInv[i]; p1<GInv[i]; p1++)
				{
					//visited1[x1] = -2;
					u32 &x1 = *p1;
					if (x1 < i)
						continue;
					visited[x1] = true;
					for (u32 *p2=GraphInv[x1]; p2<GInv[x1]; p2++)
					{
						u32 &x2 = *p2;
						if (x2 < i || visited[x2])
							continue;
						visited1[x2] = i;
						//visited[x2] = true;
						for (u32 *p3=GraphInv[x2]; p3<GInv[x2]; p3++)
						{
							u32 &x3 = *p3;
							if (x3 < i || visited[x3])
								continue;
							visited1[x3] = i;
						}
						//visited[x2] = false;
					}
					visited[x1] = false;
				}
				for (u32 *p=GraphInv[i]; p<GInv[i]; p++)
					visited1[*p] = -2;
				dfs(i, visited, visited1);
				for (u32 *p=GraphInv[i]; p<GInv[i]; p++)
					visited1[*p] = i;
			}
		}
		resTotalNum = resNum[0]+resNum[1]+resNum[2]+resNum[3]+resNum[4];
	}
	// 循环找环
	void dfs(u32 &head, bool *visited, int *visited1)
	{
		u32 *p1, *p2, *p3, *p4, *p5, *p6;
		visited[head] = true;
		//*loop++ = head;
		for (p1=Graph[head]; p1<G[head]; p1++) // depth=1
			if (*p1 > head)
				break;
		for (;p1<G[head]; p1++)
		{
			u32 &v1 = *p1;
			visited[v1] = true;
			//*loop++ = v1;
			for (p2=Graph[v1]; p2<G[v1]; p2++) // depth=2
				if (*p2 > head)
					break;
			for (; p2<G[v1]; p2++)
			{
				u32 &v2 = *p2;
				if (visited[v2])
					continue;
				if (visited1[v2] == -2)
				{
					*loop3++ = head;
					*loop3++ = v1;
					*loop3++ = v2;
					resNum[0]++;
				}
				visited[v2] = true;
				//*loop++ = v2;
				for (p3=Graph[v2]; p3<G[v2]; p3++) //depth=3
					if (*p3 > head)
						break;
				for (; p3<G[v2]; p3++)
				{
					u32 &v3 = *p3;
					if (visited[v3])
						continue;
					if (visited1[v3] == -2)
					{
						*loop4++ = head;
						*loop4++ = v1;
						*loop4++ = v2;
						*loop4++ = v3;
						resNum[1]++;
					}
					visited[v3] = true;
					//*loop++ = v3;
					for (p4=Graph[v3]; p4<G[v3]; p4++) //depth=4
						if (*p4 > head)
							break;
					for (; p4<G[v3]; p4++)
					{
						u32 &v4 = *p4;
						if (visited[v4])
							continue;
						if (visited1[v4] == -2)
						{
							*loop5++ = head;
							*loop5++ = v1;
							*loop5++ = v2;
							*loop5++ = v3;
							*loop5++ = v4;
							resNum[2]++;
						}
						else if (visited1[v4] != head)
							continue;
						visited[v4] = true;
						//*loop++ = v4;
						for (p5=Graph[v4]; p5<G[v4]; p5++) //depth=5
							if (*p5 > head)
								break;
						for (; p5<G[v4]; p5++)
						{
							u32 &v5 = *p5;
							if (visited[v5])
								continue;
							if (visited1[v5] == -2)
							{
								*loop6++ = head;
								*loop6++ = v1;
								*loop6++ = v2;
								*loop6++ = v3;
								*loop6++ = v4;
								*loop6++ = v5;
								resNum[3]++;
							}
							else if (visited1[v5] != head)
								continue;
							visited[v5] = true;
							//*loop++ = v5;
							for (p6=Graph[v5]; p6<G[v5]; p6++) //depth=6
								if (*p6 > head)
									break;
							for(; p6<G[v5]; p6++)
							{
								u32 &v6 = *p6;
								if (visited1[v6] == -2 && !visited[v6])
								{
									*loop7++ = head;
									*loop7++ = v1;
									*loop7++ = v2;
									*loop7++ = v3;
									*loop7++ = v4;
									*loop7++ = v5;
									*loop7++ = v6;
									resNum[4]++;
								}
							}
							visited[v5] = false;
							//--loop;
						}
						visited[v4] = false;
						//--loop;
					}
					visited[v3] = false;
					//--loop;
				}
				visited[v2] = false;
				//--loop;
			}
			visited[v1] = false;
			//--loop;
		}
		visited[head] = false;
		//--loop;
	}
	//保存数据
	void save()
	{
		//保存文件
		off_t fileSize = 140*1024*1024; // 最大输出文件大小
		//char *res = resString, *tmp=res;
		//tmp += fileSize-1;
		//res = tmp;

		int fd = open(OUTFILEPATH, O_RDWR|O_CREAT, 0666);
		//int ret = fallocate(fd, 0, 0, fileSize);
		//if (ret != 0) { 
    		//printf("fallocate err %d\n", ret);
  		//}
		//int ret = fallocate(fd, 0, 0, fileSize);
		//lseek(fd, fileSize-1, SEEK_SET);
		ftruncate(fd, fileSize);
		//write(fd, "", 1);
		char *mbuf = (char *)mmap(NULL, fileSize, PROT_WRITE, MAP_SHARED, fd, 0);//, *tmp = mbuf;
		mbuf += fileSize-1; //从后往前写

		*mbuf-- = '\n';
		for (int i = 4; i > -1; i--)
		{
			int k = i+3;
			resNum[i] *= k;
			for (int j = resNum[i]-1; j > -1; j--)
			{
				u32 x = result[i][j];
				//for(;;)
				//{
				if (x < 10) {
					*mbuf-- = x+'0';
				}
				else if (x < 100) {
					*mbuf-- = (x%10)+'0';
					*mbuf-- = (x/10)+'0';
				}
				else if (x < 1000) {
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					*mbuf-- = (x/10)+'0';
				}
				else if (x < 10000){
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					*mbuf-- = (x/10)+'0';
				}
				else if (x < 100000){
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					*mbuf-- = (x/10)+'0';
				}
				else{
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					x /= 10;
					*mbuf-- = (x%10)+'0';
					*mbuf-- = (x/10)+'0';
				}
				if (j % k == 0)
					*mbuf-- = '\n';
				else
					*mbuf-- = ',';
			}
		}
		do{
			*mbuf-- = (resTotalNum%10) + '0';
			resTotalNum /= 10;
		}while(resTotalNum != 0);
		//ftruncate(fd, res-tmp);
		//char *mbuf = (char *)mmap(NULL, res-tmp, PROT_WRITE, MAP_SHARED, fd, 0);//, *tmp = mbuf;]
		//memcpy(mbuf, tmp+1, res-tmp);
		//ftruncate(fd, mbuf-tmp);
		close(fd);
		//exit(0);
	}
private:
	//std::unordered_map<u32,int> idMap; //将数据中的id映射到0-n,离散化后续优化可以尝试哈希表或者红黑树
	//std::vector<int> inDegree; //每个顶点入度个数
	int rowNum; // 顶点数
	//bool *visited;
	//int *visited1;
	u32 *loop3, *loop4, *loop5, *loop6, *loop7;
	int resNum[5], resTotalNum;
};

int main()
{
	MySolver solver;
	solver.mmapLoadTxt();
	solver.establishAdjacencyTable();
	solver.searchForLoop();
	solver.save();
}
