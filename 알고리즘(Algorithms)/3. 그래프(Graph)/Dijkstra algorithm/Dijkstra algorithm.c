#include <stdio.h>
#include <stdlib.h>
#include "Priority queue.c"

// distance, parent의 초기화 작업
void Init_SS(Graph *g, int s)
{
	for (int i = 1; i <= g->vertexNum; i++) {
		g->adj[i]->distance = max;
		g->adj[i]->parent = 0;
	}
	g->adj[s]->distance = 0;
}

// Relaxation 작업, distance와 parent(predecessor)를 결정한다.
// 만약 relax를 해주는 경우라면 우선순위 큐에 넣는다.
void Relax(Graph *g, int u, Heap *heap, Vertex *cur)
{
	int v = cur->v;
	int w = cur->w;

	if (g->adj[v]->distance > g->adj[u]->distance + w) {
		g->adj[v]->distance = g->adj[u]->distance + w;
		g->adj[v]->parent = u;
		Insert(heap, g, cur);
	}
}

// 다익스트라 알고리즘
void Dijkstra(Graph *g, int s)
{
	// source를 제외한 distance를 무한대로, predecessor를 NIL로 초기화시키는 과정
	Init_SS(g, s);

	// 우선순위 큐, minHeap의 할당
	Heap *minHeap = CreateHeap(g->vertexNum*g->vertexNum);

	// minHeap에 source vertex만 넣는다.
	Insert(minHeap, g, g->adj[s]);


	int i = 1;
	// 우선순위 큐의 크기만큼 반복
	while (minHeap->currentSize) {
		// 제일 distance가 작은 vertex를 빼서 vertexList에 넣는다.
		int u = extractMin(minHeap, g);
		Vertex* cur = g->adj[u]->next;
		// 그 vertex에 인접한 vertex들에 대하여 relax를 한다.
		while (cur) {
			Relax(g, u, minHeap, cur);
			cur = cur->next;
		}
	}

	// minHeap, minHeap 안에 있는 tree에 대한 메모리 해제
	free(minHeap->heapTree);
	free(minHeap);
}

// parent를 계속 역으로 추적하면서 각 vertex의 shortest path를 구하는 함수
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