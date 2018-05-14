#include <stdio.h>
#include <stdlib.h>
#include "Priority queue.c"

// distance, parent�� �ʱ�ȭ �۾�
void Init_SS(Graph *g, int s)
{
	for (int i = 1; i <= g->vertexNum; i++) {
		g->adj[i]->distance = max;
		g->adj[i]->parent = 0;
	}
	g->adj[s]->distance = 0;
}

// Relaxation �۾�, distance�� parent(predecessor)�� �����Ѵ�.
// ���� relax�� ���ִ� ����� �켱���� ť�� �ִ´�.
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

// ���ͽ�Ʈ�� �˰���
void Dijkstra(Graph *g, int s)
{
	// source�� ������ distance�� ���Ѵ��, predecessor�� NIL�� �ʱ�ȭ��Ű�� ����
	Init_SS(g, s);

	// �켱���� ť, minHeap�� �Ҵ�
	Heap *minHeap = CreateHeap(g->vertexNum*g->vertexNum);

	// minHeap�� source vertex�� �ִ´�.
	Insert(minHeap, g, g->adj[s]);


	int i = 1;
	// �켱���� ť�� ũ�⸸ŭ �ݺ�
	while (minHeap->currentSize) {
		// ���� distance�� ���� vertex�� ���� vertexList�� �ִ´�.
		int u = extractMin(minHeap, g);
		Vertex* cur = g->adj[u]->next;
		// �� vertex�� ������ vertex�鿡 ���Ͽ� relax�� �Ѵ�.
		while (cur) {
			Relax(g, u, minHeap, cur);
			cur = cur->next;
		}
	}

	// minHeap, minHeap �ȿ� �ִ� tree�� ���� �޸� ����
	free(minHeap->heapTree);
	free(minHeap);
}

// parent�� ��� ������ �����ϸ鼭 �� vertex�� shortest path�� ���ϴ� �Լ�
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
		if (j != 0) printf("��");
	}

	free(path);
}

int main(void)
{
	Graph *g = CreateGraph();
	int s = 1;
	Dijkstra(g, s);
	for (int i = 1; i <= g->vertexNum; i++) {
		printf("vertex %d : �ִܰ��(%d), ", i, g->adj[i]->distance);
		printf("���������� ���(");
		PrintPath(g, s, i);
		printf(")\n");
	}

	Deallocation(g);

	return 0;
}