#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct Coordinate {
	double m_coor[2];

	bool isBigger(int dim, Coordinate coor) const {
		return this->m_coor[dim] > coor.m_coor[dim];
	}
	bool isSmaller(int dim, Coordinate coor) const {
		return this->m_coor[dim] < coor.m_coor[dim];
	}
	bool isEqual(Coordinate coor) const {
		return fabs(this->m_coor[0] - coor.m_coor[0]) < 1e-9 && fabs(this->m_coor[1] - coor.m_coor[1]) < 1e-9;
	}
	double distance(Coordinate coor) const {
		return sqrt(pow(this->m_coor[0] - coor.m_coor[0], 2) + pow(this->m_coor[1] - coor.m_coor[1], 2));
	}
	double distance(int dim, Coordinate coor) const {
		return abs(this->m_coor[dim] - coor.m_coor[dim]);
	}
};

struct PointStruct : public Coordinate {
	char m_data;
	PointStruct() {
		m_data = '\0';
		m_coor[0] = 0.0;
		m_coor[1] = 0.0;
	}
	PointStruct(double x, double y, char data) {
		m_data = data;
		m_coor[0] = x;
		m_coor[1] = y;
	}
};

bool comparePoints(const PointStruct& a, const PointStruct& b, int dim) {
	return a.m_coor[dim] < b.m_coor[dim];
}

PointStruct findMedianPoint(int dim, vector<PointStruct> pList) {
	sort(pList.begin(), pList.end(), [dim](const PointStruct& a, const PointStruct& b) { return comparePoints(a, b, dim); });
	return pList[pList.size() / 2];
}

struct TreeNode : public PointStruct {
	int m_dimension;
	TreeNode* m_pLeftChild;
	TreeNode* m_pRightChild;
	TreeNode() {
		PointStruct();
		m_dimension = 0;
		m_pLeftChild = NULL;
		m_pRightChild = NULL;
	}
	TreeNode(PointStruct point) {
		m_coor[0] = point.m_coor[0];
		m_coor[1] = point.m_coor[1];
		m_data = point.m_data;
		m_dimension = NULL;
		m_pLeftChild = NULL;
		m_pRightChild = NULL;
	}
	~TreeNode() {
		delete m_pLeftChild;
		delete m_pRightChild;
	}
};

TreeNode* buildTree(vector<PointStruct>& pList, int d) {
	if (pList.empty()) return NULL;
	int dimension = d % 2;
	PointStruct medianP = findMedianPoint(dimension, pList);

	vector<PointStruct> pListLeft, pListRight;
	for (int i = 0; i < pList.size(); i++) {
		if (medianP.isBigger(dimension, pList[i])) {
			pListLeft.push_back(pList[i]);
		}
		else if (medianP.isSmaller(dimension, pList[i])) {
			pListRight.push_back(pList[i]);
		}
		else if (!medianP.isEqual(pList[i])) {
			pListRight.push_back(pList[i]);
		}
	}

	TreeNode* pTreeNode = new TreeNode(medianP);
	pTreeNode->m_pLeftChild = buildTree(pListLeft, d + 1);
	pTreeNode->m_pRightChild = buildTree(pListRight, d + 1);
	pTreeNode->m_dimension = dimension;
	return pTreeNode;
}
void recurSearch(TreeNode* pNode, int depth, const Coordinate& point, PointStruct& nearest) {
	if (!pNode) return;
	int dimension = depth % 2;
	if (point.distance(*pNode) < point.distance(nearest)) {
		nearest = *pNode;
	}
	if (point.isSmaller(dimension, *pNode)) {
		recurSearch(pNode->m_pLeftChild, depth + 1, point, nearest);
		if (point.distance(nearest) >= point.distance(dimension, *pNode)) {
			recurSearch(pNode->m_pRightChild, depth + 1, point, nearest);
		}
	}
	else {
		recurSearch(pNode->m_pRightChild, depth + 1, point, nearest);
		if (point.distance(nearest) >= point.distance(dimension, *pNode)) {
			recurSearch(pNode->m_pLeftChild, depth + 1, point, nearest);
		}
	}
}

int main() {
	int N, M;
	cin >> N >> M;

	vector<PointStruct> points;
	PointStruct tempP;
	while (N--) {
		cin >> tempP.m_coor[0] >> tempP.m_coor[1] >> tempP.m_data;
		points.push_back(tempP);
	}

	TreeNode* root = buildTree(points, 0);
	Coordinate tempC;
	PointStruct result;

	while (M--) {
		cin >> tempC.m_coor[0] >> tempC.m_coor[1];
		recurSearch(root, 0, tempC, result);
		printf("%.4f\n", tempC.distance(result));
	}
	return 0;
}
