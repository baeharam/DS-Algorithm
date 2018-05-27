#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

const int max = 2100000000;

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

// 파일로부터 그래프를 읽기 위해 첫번째 줄을 없애고 vertex의 수를 계산하는 함수
// 다음위치의 파일포인터를 리턴한다.
FILE* ReadGraph(int *vertexNum)
{
	FILE *fp = fopen("hw5.data", "r");
	if (fp == NULL) {
		printf("There is no file");
		return fp;
	}

	char c = '\0';
	// 한 줄을 읽어들인다.
	while ((c = fgetc(fp)) != '\n') {
		// 알파벳일 경우 vertexNum을 1증가시킨후 나머지 알파벳을 읽는다.
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

// Graph를 만든다.
Graph* CreateGraph()
{
	Graph *g = (Graph*)malloc(sizeof(Graph));
	int v = 0;

	FILE *fp = ReadGraph(&v);

	// vertex의 개수 초기화, 인접리스트 초기화
	g->vertexNum = v;
	g->adj = CreateAdj(v);
	g->edgeNum = 0;
	g->vertexName= (char**)malloc(sizeof(char*)*(g->vertexNum + 1));
	for (int i = 1; i <= g->vertexNum; i++) g->vertexName[i] = (char*)malloc(sizeof(char) * 255);

	int v1 = 1, v2 = 1;
	char c = '\0';
	char vertex[255] = { NULL };

	// 파일의 끝이 아니고 vertex를 다 보지 않았으면
	while (!feof(fp) && v1<=g->vertexNum) {
		fscanf(fp, "%s", g->vertexName[v1]);
		for (int i = 1; i <= g->vertexNum; i++) {
			fscanf(fp, "%s", vertex);
			if (vertex[0] == '0') v2++; // 자기 자신과 연결 불가
			else if (vertex[0] == 'I') v2++; // 연결이 안되었음, weight이 무한대인 경우
			else { // 연결이 되어 있는 경우, 문자열을 정수로 바꾼다.
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

// 메모리 해제
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