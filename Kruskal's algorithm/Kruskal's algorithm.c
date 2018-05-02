#include <stdio.h>
#include <stdlib.h>

// vertex�� A(0)���� �����Ѵ�.
enum { A, B, C, D, E, F, G, H, I, J, K };

// Edge�� 2���� ������ weight�� ������.
typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;

// Vertex�� ������ ��ȣ(Ȥ�� ���ĺ�)�� ���� ���������� �����ͺ��� next�� ������.
typedef struct Vertex {
	int v;
	struct Vertex* next;
}Vertex;

// Graph�� vertex�� ���ڿ� edge�� ����, ��������Ʈ, edge�� �迭�� ���´�.
typedef struct Graph {
	int vertexNum;
	int edgeNum;
	Vertex** adj;
	Edge* edgeList;
}Graph;

// vertex�� �����Ҵ��Ͽ� �����Ѵ�.
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

// vertex�� �����Ͽ� ��������Ʈ�� �����.
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

// qsort�� �� �� weight ���� �������� �����ϱ� ���� ���Լ�
int cmp(const void* p1, const void* p2)
{
	Edge* e1 = (Edge*)p1;
	Edge* e2 = (Edge*)p2;
	return e1->weight - e2->weight;
}

// Graph�� �����.
Graph* CreateGraph()
{
	Graph *g = (Graph*)malloc(sizeof(Graph));
	int v, e;
	scanf("%d %d", &v, &e);

	// vertex, edge�� ���� �����ϰ� ���� ����Ʈ, edge �迭 �����Ҵ�
	g->vertexNum = v; g->edgeNum = e;
	g->adj = CreateAdj(v);
	g->edgeList = CreateEdgeList(e);

	// ����Ǵ� ������ weight�� �Է��ϸ鼭 ������ �����Ѵ�.
	// 1. ��������Ʈ�� vertex�� vertex�� �����Ѵ�.
	// 2. edge �迭�� �� edge���� edgeList�� �ִ´�.
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

// DisjointSet�� Union�� Find�� �ϱ� ���� �ڷᱸ���̴�.
typedef struct DisjointSet {
	int parent;
	int rank;
}DisjointSet;

// DisjointSet�� �����Ҵ��Ͽ� �ʱ�ȭ�Ѵ�.
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
			printf("%d�� %d�� ���� : %d\n", MST[i].v1, MST[i].v2, MST[i].weight);
		}
	}*/

	int sum = 0;
	for (int i = 0; i < g->edgeNum; i++) sum += MST[i].weight;
	printf("%d\n", sum);

	return 0;
}