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
	// �ڽӱ��б��Ӧ������Ķ���
	class ENode
	{
	public:
		unsigned int ivex;           // �ñ���ָ��Ķ����λ��
		ENode *nextEdge;    // ָ����һ������ָ��
		//bool hasVisited;    //  �Ƿ񱻷��ʹ� 
	};

	// �ڽӱ��б�Ķ���
	class VNode
	{
	public:
		unsigned int data;          // ������Ϣ
		ENode *firstEdge;   // ָ���һ�������ö���Ļ�
	};
public:
	ListDirectionalGraph(vector<unsigned int> vexs, vector<vector<unsigned int> > edges);
	~ListDirectionalGraph();

	// ��ӡ�ڽӱ�ͼ
	void gLPrint();

	// ��⻷
	void checkCircle();

	// ����+ȥ���ظ���·��
	void remAndSort(string storePath);

	// ȡ������С�������ڵ�һλ
	void reCircle(vector<unsigned int> &perLine);

	// ����������result
	void saveResultData(string storePath, vector<vector<unsigned int>> resData);
	

private:
	unsigned int mVexNum;	// ������Ŀ
	unsigned int mEdgeNum;	// ͼ�ıߵ���Ŀ
	

	//VNode mVexs[30000];     // �ڽӱ� 
	vector<VNode> mVexs;

	vector<vector<unsigned int> > firstFindCircle;

	vector<vector<unsigned int> > finalRes;
	
	vector<vector<unsigned int> > finalResAfterSort;


	
private:
	unsigned int getPosition(unsigned int dst);
	
	// ��node�ڵ����ӵ�list�����
	void linkLast(ENode *list, ENode *node);
};

void ListDirectionalGraph::saveResultData(string storePath, vector<vector<unsigned int>> resData) {
	string line;
	unsigned int j = 0;
	ofstream fout(storePath.c_str());

	//if (!fout.is_open()) {
	//	cout << "��Ԥ�����ļ�ʧ��" << endl;
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

// ȡ������С�������ڵ�һλ
void ListDirectionalGraph::reCircle(vector<unsigned int> &perLine) {
	unsigned int idx = 0;
	unsigned int minVal = perLine[0];
	
	//  ���������е���Сֵ���±� 
	for (unsigned int i = 1; i < perLine.size(); i++) {
		if (perLine[i] < minVal) {
			idx = i;
			minVal = perLine[i];
		}
	}	
	
	//  ����С���ƶ�����ͷ��������˳���ܱ䶯 
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

//  �Ƚ���
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
 
// ����+ȥ���ظ���·��
void ListDirectionalGraph::remAndSort(string storePath) {
#ifdef DEBUG
	cout << "first find circle : " << firstFindCircle.size() << endl;
#endif // DEBUG

	vector<unsigned int> resIdx;
	vector<unsigned int> resIdd;

	// ��ÿһ����һ�£���������һ��
	for (unsigned int i = 0; i < firstFindCircle.size(); i++) {
		reCircle(firstFindCircle[i]);
	}
	
	//  ʹ�ñȽ����Զ�ά�������� 
	sort(firstFindCircle.begin(), firstFindCircle.end(),cmpBySize);

	finalRes.push_back(firstFindCircle[0]);
	resIdx.push_back(firstFindCircle[0][0]);
	unsigned int j = 0, curPos = 0;
	
	//  ȥ�ز���
	for(unsigned int i= 0; i < firstFindCircle.size(); i++ ) {
		if (resIdx[j] == firstFindCircle[i][0]){		// ��һλ��ͬ 		
			if (firstFindCircle[curPos].size() != firstFindCircle[i].size()) {	// �ߴ粻ͬ ��һ����ͬ
				curPos = i;
				finalRes.push_back(firstFindCircle[i]);
				resIdx.push_back(firstFindCircle[i][0]);
				j++;
			}
			else{    //�ߴ���ͬ 
				unsigned int simIdx = 0;	// ����������ͬ������
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

	// д����result�ļ�
	saveResultData(storePath, finalRes);
}

// ��⻷
void ListDirectionalGraph::checkCircle() {
	ENode *p = NULL, *n = NULL;
	unsigned int nextNode = 0, depth = 0, lastTop = 0;
	vector<bool> hasVisited;    //��¼�õ��Ƿ񱻷��ʹ�
	hasVisited.resize(mVexNum, false);
	vector<unsigned int> path;          //ʹ������������·��

	// �ǵݹ飬ÿ�μ��ֻ�Ƚϵ�һ�����Ƿ�ɻ�
	for (unsigned int i = 0; i < mVexNum; i++) {
		depth = 0;
#ifdef DEBUG
		if (i % 100 == 0) cout << i << "/" << mVexNum <<endl;	
#endif
		hasVisited[i] = true;     //��¼�õ㱻������
		path.push_back(i);        //�����������Ԫ��
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
									hasVisited[nextNode] = true;     //��¼�õ㱻������
									path.push_back(nextNode);        //�����������Ԫ��
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
					while (n == NULL) {   //���˲��� 
						lastTop = path[depth - 1];
						hasVisited[path[depth - 1]] = false;
						path.pop_back();
						depth--;
						if (depth) {           //��depth Ϊ0ʱ�˳����� 
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

 //����ͼ 
ListDirectionalGraph::ListDirectionalGraph(vector<unsigned int> vexs, vector<vector<unsigned int> > edges) {
	unsigned int p1, p2;
	ENode *node1;
	// ��ʼ��"������"��"����"
	mVexNum = vexs.size();
	mEdgeNum = edges.size();

	mVexs.resize(mVexNum);

	// ��ʼ������
	for (unsigned int i = 0; i < mVexNum; i++) {
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}
	
	// ��ʼ����
	for (unsigned int i = 0; i < mEdgeNum; i++) {
		// ��ȡ�ߵ���ʼ����ͽ�������
		p1 = getPosition(edges[i][0]);
		p2 = getPosition(edges[i][1]);

		// ��ʼ��node1
		node1 = new ENode();
		node1->ivex = p2;
		node1->nextEdge = NULL;
		//node1->hasVisited = false;
		 
		// ��node1���ӵ�"p1���������ĩβ"
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			linkLast(mVexs[p1].firstEdge, node1);
	}
	
}

ListDirectionalGraph::~ListDirectionalGraph() {

}

struct Data {	// ��������ÿһ�еĸ�ʽ
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
	
	void  remPoit(vector<unsigned int> &vexs);       //ɾ��û����Ⱥͳ��ȵĵ� �ͱ� 

private:
	bool init();
	bool loadTestData();

	void  removePoint(vector<unsigned int> &point, vector<unsigned int> &vexs);

private:
	

	vector<Data> testDataSet;
	//set<unsigned int> testfromId;      //���ϱ�����Զ�ȥ�أ��������ݵ�ʹ�� 
	
	vector<unsigned int> testFromId;   // ���鱣��������ڲ�����ȥ�����Ⱥ����Ϊ0�ĵ�ʱʹ�� 
	
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
		cout << "���ļ�ʧ��" << endl;
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
				char c = sin.peek();	// �鿴��һ���ַ�
				if (int(c) != -1) {
					sin >> dataV;
					feature.push_back(dataV);
					sin >> ch;       //����ո� 
					i++;
				}
				else {
					cout << "�ļ����ݸ�ʽ����ȷ"<< endl;
					return false;
				}
			}
			//testDataSet.push_back(Data(feature[0], feature[1], feature[2]));   //ѹ��һ���ṹ�� 
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
		unsigned int  nodeCnt = 0;       //��¼�������
		unordered_map<unsigned int, int>  nodemap;
		for (unsigned int &x : point) {
			nodemap[x] = nodeCnt++;           //��ÿ������ӳ�� 
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
		// ȥ����Ȼ����Ϊ0��ĵ㼯 
		vector<unsigned int> idAfter;
		for (unsigned int i = 0; i < point.size(); i++) {
			if (hashTableIn[nodemap[point[i]]] == false || hashTableOut[nodemap[point[i]]] == false) {
				flag = true;
				continue;
			}
			idAfter.push_back(point[i]);      //idAfter ��ֻ������Ⱥͳ��ȶ�����0�ĵ� 
		}
		point = idAfter;       //���¸�ֵ��ԭ����

		// ȥ���� ���Ϊ0�ĳ��ߣ� ����Ϊ0�����
		

		for (unsigned int i = 0; i<point.size(); i++) {
			hashTable[nodemap[point[i]]] = true;
		}
		vector<unsigned int>  link;     //����ȥ���ߺ������
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
	auto  tmp = vexs;       //�Զ�����
	sort(tmp.begin(), tmp.end());      //�Դ���ĵ㼯��������

	//  �Ե㼯����ȥ�� �� unique �����ظ�Ԫ�ص�λ�ã� ֱ��ɾ����ĩβ���� 
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

	//  ����Ȼ����Ϊ0�ĵ����ɾ����ɾ������������ͼ
	removePoint(tmp, vexs);

	unsigned int nodeCnt = 0;
	unordered_map<unsigned int, unsigned int>  idHash;   // ������ĵ� ��0��n ӳ�� 

	for (unsigned int &x : tmp) {        //feach ���,�����е�ÿ��Ԫ�� 
		idHash[x] = nodeCnt++;      //�Ե�ֵ������ֵ����ӳ�䡣 
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
	pG = new ListDirectionalGraph(testFromId, testTransLink);    // ����ͼ��������Ƕ���ͱ� 
#ifdef DEBUG
	cout << "Has Created Over" << endl;
#endif // DEBUG

	//pG->gLPrint(); // ��ӡͼ�����ڽӱ���ʽ

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
	startTime = clock();	// ��ʱ��ʼ

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
	endTime = clock();	// ��ʱ����
	std::cout << "The run time is : "
		<< (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
#endif // DEBUG	

#ifdef DEBUG
	system("pause");
#endif // DEBUG	
	return 0;
}
