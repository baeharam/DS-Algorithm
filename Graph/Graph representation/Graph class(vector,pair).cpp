#include <iostream>
#include <vector>

// 무방향/방향 구분
enum{ UNDIRECTED = 1, DIRECTED = 2 };
// 타입이 너무 길어서 VECTOR로 재정의
typedef std::vector<std::vector<std::pair<int, int>>> VECTOR;

class Graph{
private:
	VECTOR vertex; // 그래프를 나타내는 2차원 벡터
	std::vector<int> vertexName; // 사용자가 주는 vertex이름 벡터
	int type; // 방향인가 무방향인가
	int real_v1; // 실제 사용자가 입력한 정점 v1
	int real_v2; // 실제 사용자가 입력한 정점 v2

public:
	Graph(int whatTypeis); // 무방향/방향 타입을 인자로 받는다.
	void InsertVertex(int v); // 정점 추가
	void InsertEdge(int v1, int v2, int weight); // 간선 추가
	void RemoveEdge(int v1, int v2); // 간선 제거
	void RemoveVertex(int v); // 정점 제거
	bool isAdjacent(int v1, int v2) const; // 정점이 인접해있는가?
	int getDegree(int v) const; // 차수 반환
	void DrawGraph() const; // 그래프 그리기
};

// 방향그래프인지 무방향그래프인지 타입을 인자로 받는다.
// vertex의 개수도 인자로 받는다.
// 벡터의 배열을 동적 할당한다.
Graph::Graph(int whatTypeis) :type(whatTypeis)
{
	vertexName.push_back(0); // dummy
	std::vector<std::pair<int, int>> dummy;
	vertex.push_back(dummy);
}

// vertex를 삽입하는 함수
void Graph::InsertVertex(int v)
{
	std::vector<std::pair<int, int>> temp;
	vertex.push_back(temp);
	vertexName.push_back(v);
}

// 기본 가중치는 0이고 주어지면 가중치를 적용한다.
void Graph::InsertEdge(int v1, int v2, int weight = 0)
{
	// pair에 넘겨질 v1,v2를 저장해놓는다.
	real_v1 = v1;
	real_v2 = v2;

	// vertexName에 들어간 값의 인덱스를 vertex가 사용하기 때문에
	// 거기서 v1과 v2의 인덱스를 찾아낸다.
	for (int i = 1; i < vertexName.size(); i++){
		if (vertexName[i] == v1) v1 = i;
		else if (vertexName[i] == v2) v2 = i;
	}

	// 방향/무방향으로 나누며 실제 pair에 전달해주는 정점은
	// real_v1, real_v2이다.
	if (type == UNDIRECTED){
		vertex[v1].push_back(std::make_pair(real_v2, weight));
		vertex[v2].push_back(std::make_pair(real_v1, weight));
	}
	else if (type == DIRECTED)
		vertex[v1].push_back(std::make_pair(real_v2, weight));
}


// 간선을 삭제한다.
// 무방향 : 서로 삭제, 방향 : 한 방향만 삭제
void Graph::RemoveEdge(int v1, int v2)
{
	// 출력할 v1,v2를 저장해놓는다.
	real_v1 = v1;
	real_v2 = v2;

	// vertexName에 들어간 값의 인덱스를 vertex가 사용하기 때문에
	// 거기서 v1과 v2의 인덱스를 찾아낸다.
	for (int i = 1; i < vertexName.size(); i++){
		if (vertexName[i] == v1) v1 = i;
		else if (vertexName[i] == v2) v2 = i;
	}

	int i, j;
	// v1과 v2가 어디있는지 벡터의 인덱스 알아내는 작업
	for (i = 0; vertex[v1].size(); i++){
		if (vertex[v1][i].first == real_v2)
			break;
	}
	for (j = 0; vertex[v2].size(); j++){
		if (vertex[v2][j].first == real_v1)
			break;
	}

	// 무방향 그래프면 서로 삭제해야한다.
	if (type == UNDIRECTED){
		vertex[v1].erase(vertex[v1].begin() + i);
		vertex[v2].erase(vertex[v2].begin() + j);
	}
	// 방향 그래프면 주어진 방향만 삭제한다.
	else if (type == DIRECTED)
		vertex[v1].erase(vertex[v1].begin() + i);

	std::cout << "------------------------------------------" << '\n';
	std::cout << real_v1 << "과 " << real_v2 << "의 연결이 끊어졌습니다." << '\n';
	std::cout << "------------------------------------------" << '\n';
}

// 정점을 삭제한다.
// 따라서 정점에 연결된 모든 간선을 삭제한다.
void Graph::RemoveVertex(int v)
{
	std::cout << "------------------------------------------" << '\n';
	std::cout << "정점 "<<v<<"가 삭제됩니다..." << '\n';
	std::cout << "------------------------------------------" << '\n';

	// 실제 사용자가 입력한 값 저장
	real_v1 = v;

	for (int i = 1; i < vertexName.size(); i++){
		if (vertexName[i] == v) v = i;
	}

	// 벡터에서 하나가 지워지면 한칸씩 앞으로 당겨지기 때문에
	// 인덱스 0만 계속 지워주면 된다.
	while (vertex[v].size())
		RemoveEdge(real_v1, vertex[v][0].first);
}

// 두 정점이 서로 붙어있는지 알려주는 함수
bool Graph::isAdjacent(int v1, int v2) const
{
	for (int i = 0; i < vertex[v1].size(); i++){
		if (vertex[v1][i].first == v2){
			std::cout << "------------------------------------------" << '\n';
			std::cout << "두 정점 "<<v1<<"과 "<<v2<<"는 인접해있습니다." << '\n';
			std::cout << "------------------------------------------" << '\n';
			return true;
		}
	}
	std::cout << "------------------------------------------" << '\n';
	std::cout << "두 정점 " << v1 << "과 " << v2 << "는 인접해있지 않습니다." << '\n';
	std::cout << "------------------------------------------" << '\n';
	return false;
}

// 정점에 연결된 간선의 개수를 알려주는 함수 (차수)
int Graph::getDegree(int v) const
{
	std::cout << "------------------------------------------" << '\n';
	std::cout << "정점 "<<v<<"에 연결된 간선의 수는 " << vertex[v].size()<<"개 입니다."<< '\n';
	std::cout << "------------------------------------------" << '\n';
	return vertex[v].size();
}

// 그래프를 보여주는 함수
void Graph::DrawGraph() const
{
	if (type == DIRECTED) std::cout << "방향 그래프" << '\n';
	else std::cout << "무방향 그래프" << '\n';

	for (int i = 1; i < vertex.size(); i++){
		if (vertex[i].size()) std::cout << vertexName[i] << " → ";
		for (int j = 0; j < vertex[i].size(); j++){
			if ((j + 1) % 4 == 0) std::cout << "\n     ";
			std::cout << vertex[i][j].first << ", ";
			if (vertex[i][j].second != 0)
				std::cout << "가중치 (" << vertex[i][j].second << ") | ";
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

