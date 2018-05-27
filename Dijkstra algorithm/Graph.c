#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

const int max = 2100000000;

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

// ���Ϸκ��� �׷����� �б� ���� ù��° ���� ���ְ� vertex�� ���� ����ϴ� �Լ�
// ������ġ�� ���������͸� �����Ѵ�.
FILE* ReadGraph(int *vertexNum)
{
	FILE *fp = fopen("hw5.data", "r");
	if (fp == NULL) {
		printf("There is no file");
		return fp;
	}

	char c = '\0';
	// �� ���� �о���δ�.
	while ((c = fgetc(fp)) != '\n') {
		// ���ĺ��� ��� vertexNum�� 1������Ų�� ������ ���ĺ��� �д´�.
		if (c >= 65 && c <= 90) {
			(*vertexNum)++;
			while ((c = fgetc(fp))) {
				if (c >= 65 && c <= 90) continue;
				else break;
			}
		}
	}
	return fp;
}

// Graph�� �����.
Graph* CreateGraph()
{
	Graph *g = (Graph*)malloc(sizeof(Graph));
	int v = 0;

	FILE *fp = ReadGraph(&v);

	// vertex�� ���� �ʱ�ȭ, ��������Ʈ �ʱ�ȭ
	g->vertexNum = v;
	g->adj = CreateAdj(v);
	g->edgeNum = 0;
	g->vertexName= (char**)malloc(sizeof(char*)*(g->vertexNum + 1));
	for (int i = 1; i <= g->vertexNum; i++) g->vertexName[i] = (char*)malloc(sizeof(char) * 255);

	int v1 = 1, v2 = 1;
	char c = '\0';
	char vertex[255] = { NULL };

	// ������ ���� �ƴϰ� vertex�� �� ���� �ʾ�����
	while (!feof(fp) && v1<=g->vertexNum) {
		fscanf(fp, "%s", g->vertexName[v1]);
		for (int i = 1; i <= g->vertexNum; i++) {
			fscanf(fp, "%s", vertex);
			if (vertex[0] == '0') v2++; // �ڱ� �ڽŰ� ���� �Ұ�
			else if (vertex[0] == 'I') v2++; // ������ �ȵǾ���, weight�� ���Ѵ��� ���
			else { // ������ �Ǿ� �ִ� ���, ���ڿ��� ������ �ٲ۴�.
				g->edgeNum++;
				int weight = (int)(strtol(vertex, NULL, 10));
				ConnectVertex(g->adj, v1, v2, weight);
			}
		}
		v1++;
		v2 = 1;
	}

	return g;
}

// �޸� ����
void Deallocation(Graph *g)
{
	for (int i = 1; i <= g->vertexNum; i++) {
		free(g->adj[i]);
		free(g->vertexName[i]);
	}
	free(g->adj);
	free(g->vertexName);
	free(g);
}