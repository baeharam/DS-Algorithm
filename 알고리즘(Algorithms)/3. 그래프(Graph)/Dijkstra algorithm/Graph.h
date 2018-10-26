#ifndef _GRAPH_H_
#define _GRAPH_H_

const int max;

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
	char **vertexName;
	Vertex** adj;
}Graph;

// Edge�� �����ϴ� �� vertex�� weight�� ���´�.
typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;

// �Լ��� ����
Vertex* CreateVertex(int v);
Vertex** CreateAdj(int vertexNum);
void ConnectVertex(Vertex** adj, int v1, int v2, int w);
FILE* ReadGraph(int *vertexNum);
Graph* CreateGraph();
void Deallocation(Graph *g);


#endif