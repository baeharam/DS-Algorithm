#include <iostream>
#include <vector>

std::vector<int> graph[100];

int main(void)
{
	int vertex, edge;
	std::cin >> vertex >> edge;

	int v1, v2;

	while (edge--){
		std::cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}

	for (int i = 1; i <= vertex; i++){
		std::cout << i << "에 연결된 숫자들 : ";
		for (int j = 0; j < graph[i].size(); j++){
			std::cout << graph[i][j] << ' ';

		}
		std::cout << '\n';
	}

	return 0;
}