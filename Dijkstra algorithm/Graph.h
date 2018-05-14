#ifndef _GRAPH_H_
#define _GRAPH_H_

// vertex�� A(0)���� �����Ѵ�.
enum { A, B, C, D, E, F, G, H, I, J, K };
const int max;
typedef enum { false, true } bool;

// Vertex�� ������ ��ȣ(Ȥ�� ���ĺ�)�� ���� ���������� �����ͺ��� next�� ������.
typedef struct Vertex {
	int v;
	int distance;
	int parent;
	int w;
	struct Vertex* next;
}Vertex;

// Graph�� vertex�� ���ڿ� ��������Ʈ�� ���´�.
typedef struct Graph {
	int vertexNum;
	int edgeNum;
	Vertex** adj;
}Graph;

// Edge�� �����ϴ� �� vertex�� weight�� ���´�.
typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;

#endif