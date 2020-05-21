#include <iostream>  
#include <fstream>         
#include <vector>          
#include <memory>             
#include <sstream>             
#include <algorithm>   
#include <unordered_map>

//#define DEBUG

#ifdef DEBUG
#include <ctime>
#endif // DEBUG

using namespace std;

class ListDirectionalGraph {
private:
	// 邻接表中表对应的链表的顶点
	class ENode
	{
	public:
		unsigned int ivex;           // 该边所指向的顶点的位置
		ENode *nextEdge;    // 指向下一条弧的指针
		//bool hasVisited;    //  是否被访问过 
	};

	// 邻接表中表的顶点
	class VNode
	{
	public:
		unsigned int data;          // 顶点信息
		ENode *firstEdge;   // 指向第一条依附该顶点的弧
	};
public:
	ListDirectionalGraph(vector<unsigned int> vexs, vector<vector<unsigned int> > edges);
	~ListDirectionalGraph();

	// 打印邻接表图
	void gLPrint();

	// 检测环
	void checkCircle();

	// 排序+去除重复的路劲
	void remAndSort(string storePath);

	// 取环的最小的起点放在第一位
	void reCircle(vector<unsigned int> &perLine);

	// 保存数据至result
	void saveResultData(string storePath, vector<vector<unsigned int>> resData);
	

private:
	unsigned int mVexNum;	// 顶点数目
	unsigned int mEdgeNum;	// 图的边的数目
	

	//VNode mVexs[30000];     // 邻接表 
	vector<VNode> mVexs;

	vector<vector<unsigned int> > firstFindCircle;

	vector<vector<unsigned int> > finalRes;
	
	vector<vector<unsigned int> > finalResAfterSort;


	
private:
	unsigned int getPosition(unsigned int dst);
	
	// 将node节点链接到list的最后
	void linkLast(ENode *list, ENode *node);
};

void ListDirectionalGraph::saveResultData(string storePath, vector<vector<unsigned int>> resData) {
	string line;
	unsigned int j = 0;
	ofstream fout(storePath.c_str());

	//if (!fout.is_open()) {
	//	cout << "打开预测结果文件失败" << endl;
	//}
	fout << resData.size() << endl;

	for (unsigned int i = 0; i < resData.size(); i++) {
		for (j = 0; j < resData[i].size() - 1; j++) {
			fout << resData[i][j] << ",";
		}
		fout << resData[i][j] << endl;
	}

	fout.close();
}

// 取环的最小的起点放在第一位
void ListDirectionalGraph::reCircle(vector<unsigned int> &perLine) {
	unsigned int idx = 0;
	unsigned int minVal = perLine[0];
	
	//  查找数组中的最小值和下标 
	for (unsigned int i = 1; i < perLine.size(); i++) {
		if (perLine[i] < minVal) {
			idx = i;
			minVal = perLine[i];
		}
	}	
	
	//  将最小的移动到开头，其他的顺序不能变动 
	vector<unsigned int> mPerLine;
	unsigned int thd = idx;
	while (thd != perLine.size()) {
		mPerLine.push_back(perLine[thd]);
		thd++;
	}
	thd = 0;
	while (thd != idx) {
		mPerLine.push_back(perLine[thd]);
		thd++;
	}
	perLine = mPerLine;
	
	
}

//  比较器
bool cmpBySize(vector<unsigned int> &circleA,vector<unsigned int> &circleB){
	if(circleA.size() == circleB.size()){
		unsigned int i=0;
		while(circleA[i] == circleB[i]){
			if(i <circleA.size() - 1)
				i++;
			else
				break;
		}
		return circleA[i] < circleB[i]; 
	}
	else
		return circleA.size() < circleB.size(); 
}
 
// 排序+去除重复的路劲
void ListDirectionalGraph::remAndSort(string storePath) {
#ifdef DEBUG
	cout << "first find circle : " << firstFindCircle.size() << endl;
#endif // DEBUG

	vector<unsigned int> resIdx;
	vector<unsigned int> resIdd;

	// 先每一行排一下，再整体排一下
	for (unsigned int i = 0; i < firstFindCircle.size(); i++) {
		reCircle(firstFindCircle[i]);
	}
	
	//  使用比较器对二维数组排序 
	sort(firstFindCircle.begin(), firstFindCircle.end(),cmpBySize);

	finalRes.push_back(firstFindCircle[0]);
	resIdx.push_back(firstFindCircle[0][0]);
	unsigned int j = 0, curPos = 0;
	
	//  去重操作
	for(unsigned int i= 0; i < firstFindCircle.size(); i++ ) {
		if (resIdx[j] == firstFindCircle[i][0]){		// 第一位相同 		
			if (firstFindCircle[curPos].size() != firstFindCircle[i].size()) {	// 尺寸不同 环一定不同
				curPos = i;
				finalRes.push_back(firstFindCircle[i]);
				resIdx.push_back(firstFindCircle[i][0]);
				j++;
			}
			else{    //尺寸相同 
				unsigned int simIdx = 0;	// 用来返回相同的索引
				for (unsigned int m = 0; m < firstFindCircle[i].size(); m++) {
					if (firstFindCircle[curPos][m] == firstFindCircle[i][m]) {
						simIdx++;
					}
				}
				
				if(simIdx != firstFindCircle[i].size()) {
					finalRes.push_back(firstFindCircle[i]);
					curPos = i;
					resIdx.push_back(firstFindCircle[i][0]);
					j++;
				}
				
			}
		}
		else
		{		
			curPos = i;
			finalRes.push_back(firstFindCircle[i]);
			resIdx.push_back(firstFindCircle[i][0]);
			resIdd.push_back(firstFindCircle[i][1]);
			j++;
		}
		
	}

#ifdef DEBUG
	cout << "final find circle : " << finalRes.size() << endl;
#endif // DEBUG

	// 写入结果result文件
	saveResultData(storePath, finalRes);
}

// 检测环
void ListDirectionalGraph::checkCircle() {
	ENode *p = NULL, *n = NULL;
	unsigned int nextNode = 0, depth = 0, lastTop = 0;
	vector<bool> hasVisited;    //记录该点是否被访问过
	hasVisited.resize(mVexNum, false);
	vector<unsigned int> path;          //使用数组来保存路径

	// 非递归，每次检测只比较第一个点是否成环
	for (unsigned int i = 0; i < mVexNum; i++) {
		depth = 0;
#ifdef DEBUG
		if (i % 100 == 0) cout << i << "/" << mVexNum <<endl;	
#endif
		hasVisited[i] = true;     //记录该点被访问了
		path.push_back(i);        //向数组中添加元素
		depth++;
		p = mVexs[i].firstEdge;
		while (p != NULL) {
			nextNode = p->ivex;	
			if (nextNode > i) {
				n = p;
				while (depth >= 1) {
					while (n != NULL) {
						nextNode = n->ivex;
						if (nextNode >= i) {
							if (!hasVisited[nextNode]) {
								if (depth < 7) {
									hasVisited[nextNode] = true;     //记录该点被访问了
									path.push_back(nextNode);        //向数组中添加元素
									depth++;
									n = mVexs[nextNode].firstEdge;
								}
								else {

									n = n->nextEdge;
								}
							}
							else {
								if (nextNode == i) {
									if (depth >= 3) {
										vector<unsigned int> tmp;
										for (unsigned int t = 0; t < path.size(); t++) {
											tmp.push_back(mVexs[path[t]].data);
										}
										firstFindCircle.push_back(tmp);
									}
								}
								n = n->nextEdge;
							}
						}
						else {
							n = n->nextEdge;
						}
					}
					while (n == NULL) {   //回退操作 
						lastTop = path[depth - 1];
						hasVisited[path[depth - 1]] = false;
						path.pop_back();
						depth--;
						if (depth) {           //当depth 为0时退出查找 
							n = mVexs[path[depth - 1]].firstEdge;
							while (n != NULL && n->ivex <= lastTop) {
								n = n->nextEdge;
							}
						}
						else {
							break;
						}
					}
				}
				
			}
			p = p->nextEdge;
		}
		while (!path.empty()) { 
			hasVisited[path[depth - 1]] = false;
			path.pop_back(); 
			depth--;
		}
	}

#ifdef DEBUG
	cout << mVexNum << "/" << mVexNum << endl;
#endif // DEBUG
}

void ListDirectionalGraph::gLPrint() {
	ENode *node;

	cout << "List Graph:" << endl;
	for (unsigned int i = 0; i < mVexNum; i++)
	{
		cout << i << "  (" << mVexs[i].data << "): ";
		node = mVexs[i].firstEdge;
		while (node != NULL)
		{
			cout << node->ivex << "(" << mVexs[node->ivex].data << ") ";
			node = node->nextEdge;
		}
		cout << endl;
	}
}

unsigned int ListDirectionalGraph::getPosition(unsigned int dat) {
	for (unsigned int i = 0; i < mVexNum; i++) {
		if (mVexs[i].data == dat) {
			return i;
		}
	}
	return -1;
}

void ListDirectionalGraph::linkLast(ENode *list, ENode *node) {
	ENode *p = list;

	while (p->nextEdge)
		p = p->nextEdge;
	p->nextEdge = node;
}

 //构造图 
ListDirectionalGraph::ListDirectionalGraph(vector<unsigned int> vexs, vector<vector<unsigned int> > edges) {
	unsigned int p1, p2;
	ENode *node1;
	// 初始化"顶点数"和"边数"
	mVexNum = vexs.size();
	mEdgeNum = edges.size();

	mVexs.resize(mVexNum);

	// 初始化顶点
	for (unsigned int i = 0; i < mVexNum; i++) {
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}
	
	// 初始化边
	for (unsigned int i = 0; i < mEdgeNum; i++) {
		// 读取边的起始顶点和结束顶点
		p1 = getPosition(edges[i][0]);
		p2 = getPosition(edges[i][1]);

		// 初始化node1
		node1 = new ENode();
		node1->ivex = p2;
		node1->nextEdge = NULL;
		//node1->hasVisited = false;
		 
		// 将node1链接到"p1所在链表的末尾"
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			linkLast(mVexs[p1].firstEdge, node1);
	}
	
}

ListDirectionalGraph::~ListDirectionalGraph() {

}

struct Data {	// 读入数据每一行的格式
	unsigned int fromId;
	unsigned int dstId;
	unsigned int transAmount;
	Data(unsigned int f, unsigned int d, unsigned int t) : fromId(f), dstId(d), transAmount(t) {}
};

class LR {
public:
	LR(string testFile, string resF);
	void showTestData();
	void showResults();
	
	void  remPoit(vector<unsigned int> &vexs);       //删除没有入度和出度的点 和边 

private:
	bool init();
	bool loadTestData();

	void  removePoint(vector<unsigned int> &point, vector<unsigned int> &vexs);

private:
	

	vector<Data> testDataSet;
	//set<unsigned int> testfromId;      //集合保存会自动去重，读入数据的使用 
	
	vector<unsigned int> testFromId;   // 数组保存更有利于操作，去除出度和入度为0的点时使用 
	
	vector<vector<unsigned int> > testTransLink;
	string testFile, resFile;

private:
	unsigned int featuresNum;
};

LR::LR(string testF, string resF)
{
	testFile = testF;
	resFile = resF;
	featuresNum = 0;
	init();
}

void LR::showTestData()
{
	for (unsigned int i = 0; i < testDataSet.size(); i++)
	{
		cout << testDataSet[i].fromId << " "
			<< testDataSet[i].dstId << " "
			<< testDataSet[i].transAmount << endl;
	}
}

bool LR::init()
{
	bool status = loadTestData();
	return true;
}

bool LR::loadTestData()
{
	ifstream infile(testFile.c_str());
	string line;

	if (!infile) {
		cout << "打开文件失败" << endl;
		exit(0);
	}

	while (infile) {
		getline(infile, line);
		if (line.size() > featuresNum) {
			stringstream sin(line);
			char ch;
			unsigned int dataV;
			int i;
			vector<unsigned int> feature;
			i = 0;

			while (sin) {
				char c = sin.peek();	// 查看下一个字符
				if (int(c) != -1) {
					sin >> dataV;
					feature.push_back(dataV);
					sin >> ch;       //缓冲空格 
					i++;
				}
				else {
					cout << "文件数据格式不正确"<< endl;
					return false;
				}
			}
			//testDataSet.push_back(Data(feature[0], feature[1], feature[2]));   //压入一个结构体 
			//testfromId.insert(feature[0]);
			//vector<unsigned int> tLink;  // = {feature[0], feature[1]};
			//tLink.push_back(feature[0]);
			//tLink.push_back(feature[1]);
			//testTransLink.push_back(tLink);
			testFromId.push_back(feature[0]);
			testFromId.push_back(feature[1]);
		}
	}
		
	infile.close();
	return true;
}

bool  cmpBylink(vector<unsigned int> a,vector<unsigned int>b){
	if(a[0] == b[0]){
		return a[1] < b[1];
	}
	else{
		return  a[0] < b[0];
	}
	
}

void  LR::removePoint(vector<unsigned int> &point, vector<unsigned int> &vexs) {
	bool flag = true;
	while (flag) {
		flag = false;
		unsigned int  nodeCnt = 0;       //记录点的数量
		unordered_map<unsigned int, int>  nodemap;
		for (unsigned int &x : point) {
			nodemap[x] = nodeCnt++;           //对每个点做映射 
		}

		bool *hashTableIn = new bool[nodeCnt];
		bool *hashTableOut = new bool[nodeCnt];
		bool *hashTable = new bool[nodeCnt];
		for (unsigned int i = 0; i < nodeCnt; i++) {
			hashTableIn[i] = false;
			hashTableOut[i] = false;
			hashTable[i] = false;
		}

		//vector<bool> hashTableIn, hashTableOut;
		//hashTableIn.resize(nodeCnt, false);
		//hashTableOut.resize(nodeCnt, false);
		for (unsigned int i = 0; i<vexs.size(); i += 2) {
			if (hashTableOut[nodemap[vexs[i]]] == false)
				hashTableOut[nodemap[vexs[i]]] = true;
			if (hashTableIn[nodemap[vexs[i + 1]]] == false)
				hashTableIn[nodemap[vexs[i + 1]]] = true;
		}
		// 去除入度或出度为0后的点集 
		vector<unsigned int> idAfter;
		for (unsigned int i = 0; i < point.size(); i++) {
			if (hashTableIn[nodemap[point[i]]] == false || hashTableOut[nodemap[point[i]]] == false) {
				flag = true;
				continue;
			}
			idAfter.push_back(point[i]);      //idAfter 中只保存入度和出度都大于0的点 
		}
		point = idAfter;       //重新赋值会原数组

		// 去除边 入度为0的出边， 出度为0的入边
		

		for (unsigned int i = 0; i<point.size(); i++) {
			hashTable[nodemap[point[i]]] = true;
		}
		vector<unsigned int>  link;     //保存去除边后的数据
		for (unsigned int i = 0; i<vexs.size(); i += 2) {
			if (hashTable[nodemap[vexs[i]]] == false || hashTable[nodemap[vexs[i + 1]]] == false)
				continue;
			link.push_back(vexs[i]);
			link.push_back(vexs[i + 1]);
		}
		vexs = link;

		delete[]hashTableIn;
		delete[]hashTableOut;
		delete[]hashTable;
	}
	
}

void  LR::remPoit(vector<unsigned int> &vexs){
	auto  tmp = vexs;       //自动变量
	sort(tmp.begin(), tmp.end());      //对传入的点集进行排序

	//  对点集进行去重 ， unique 返回重复元素的位置， 直接删除到末尾即可 
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

	//  对入度或出度为0的点进行删除，删除后再来构建图
	removePoint(tmp, vexs);

	unsigned int nodeCnt = 0;
	unordered_map<unsigned int, unsigned int>  idHash;   // 排序完的点 对0到n 映射 

	for (unsigned int &x : tmp) {        //feach 语句,遍历中的每个元素 
		idHash[x] = nodeCnt++;      //对点值和索引值进行映射。 
	}
#ifdef DEBUG
	cout << nodeCnt << " Nodes in Total" << endl;
#endif	
	unsigned int sz = vexs.size();
	vector<unsigned int> tmp_vect;
	for (unsigned int i = 0; i < sz; i += 2) {
		tmp_vect.push_back(tmp[idHash[vexs[i]]]);
		tmp_vect.push_back(tmp[idHash[vexs[i + 1]]]);
		testTransLink.push_back(tmp_vect);
		while (!tmp_vect.empty()) tmp_vect.pop_back();
	}

	sort(testTransLink.begin(), testTransLink.end());

	vexs = tmp;
}

void LR::showResults() {
	remPoit(testFromId);
		
	ListDirectionalGraph* pG;

	//for (unsigned int i = 0; i < testFromId.size(); i++) {
	//	cout << testFromId[i] << " ";
	//}
	//cout << endl;

	//for (unsigned int i = 0; i < testTransLink.size(); i++) {
	//	for (unsigned int j = 0; j < testTransLink[i].size(); j++)
	//		cout << testTransLink[i][j] << " ";
	//	cout << endl;
	//}
	
#ifdef DEBUG
	cout << "Create the Directional Graph" << endl;
#endif // DEBUG
	pG = new ListDirectionalGraph(testFromId, testTransLink);    // 构造图，传入的是顶点和边 
#ifdef DEBUG
	cout << "Has Created Over" << endl;
#endif // DEBUG

	//pG->gLPrint(); // 打印图，以邻接表形式

#ifdef DEBUG
	cout << "Check Circle Start" << endl;
#endif // DEBUG
	pG->checkCircle();
#ifdef DEBUG
	cout << "Has Checked Over" << endl;
#endif // DEBUG	

#ifdef DEBUG
	cout << "Remove And Sort" << endl;
#endif // DEBUG	
	pG->remAndSort(resFile);
}

int main() {
#ifdef DEBUG
	clock_t startTime, endTime;
	startTime = clock();	// 计时开始

	string testFile = "./data/test_data.txt";
	string resFile = "./projects/student/result.txt";
#else
	string testFile = "/data/test_data.txt";
	string resFile = "/projects/student/result.txt";
#endif // DEBUG	
	
	LR logist(testFile, resFile);
	//logist.showTestData();
	logist.showResults();

#ifdef DEBUG
	endTime = clock();	// 计时结束
	std::cout << "The run time is : "
		<< (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
#endif // DEBUG	

#ifdef DEBUG
	system("pause");
#endif // DEBUG	
	return 0;
}
