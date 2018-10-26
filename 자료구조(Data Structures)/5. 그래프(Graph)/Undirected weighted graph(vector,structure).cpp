#include <iostream>
#include <vector>

// vertex�� weight�� ¦ (pair��ü ��ü)
typedef struct vw{
	int v;
	int w;
}VW;

std::vector<vw> graph[100];

int main(void)
{
	int vertex, edge;
	std::cin >> vertex >> edge;

	int v1, v2, weight; // ����ġ����

	while (edge--){
		std::cin >> v1 >> v2 >> weight;
		// ������ push_back�ϰ� ����ġ�� push_back
		VW temp; temp.v = v2; temp.w = weight;
		graph[v1].push_back(temp);
		temp.v = v1;
		graph[v2].push_back(temp);

	}

	for (int i = 1; i <= vertex; i++){
		std::cout << i << "�� ���� : ";
		for (int j = 0; j < graph[i].size(); j++){
			std::cout << graph[i][j].v << " ,";
			std::cout << "����ġ (" << graph[i][j].w << ") ";
		}
		std::cout << '\n';
	}

	return 0;
}