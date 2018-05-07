#include "Graph.h"

// vertex를 동적할당하여 리턴한다.
Vertex* CreateVertex(int v)
{
	Vertex *create = (Vertex*)malloc(sizeof(Vertex));
	create->v = v;
	create->next = NULL;
	create->w = 0;
	return create;
}

// 인접리스트를 할당한다.
Vertex** CreateAdj(int vertexNum)
{
	Vertex **adj = (Vertex**)malloc(sizeof(Vertex*)*(vertexNum + 1));
	for (int i = 1; i <= vertexNum; i++)
		adj[i] = CreateVertex(i);
	return adj;
}

// vertex를 연결하여 인접리스트를 만든다.
void ConnectVertex(Vertex** adj, int v1, int v2, int w)
{
	Vertex* current = adj[v1];
	if (current == NULL) current = CreateVertex(v1);
	else {
		while (current->next != NULL) current = current->next;
		current->next = CreateVertex(v2);
		current->next->w = w;
	}
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

	// 연결되는 정점과 weight을 입력하면서 다음을 진행한다.
	// 인접리스트로 vertex와 vertex를 연결한다.
	int v1, v2, w;
	for (int i = 0; i < e; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		ConnectVertex(g->adj, v1, v2, w);
	}

	return g;
}

// 메모리 해제
void Deallocation(Graph *g)
{
	for (int i = 1; i <= g->vertexNum; i++) free(g->adj[i]);
	free(g->adj);
	free(g);
}