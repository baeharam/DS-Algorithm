#include <iostream>

int graph[21][21]; // 최대 정점의 개수=20개

int main(void)
{
	int vertex; // 정점의 수
	int edge; // 간선의 수

	int v1, v2; // 연결될 정점

	std::cin >> vertex >> edge; // 정점/간선의 수 입력

	for (int i = 0; i<edge; i++){
		std::cin >> v1 >> v2; // 연결될 정점 입력
		graph[v1][v2] = 1; // 방향그래프이므로 정해진 방향만 활성화
	}

	for (int i = 0; i <= vertex; i++){
		for (int j = 0; j <= vertex; j++)
			std::cout << graph[i][j] << ' ';
		std::cout << '\n';
	}
	return 0;
}