#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
// vertex는 A(0)부터 시작한다.
enum { A, B, C, D, E, F, G, H, I, J, K };
const int max = 2100000000;
typedef enum { false, true } bool;

// Vertex는 정점의 번호(혹은 알파벳)와 다음 정점으로의 포인터변수 next를 가진다.
typedef struct Vertex {
	int v;
	int distance;
	int parent;
	int w;
	struct Vertex* next;
}Vertex;

// Graph는 vertex의 숫자와 인접리스트를 갖는다.
typedef struct Graph {
	int vertexNum;
	int edgeNum;
	Vertex** adj;
}Graph;

// Edge는 연결하는 두 vertex와 weight을 갖는다.
typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;

#endif