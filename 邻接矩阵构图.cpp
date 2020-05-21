#include <iostream>
#include <vector>

using namespace std;

class MatrixDirectGraph {
public:
	// 以邻接矩阵创建图
	// vexs：使用到的点集  edges：涵盖的边
	MatrixDirectGraph(vector<unsigned int> vexs, vector<vector<unsigned int>> edges);	
	~MatrixDirectGraph();

	// 打印邻接矩阵
	void gMPrint();

private:
	vector<unsigned int> mVexs;		// 顶点集合
	unsigned int mVexNum;			// 顶点数
	unsigned int mEdgNum;			// 边数
	unsigned int mMatrix[100][100];		// 邻接矩阵

private:
	unsigned int getPosition(int dat);
};

MatrixDirectGraph::MatrixDirectGraph(vector<unsigned int> vexs, vector<vector<unsigned int>> edges) {
	unsigned int p1, p2;
	mVexNum = vexs.size();	// 初始化顶点数
	mEdgNum = edges.size();	// 初始化边数
	for (unsigned int i = 0; i < mVexNum; i++)	// 初始化顶点
		mVexs.push_back(vexs[i]);

	// 初始化"边"
	for (unsigned int i = 0; i < mEdgNum; i++)
	{
		// 读取边的起始顶点和结束顶点
		p1 = getPosition(edges[i][0]);
		p2 = getPosition(edges[i][1]);

		mMatrix[p1][p2] = 1;
	}
}

MatrixDirectGraph::~MatrixDirectGraph(){

}

void MatrixDirectGraph::gMPrint() {
	cout << "Martix Graph:" << endl;
	for (unsigned int i = 0; i < mVexNum; i++)
	{
		for (unsigned int j = 0; j < mVexNum; j++)
			cout << mMatrix[i][j] << " ";
		cout << endl;
	}
}

unsigned int MatrixDirectGraph::getPosition(int dat)
{
	for (unsigned int i = 0; i<mVexNum; i++)
		if (mVexs[i] == dat)
			return i;
	return -1;
}

int main() {
	vector<unsigned int> vexs = { 1, 2, 3, 4, 5, 6, 7 };
	vector<vector<unsigned int>> edges = {
		{ 1, 2 },
		{ 2, 3 },
		{ 2, 5 },
		{ 2, 6 },
		{ 3, 5 },
		{ 4, 3 },
		{ 5, 2 },
		{ 5, 4 },
		{ 6, 7 } };

	MatrixDirectGraph* pG;
	pG = new MatrixDirectGraph(vexs, edges);

	pG->gMPrint();   // 打印图

	cout << "over" << endl;
	system("pause");
	return 0;
}