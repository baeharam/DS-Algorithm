#include <iostream>
#include <vector>

std::vector<int> graph[100];

int main(void)
{
	int vertex, edge;
	std::cin >> vertex >> edge;

	int v1, v2, weight; // 가중치포함

	while (edge--){
		std::cin >> v1 >> v2 >> weight;
		// 정점을 push_back하고 가중치도 push_back
		// 짝수번째 : 정점, 홀수번째 : 가중치
		graph[v1].push_back(v2); graph[v1].push_back(weight);
		graph[v2].push_back(v1); graph[v1].push_back(weight);

	}

	for (int i = 1; i <= vertex; i++){
		std::cout << i << "에 연결 : ";
		for (int j = 0; j < graph[i].size(); j++){
			if (!(j % 2)) std::cout << graph[i][j] << ", ";
			else std::cout << graph[i][j-1]<<"까지의 가중치 -> /" <<
				graph[i][j] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}