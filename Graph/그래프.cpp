#include <iostream>
#include <vector>

// ������/���� ����
enum{ UNDIRECTED = 1, DIRECTED = 2 };
// Ÿ���� �ʹ� �� VECTOR�� ������
typedef std::vector<std::vector<std::pair<int, int>>> VECTOR;

class Graph{
private:
	VECTOR vertex; // �׷����� ��Ÿ���� 2���� ����
	std::vector<int> vertexName; // ����ڰ� �ִ� vertex�̸� ����
	int type; // �����ΰ� �������ΰ�
	int real_v1; // ���� ����ڰ� �Է��� ���� v1
	int real_v2; // ���� ����ڰ� �Է��� ���� v2

public:
	Graph(int whatTypeis); // ������/���� Ÿ���� ���ڷ� �޴´�.
	void InsertVertex(int v); // ���� �߰�
	void InsertEdge(int v1, int v2, int weight); // ���� �߰�
	void RemoveEdge(int v1, int v2); // ���� ����
	void RemoveVertex(int v); // ���� ����
	bool isAdjacent(int v1, int v2) const; // ������ �������ִ°�?
	int getDegree(int v) const; // ���� ��ȯ
	void DrawGraph() const; // �׷��� �׸���
};

// ����׷������� ������׷������� Ÿ���� ���ڷ� �޴´�.
// vertex�� ������ ���ڷ� �޴´�.
// ������ �迭�� ���� �Ҵ��Ѵ�.
Graph::Graph(int whatTypeis) :type(whatTypeis)
{
	vertexName.push_back(0); // dummy
	std::vector<std::pair<int, int>> dummy;
	vertex.push_back(dummy);
}

// vertex�� �����ϴ� �Լ�
void Graph::InsertVertex(int v)
{
	std::vector<std::pair<int, int>> temp;
	vertex.push_back(temp);
	vertexName.push_back(v);
}

// �⺻ ����ġ�� 0�̰� �־����� ����ġ�� �����Ѵ�.
void Graph::InsertEdge(int v1, int v2, int weight = 0)
{
	// pair�� �Ѱ��� v1,v2�� �����س��´�.
	real_v1 = v1;
	real_v2 = v2;

	// vertexName�� �� ���� �ε����� vertex�� ����ϱ� ������
	// �ű⼭ v1�� v2�� �ε����� ã�Ƴ���.
	for (int i = 1; i < vertexName.size(); i++){
		if (vertexName[i] == v1) v1 = i;
		else if (vertexName[i] == v2) v2 = i;
	}

	// ����/���������� ������ ���� pair�� �������ִ� ������
	// real_v1, real_v2�̴�.
	if (type == UNDIRECTED){
		vertex[v1].push_back(std::make_pair(real_v2, weight));
		vertex[v2].push_back(std::make_pair(real_v1, weight));
	}
	else if (type == DIRECTED)
		vertex[v1].push_back(std::make_pair(real_v2, weight));
}


// ������ �����Ѵ�.
// ������ : ���� ����, ���� : �� ���⸸ ����
void Graph::RemoveEdge(int v1, int v2)
{
	// ����� v1,v2�� �����س��´�.
	real_v1 = v1;
	real_v2 = v2;

	// vertexName�� �� ���� �ε����� vertex�� ����ϱ� ������
	// �ű⼭ v1�� v2�� �ε����� ã�Ƴ���.
	for (int i = 1; i < vertexName.size(); i++){
		if (vertexName[i] == v1) v1 = i;
		else if (vertexName[i] == v2) v2 = i;
	}

	int i, j;
	// v1�� v2�� ����ִ��� ������ �ε��� �˾Ƴ��� �۾�
	for (i = 0; vertex[v1].size(); i++){
		if (vertex[v1][i].first == real_v2)
			break;
	}
	for (j = 0; vertex[v2].size(); j++){
		if (vertex[v2][j].first == real_v1)
			break;
	}

	// ������ �׷����� ���� �����ؾ��Ѵ�.
	if (type == UNDIRECTED){
		vertex[v1].erase(vertex[v1].begin() + i);
		vertex[v2].erase(vertex[v2].begin() + j);
	}
	// ���� �׷����� �־��� ���⸸ �����Ѵ�.
	else if (type == DIRECTED)
		vertex[v1].erase(vertex[v1].begin() + i);

	std::cout << "------------------------------------------" << '\n';
	std::cout << real_v1 << "�� " << real_v2 << "�� ������ ���������ϴ�." << '\n';
	std::cout << "------------------------------------------" << '\n';
}

// ������ �����Ѵ�.
// ���� ������ ����� ��� ������ �����Ѵ�.
void Graph::RemoveVertex(int v)
{
	std::cout << "------------------------------------------" << '\n';
	std::cout << "���� "<<v<<"�� �����˴ϴ�..." << '\n';
	std::cout << "------------------------------------------" << '\n';

	// ���� ����ڰ� �Է��� �� ����
	real_v1 = v;

	for (int i = 1; i < vertexName.size(); i++){
		if (vertexName[i] == v) v = i;
	}

	// ���Ϳ��� �ϳ��� �������� ��ĭ�� ������ ������� ������
	// �ε��� 0�� ��� �����ָ� �ȴ�.
	while (vertex[v].size())
		RemoveEdge(real_v1, vertex[v][0].first);
}

// �� ������ ���� �پ��ִ��� �˷��ִ� �Լ�
bool Graph::isAdjacent(int v1, int v2) const
{
	for (int i = 0; i < vertex[v1].size(); i++){
		if (vertex[v1][i].first == v2){
			std::cout << "------------------------------------------" << '\n';
			std::cout << "�� ���� "<<v1<<"�� "<<v2<<"�� �������ֽ��ϴ�." << '\n';
			std::cout << "------------------------------------------" << '\n';
			return true;
		}
	}
	std::cout << "------------------------------------------" << '\n';
	std::cout << "�� ���� " << v1 << "�� " << v2 << "�� ���������� �ʽ��ϴ�." << '\n';
	std::cout << "------------------------------------------" << '\n';
	return false;
}

// ������ ����� ������ ������ �˷��ִ� �Լ� (����)
int Graph::getDegree(int v) const
{
	std::cout << "------------------------------------------" << '\n';
	std::cout << "���� "<<v<<"�� ����� ������ ���� " << vertex[v].size()<<"�� �Դϴ�."<< '\n';
	std::cout << "------------------------------------------" << '\n';
	return vertex[v].size();
}

// �׷����� �����ִ� �Լ�
void Graph::DrawGraph() const
{
	if (type == DIRECTED) std::cout << "���� �׷���" << '\n';
	else std::cout << "������ �׷���" << '\n';

	for (int i = 1; i < vertex.size(); i++){
		if (vertex[i].size()) std::cout << vertexName[i] << " �� ";
		for (int j = 0; j < vertex[i].size(); j++){
			if ((j + 1) % 4 == 0) std::cout << "\n     ";
			std::cout << vertex[i][j].first << ", ";
			if (vertex[i][j].second != 0)
				std::cout << "����ġ (" << vertex[i][j].second << ") | ";
		}
		std::cout << '\n';
	}
	std::cout << "------------------------------------------" << '\n';
}


int main(void)
{
	Graph g(UNDIRECTED);

	for (int i = 1; i <= 8; i++)
		g.InsertVertex(i);

	g.InsertEdge(1, 2,3);
	g.InsertEdge(1, 3,2);
	g.InsertEdge(2, 4,5);
	g.InsertEdge(2, 5,6);
	g.InsertEdge(4, 8,3);
	g.InsertEdge(5, 8,1);
	g.InsertEdge(3, 6,2);
	g.InsertEdge(3, 7,3);
	g.InsertEdge(6, 8,4);
	g.InsertEdge(7, 8,9);

	g.DrawGraph();

	g.RemoveEdge(1, 3);

	g.DrawGraph();

	g.RemoveVertex(4);


	return 0;
}

