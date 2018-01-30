#include <iostream>

int graph[21][21]; // �ִ� ������ ����=20��

int main(void)
{
	int vertex; // ������ ��
	int edge; // ������ ��

	int v1, v2; // ����� ����
	int weight; // ����ġ

	std::cin >> vertex >> edge; // ����/������ �� �Է�

	for (int i = 0; i<edge; i++){
		// ����� ������ ����ġ �Է�
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