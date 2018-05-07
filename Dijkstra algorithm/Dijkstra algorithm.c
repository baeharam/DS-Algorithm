#include "Priority queue.c"

// distance, parent의 초기화 작업
void Init_SS(Graph *g, int s)
{
	for (int i = 1; i <= g->vertexNum; i++) {
		g->adj[i]->distance = max;
		g->adj[i]->parent = NULL;
	}
	g->adj[s]->distance = 0;
}

// Relaxation 작업, distance와 parent(predecessor)를 결정한다.
void Relax(Graph *g, int u, int v, int w)
{
	if (g->adj[v]->distance > g->adj[u]->distance + w) {
		g->adj[v]->distance = g->adj[u]->distance + w;
		g->adj[v]->parent = u;
	}
}

void Dijkstra(Graph *g, int s)
{
	Init_SS(g, s);
	int *vertexList = (int*)malloc(sizeof(int)*(g->vertexNum+1));
	Heap *minHeap = CreateHeap(g->vertexNum);

	for (int i = 1; i <= g->vertexNum; i++) Insert(minHeap, g, g->adj[i]);

	int i = 1;
	while (minHeap->currentSize) {
		int u = extractMin(minHeap, g);
		vertexList[i++] = u;
		Vertex* cur = g->adj[u]->next;
		while (cur) {
			Relax(g, u, cur->v, cur->w);
			cur = cur->next;
		}
	}

	free(minHeap->heapTree);
	free(minHeap);
}

void PrintPath(Graph *g, int s, int v)
{
	int *path = (int*)malloc(sizeof(int)*g->vertexNum);
	Vertex *cur = g->adj[v];
	path[0] = v;

	int i = 1;
	while (cur->parent) {
		path[i] = cur->parent;
		cur = g->adj[cur->parent];
		i++;
	}

	for (int j = i - 1; j >= 0; j--) {
		printf("%d", path[j]);
		if (j != 0) printf("→");
	}

	free(path);
}

int main(void)
{
	Graph *g = CreateGraph();
	int s = 1;
	Dijkstra(g, s);
	for (int i = 1; i <= g->vertexNum; i++) {
		printf("vertex %d : 최단경로(%d), ", i, g->adj[i]->distance);
		printf("이제까지의 경로(");
		PrintPath(g, s, i);
		printf(")\n");
	}

	Deallocation(g);

	return 0;
}