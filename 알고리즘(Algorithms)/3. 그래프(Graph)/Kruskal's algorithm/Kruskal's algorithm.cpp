#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

struct Edge {
	int v1;
	int v2;
	int w;
};

struct Disjoint {
	int parent;
	int rank;
};

bool operator<(const Edge& e1, const Edge&e2) {
	return e1.w > e2.w;
}

vector<vector<int>> graph;
vector<Edge> MST;
priority_queue<Edge> q;
Disjoint *set;

void MakeSet()
{
	for (int i = 1; i <= graph.size() - 1; i++) {
		set[i].parent = i;
		set[i].rank = 0;
	}
}

int FindSet(int u)
{
	if (set[u].parent == u) return u;
	else return FindSet(set[u].parent);
}


void Kruskal()
{
	while (!q.empty()) {
		Edge e = q.top(); q.pop();
		if (FindSet(e.v1) != FindSet(e.v2)) {
			set[e.v1].parent = e.v2;
			MST.push_back(e);
		}
	}
}

int main(void)
{
	int v, e; cin >> v >> e;
	graph.resize(v + 1);
	for (int i = 1; i <= v; i++) graph[i].resize(v + 1);
	set = new Disjoint[v + 1];
	MakeSet();

	int v1, v2, w;
	for (int i = 0; i < e; i++) {
		cin >> v1 >> v2 >> w;
		graph[v1][v2] = w;
		Edge edge = { v1,v2,w };
		q.push(edge);
	}

	Kruskal();

	for (int i = 0; i < MST.size(); i++) {
		cout << MST[i].v1 << "과 " << MST[i].v2 << "가 " << MST[i].w << "의 weight으로 연결됨!\n";
	}
	return 0;
}
