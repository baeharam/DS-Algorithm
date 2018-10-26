#include "Graph.h"

// vertex�� �����Ҵ��Ͽ� �����Ѵ�.
Vertex* CreateVertex(int v)
{
	Vertex *create = (Vertex*)malloc(sizeof(Vertex));
	create->v = v;
	create->next = NULL;
	create->w = 0;
	return create;
}

// ��������Ʈ�� �Ҵ��Ѵ�.
Vertex** CreateAdj(int vertexNum)
{
	Vertex **adj = (Vertex**)malloc(sizeof(Vertex*)*(vertexNum + 1));
	for (int i = 1; i <= vertexNum; i++)
		adj[i] = CreateVertex(i);
	return adj;
}

// vertex�� �����Ͽ� ��������Ʈ�� �����.
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

// Graph�� �����.
Graph* CreateGraph()
{
	Graph *g = (Graph*)malloc(sizeof(Graph));
	int v, e;
	scanf("%d %d", &v, &e);

	// vertex, edge�� ���� �����ϰ� ���� ����Ʈ, edge �迭 �����Ҵ�
	g->vertexNum = v; g->edgeNum = e;
	g->adj = CreateAdj(v);

	// ����Ǵ� ������ weight�� �Է��ϸ鼭 ������ �����Ѵ�.
	// ��������Ʈ�� vertex�� vertex�� �����Ѵ�.
	int v1, v2, w;
	for (int i = 0; i < e; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		ConnectVertex(g->adj, v1, v2, w);
	}

	return g;
}

// �޸� ����
void Deallocation(Graph *g)
{
	for (int i = 1; i <= g->vertexNum; i++) free(g->adj[i]);
	free(g->adj);
	free(g);
}