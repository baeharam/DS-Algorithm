#include <stdio.h>

// vertex�� A(0)���� �����Ѵ�.
enum { A, B, C, D, E, F, G, H, I, J, K };
const int max = 2100000000;
typedef enum { false, true } bool;

// Edge�� 2���� ������ weight�� ������.
typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;

// Vertex�� ������ ��ȣ(Ȥ�� ���ĺ�)�� ���� ���������� �����ͺ��� next�� ������.
typedef struct Vertex {
	int v;
	int distance;
	int parent;
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

	return g;
}

// distance, parent�� �ʱ�ȭ �۾�
void Init_SS(Graph *g, int s)
{
	for (int i = 1; i <= g->vertexNum; i++) {
		g->adj[i]->distance = max;
		g->adj[i]->parent = NULL;
	}
	g->adj[s]->distance = 0;
}

// Relaxation �۾�
void Relax(Graph *g, int u, int v, int w)
{
	if (g->adj[v]->distance > g->adj[u]->distance + w) {
		g->adj[v]->distance = g->adj[u]->distance + w;
		g->adj[v]->parent = u;
	}
}

// ����-���� �˰����� �̿��ؼ� �� vertex�� shortest path ���ϱ�
bool BellmanFord(Graph *g, int s)
{
	Init_SS(g, s);
	for (int i = 1; i < g->vertexNum; i++) {
		for (int j = 0; j < g->edgeNum; j++)
			Relax(g, g->edgeList[j].v1, g->edgeList[j].v2, g->edgeList[j].weight);
	}
	for (int i = 0; i < g->edgeNum; i++) {
		int u = g->edgeList[i].v1, v = g->edgeList[i].v2, w = g->edgeList[i].weight;
		if (g->adj[v]->distance > g->adj[u]->distance + w) return false;
	}
	return true;
}

void PrintPath(Graph *g, int s, int v)
{
	int *path = (int*)malloc(sizeof(int)*g->vertexNum);
	Vertex *cur = g->adj[v];
	path[0] = v;
	
	int i = 1;
	while(cur->parent){
		path[i] = cur->parent;
		cur = g->adj[cur->parent];
		i++;
	}
	
	for (int j = i-1; j >= 0; j--) {
		printf("%d", path[j]);
		if (j != 0) printf("��");
	}

	free(path);
}

void Deallocation(Graph *g)
{
	for (int i = 1; i <= g->vertexNum; i++) free(g->adj[i]);
	free(g->adj);
	free(g->edgeList);
	free(g);
}

int main(void)
{
	Graph *g = CreateGraph();
	int s = 2;
	BellmanFord(g, s);
	for (int i = 1; i <= g->vertexNum; i++) {
		printf("vertex %d : �ִܰ��(%d), ", i, g->adj[i]->distance);
		printf("���������� ���(");
		PrintPath(g, s, i);
		printf(")\n");
	}

	return 0;
}