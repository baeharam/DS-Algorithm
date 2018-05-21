#include "Graph.c"

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

// ����-���� �˰������� �̿��ؼ� �� vertex�� shortest path ���ϱ�
bool BellmanFord(Graph *g, int s)
{
	Init_SS(g, s);
	for (int i = 1; i < g->vertexNum; i++) {
		for (int j = 1; j <= g->vertexNum; j++) {
			Vertex *cur = g->adj[j]->next;
			while (cur) {
				Relax(g, j, cur->v, cur->w);
				cur = cur->next;
			}
		}
	}
	for (int j = 1; j <= g->vertexNum; j++) {
		Vertex *cur = g->adj[j]->next;
		while (cur) {
			Relax(g, j, cur->v, cur->w);
			cur = cur->next;
		}
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

int main(void)
{
	Graph *g = CreateGraph();
	int s = 1;
	BellmanFord(g, s);
	for (int i = 1; i <= g->vertexNum; i++) {
		printf("vertex %d : �ִܰ��(%d), ", i, g->adj[i]->distance);
		printf("���������� ���(");
		PrintPath(g, s, i);
		printf(")\n");
	}

	Deallocation(g);

	return 0;
}