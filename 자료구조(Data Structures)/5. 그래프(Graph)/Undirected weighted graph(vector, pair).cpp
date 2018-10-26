#include <iostream>
#include <vector>

std::vector<std::pair<int,int>> graph[100];

int main(void)
{
	int vertex, edge;
	std::cin >> vertex >> edge;

	int v1, v2, weight; // 가중치포함

	while (edge--){
		std::cin >> v1 >> v2 >> weight;
		// 정점을 push_back하고 가중치도 push_back
		graph[v1].push_back(std::make_pair(v2, weight));
		graph[v2].push_back(std::make_pair(v1, weight));
	}

	for (int i = 1; i <= vertex; i++){
		std::cout << i << "에 연결 : ";
		for (int j = 0; j < graph[i].size(); j++){
			std::cout << graph[i][j].first << " ,";
			std::cout << "가중치 -> " << graph[i][j].second << " | ";
		}
		std::cout << '\n';
	}

	return 0;
}