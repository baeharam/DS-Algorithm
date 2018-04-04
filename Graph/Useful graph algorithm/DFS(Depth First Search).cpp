#include <cstdio>
#include <stack>

int graph[11][11];
bool visited[11];

void DFS(int v)
{
	printf("visited node %d\n", v);
	visited[v] = true;
	for (int i = 1; i <= 10; i++)
		if (graph[v][i] == 1 && !visited[i]) DFS(i);
}

int main(void)
{
	// Undirected graph
	int n, m; scanf("%d%d", &n, &m); // n and m will be connected.

	while (n&&m) {
		graph[n][m] = graph[m][n] = 1;
		scanf("%d%d", &n, &m);
	}

	for (int i = 1; i <= 10; i++) visited[i] = false;

	// Recursive DFS
	//DFS(1);

	std::stack<int> adj;
	int v = 1;
	adj.push(v);


	// Stack DFS
	while (!adj.empty()) {
		bool adjacent = false;
		v = adj.top();
		if (!visited[v]) {
			printf("visited node %d\n", v);
			visited[v] = true;
		}
		for (int i = 1; i <= 10; i++) {
			if (graph[v][i] == 1 && !visited[i]) {
				adjacent = true;
				adj.push(i);
				break;
			}
		}
		if (!adjacent) adj.pop();
	}

	return 0;
}