#include <iostream>
#include <vector>

std::vector<int> graph[100];

int main(void)
{
	int vertex, edge;
	std::cin >> vertex >> edge;

	int v1, v2, weight; // ����ġ����

	while (edge--){
		std::cin >> v1 >> v2 >> weight;
		// ������ push_back�ϰ� ����ġ�� push_back
		// ¦����° : ����, Ȧ����° : ����ġ
		graph[v1].push_back(v2); graph[v1].push_back(weight);
		graph[v2].push_back(v1); graph[v1].push_back(weight);

	}

	for (int i = 1; i <= vertex; i++){
		std::cout << i << "�� ���� : ";
		for (int j = 0; j < graph[i].size(); j++){
			if (!(j % 2)) std::cout << graph[i][j] << ", ";
			else std::cout << graph[i][j-1]<<"������ ����ġ -> /" <<
				graph[i][j] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}