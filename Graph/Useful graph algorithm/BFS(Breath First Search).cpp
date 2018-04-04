#include <cstdio>
#include <queue>

int graph[11][11];
bool visited[11];

int main(void)
{
	// Undirected graph
	int n, m; scanf("%d%d", &n, &m); // n and m will be connected.

	while (n&&m) {
		graph[n][m] = graph[m][n] = 1;
		scanf("%d%d", &n, &m);
	}

	for (int i = 1; i <= 10; i++) visited[i] = false;
	std::queue<int> adj;

	int v = 1;
	// push first node into queue and makes it true for visiting
	adj.push(v); visited[v] = true;

	// If queue is not empty
	while (!adj.empty()) {
		v = adj.front();
		printf("visited node %d\n", v);
		for (int i = 1; i <= 10; i++) {
			if (graph[v][i] == 1 && !visited[i]) {
				adj.push(i);
				visited[i] = true;
			}
		}
		adj.pop();
	}
	return 0;
}