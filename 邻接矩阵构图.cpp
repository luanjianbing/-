#include <iostream>
#include <vector>

using namespace std;

class MatrixDirectGraph {
public:
	// ���ڽӾ��󴴽�ͼ
	// vexs��ʹ�õ��ĵ㼯  edges�����ǵı�
	MatrixDirectGraph(vector<unsigned int> vexs, vector<vector<unsigned int>> edges);	
	~MatrixDirectGraph();

	// ��ӡ�ڽӾ���
	void gMPrint();

private:
	vector<unsigned int> mVexs;		// ���㼯��
	unsigned int mVexNum;			// ������
	unsigned int mEdgNum;			// ����
	unsigned int mMatrix[100][100];		// �ڽӾ���

private:
	unsigned int getPosition(int dat);
};

MatrixDirectGraph::MatrixDirectGraph(vector<unsigned int> vexs, vector<vector<unsigned int>> edges) {
	unsigned int p1, p2;
	mVexNum = vexs.size();	// ��ʼ��������
	mEdgNum = edges.size();	// ��ʼ������
	for (unsigned int i = 0; i < mVexNum; i++)	// ��ʼ������
		mVexs.push_back(vexs[i]);

	// ��ʼ��"��"
	for (unsigned int i = 0; i < mEdgNum; i++)
	{
		// ��ȡ�ߵ���ʼ����ͽ�������
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

	pG->gMPrint();   // ��ӡͼ

	cout << "over" << endl;
	system("pause");
	return 0;
}