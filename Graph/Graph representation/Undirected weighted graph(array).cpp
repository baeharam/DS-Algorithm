#include <iostream>

int graph[21][21]; // 최대 정점의 개수=20개

int main(void)
{
	int vertex; // 정점의 수
	int edge; // 간선의 수

	int v1, v2; // 연결될 정점
	int weight; // 가중치

	std::cin >> vertex >> edge; // 정점/간선의 수 입력

	for (int i = 0; i<edge; i++){
		// 연결될 정점과 가중치 입력
		std::cin >> v1 >> v2 >> weight; 
		graph[v1][v2] = weight;
		graph[v2][v1] = weight;
	}

	for (int i = 0; i <= vertex; i++){
		for (int j = 0; j <= vertex; j++)
			std::cout << graph[i][j] << ' ';
		std::cout << '\n';
	}
	return 0;
}