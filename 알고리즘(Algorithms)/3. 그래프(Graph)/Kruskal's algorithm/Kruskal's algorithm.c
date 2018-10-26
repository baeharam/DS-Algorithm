#include <stdio.h>
#include <stdlib.h>

// vertex는 A(0)부터 시작한다.
enum { A, B, C, D, E, F, G, H, I, J, K };

// Edge는 2개의 정점과 weight을 가진다.
typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;

// Vertex는 정점의 번호(혹은 알파벳)와 다음 정점으로의 포인터변수 next를 가진다.
typedef struct Vertex {
	int v;
	struct Vertex* next;
}Vertex;

// Graph는 vertex의 숫자와 edge의 숫자, 인접리스트, edge의 배열을 갖는다.
typedef struct Graph {
	int vertexNum;
	int edgeNum;
	Vertex** adj;
	Edge* edgeList;
}Graph;

// vertex를 동적할당하여 리턴한다.
Vertex* CreateVertex(int v)
{
	Vertex *create = (Vertex*)malloc(sizeof(Vertex));
	create->v = v;
	create->next = NULL;
	return create;
}

Vertex** CreateAdj(int vertexNum)
{
	Vertex **adj = (Vertex**)malloc(sizeof(Vertex*)*(vertexNum + 1));
	for (int i = 1; i <= vertexNum; i++)
		adj[i] = CreateVertex(i);
	return adj;
}

Edge* CreateEdgeList(int edgeNum)
{
	Edge* edgeList = (Edge*)malloc(sizeof(Edge)*edgeNum);
	for (int i = 0; i < edgeNum; i++) {
		edgeList[i].v1 = 0;
		edgeList[i].v2 = 0;
		edgeList[i].weight = 0;
	}
	return edgeList;
}

// vertex를 연결하여 인접리스트를 만든다.
void ConnectVertex(Vertex** adj, int v1, int v2)
{
	Vertex* current = adj[v1];
	if (current == NULL) current = CreateVertex(v1);
	else {
		while (current->next != NULL) current = current->next;
		current->next = CreateVertex(v2);
	}
	current = adj[v2];
	if (current == NULL) current = CreateVertex(v2);
	else {
		while (current->next != NULL) current = current->next;
		current->next = CreateVertex(v1);
	}
}

// qsort를 쓸 때 weight 기준 오름차순 정렬하기 위한 비교함수
int cmp(const void* p1, const void* p2)
{
	Edge* e1 = (Edge*)p1;
	Edge* e2 = (Edge*)p2;
	return e1->weight - e2->weight;
}

// Graph를 만든다.
Graph* CreateGraph()
{
	Graph *g = (Graph*)malloc(sizeof(Graph));
	int v, e;
	scanf("%d %d", &v, &e);

	// vertex, edge의 개수 설정하고 인접 리스트, edge 배열 동적할당
	g->vertexNum = v; g->edgeNum = e;
	g->adj = CreateAdj(v);
	g->edgeList = CreateEdgeList(e);

	// 연결되는 정점과 weight을 입력하면서 다음을 진행한다.
	// 1. 인접리스트로 vertex와 vertex를 연결한다.
	// 2. edge 배열로 각 edge들을 edgeList에 넣는다.
	int v1, v2, w;
	for (int i = 0; i < e; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		ConnectVertex(g->adj, v1, v2);
		g->edgeList[i].v1 = v1; g->edgeList[i].v2 = v2;
		g->edgeList[i].weight = w;
	}

	qsort(g->edgeList, e, sizeof(Edge), cmp);

	return g;
}

// DisjointSet은 Union과 Find를 하기 위한 자료구조이다.
typedef struct DisjointSet {
	int parent;
	int rank;
}DisjointSet;

// DisjointSet을 동적할당하여 초기화한다.
DisjointSet* MakeSet(int vertexNum)
{
	DisjointSet* set = (DisjointSet*)malloc(sizeof(DisjointSet)*(vertexNum + 1));
	for (int i = 1; i <= vertexNum; i++) {
		set[i].parent = i;
		set[i].rank = 0;
	}

	return set;
}

int Find(DisjointSet *set, int v)
{
	if (v == set[v].parent) return v;
	else return Find(set, set[v].parent);
}

// 동적할당한 모든 배열의 메모리를 반환해주어야 한다.
// Graph, Edge, DisjointSet, Vertex
void Deallocation(Graph *g, Edge *MST, DisjointSet *set)
{
	for (int i = 1; i <= g->vertexNum; i++)
		free(g->adj[i]);
	free(g->adj);

	free(g->edgeList);
	free(MST);
	free(set);
}

int main(void)
{
	Graph *g = CreateGraph();
	Edge *MST = CreateEdgeList(g->edgeNum);
	DisjointSet *set = MakeSet(g->vertexNum);

	for (int i = 0; i < g->edgeNum; i++) {
		int u = g->edgeList[i].v1, v = g->edgeList[i].v2;
		int find_u = Find(set, u), find_v = Find(set, v);
		if (find_u!=find_v) {
			MST[i] = g->edgeList[i];
			set[find_u].parent = find_v;
		}
	}

	/*
	for (int i = 0; i < g->edgeNum; i++) {
		if (MST[i].weight != 0) {
			printf("%d와 %d를 연결 : %d\n", MST[i].v1, MST[i].v2, MST[i].weight);
		}
	}*/

	int sum = 0;
	for (int i = 0; i < g->edgeNum; i++) sum += MST[i].weight;
	printf("%d\n", sum);

	Deallocation(g, MST, set);

	return 0;
}