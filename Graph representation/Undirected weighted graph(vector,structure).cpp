#include <iostream>
#include <vector>

// vertex와 weight의 짝 (pair객체 대체)
typedef struct vw{
	int v;
	int w;
}VW;

std::vector<vw> graph[100];

int main(void)
{
	int vertex, edge;
	std::cin >> vertex >> edge;

	int v1, v2, weight; // 가중치포함

	while (edge--){
		std::cin >> v1 >> v2 >> weight;
		// 정점을 push_back하고 가중치도 push_back
		VW temp; temp.v = v2; temp.w = weight;
		graph[v1].push_back(temp);
		temp.v = v1;
		graph[v2].push_back(temp);

	}

	for (int i = 1; i <= vertex; i++){
		std::cout << i << "에 연결 : ";
		for (int j = 0; j < graph[i].size(); j++){
			std::cout << graph[i][j].v << " ,";
			std::cout << "가중치 (" << graph[i][j].w << ") ";
		}
		std::cout << '\n';
	}

	return 0;
}