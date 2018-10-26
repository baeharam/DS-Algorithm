#include <stdio.h>
#include <stdlib.h>

enum { A = 1, alpha = 64 };
typedef enum { false, true } bool;

typedef struct node {
	int v;
	int d; // discovery time
	int f; // finish time
	struct node* next;
}Node;

typedef struct list {
	Node* nodeList;
	int vertexNum;
}adjList;

// Allocation and Initialization of Node
Node* CreateNode(int v)
{
	Node* node = (Node*)malloc(sizeof(Node));

	node->d = 0; node->f = 0; node->next = NULL;
	node->v = v;
	return node;
}

// Allocation and Initialization of adjList
adjList* CreateList(int vertexNum)
{
	adjList* list = (adjList*)malloc(sizeof(adjList)*(vertexNum+1));
	for (int i = 1; i <= vertexNum; i++) list[i].nodeList = NULL;
	list->vertexNum = vertexNum;
}

// DFS of specific vertex
void DFS(adjList *adj, bool *visited, int vertex, int *time, int *SCC,int *k)
{
	// If vertex was visited, don't visit
	if (visited[vertex]) return;
	// else, Do DFS!
	else {
		Node* current = adj[vertex].nodeList;
		if (SCC != NULL) SCC[++*k] = vertex;
		visited[vertex] = true;
		// If vertex is visited, discovery time is computed
		current->d = ++*time;
		// Continue to search adjacency vertices
		Node* temp = current->next;
		while (temp != NULL) {
			DFS(adj, visited, temp->v, time, SCC, k);
			temp = temp->next;
		}
		// If there are no adjacent vertices, finish time is computed
		current->f = ++*time;
	}
}

// Transpose of adjacency list
adjList* Transpose(adjList *adj)
{
	// Create adjacency list
	adjList* transpose = CreateList(adj->vertexNum);

	for (int i = 1; i <= adj->vertexNum; i++) {
		// Check all vertices of adj
		Node* current = adj[i].nodeList;
		while (current->next != NULL) {
			current = current->next;
			// Connect vertices to same vertex. so check is very important
			if(transpose[current->v].nodeList==NULL) transpose[current->v].nodeList = CreateNode(current->v);

			// Connceted vertices. It shouldn't be same with other vertices.
			Node* temp = CreateNode(i);

			// Connect process
			Node* t_current = transpose[current->v].nodeList;
			int v = t_current->v;
			while (t_current->next != NULL) { t_current = t_current->next; }
			t_current->next = temp;
		}
	}
	// If memory is not allocated to the "row vertices", allocate.
	for (int i = 1; i <= transpose->vertexNum; i++)
		if (transpose[i].nodeList == NULL) transpose[i].nodeList = CreateNode(i);

	return transpose;
}

// Print Adjacency List using alphabet
void PrintAdj(adjList *adj)
{
	printf("----Adjacency List----\n");
	for (int i = 1; i <= adj->vertexNum; i++) {
		printf("%c : ", i+alpha);
		Node* current = adj[i].nodeList->next;
		if (current == NULL) printf("There are no vertices");
		while (current != NULL) {
			printf("%c ", current->v + alpha);
			current = current->next;
		}
		printf("\n");
	}
	printf("---------------------\n");
}

// vertex and finish time structure
typedef struct vf {
	int v;
	int f;
}VF;

// qsort compare function, descending order
bool cmp(const void *p1, const void *p2)
{
	VF* vf1 = (VF*)p1;
	VF* vf2 = (VF*)p2;
	return vf2->f - vf1->f;
}

// Create sorted vertices array of VF structure
// For DFS of decreasing finish time vertex
VF* CreateSorted(adjList* adj)
{
	VF *sorted_vertices = (VF*)malloc(sizeof(VF)*(adj->vertexNum+1));

	for (int i = 1; i <= adj->vertexNum; i++) {
		Node* current = adj[i].nodeList;
		sorted_vertices[i].v = current->v;
		sorted_vertices[i].f = current->f;
	}
	qsort(sorted_vertices+1, adj->vertexNum, sizeof(VF), cmp);
	for (int i = 1; i <= adj->vertexNum; i++) printf("%d ", sorted_vertices[i].v);
	return sorted_vertices;
}

// Print discovery/finish time of each vertices
void PrintDF(adjList *adj)
{
	printf("----------------Discovery/Finish time----------------\n");
	for (int i = 1; i <= adj->vertexNum; i++) {
		printf("%c : ", i + alpha);
		Node* current = adj[i].nodeList;
		printf("discovery time ¡æ %2d | ", current->d);
		printf("finish time ¡æ %2d\n", current->f);
	}
	printf("-----------------------------------------------------\n");
	
}

// Print SCC list
void PrintSCC(int *SCC, int k)

{
	int n = 1, i = 1; // n = nth SCC element
	while (i <= k) {
		printf("SCC %d : ", n);
		while (SCC[i] != -1 && i<=k) {
			printf("%c ", SCC[i] + alpha);
			i++;
		}
		printf("\n");
		while (SCC[i] == -1) i++;
		n++;
	}
}

// Initialization of "visited array" and "time"
void Init(bool* visited, int vertexNum, int *time)
{
	for (int i = 1; i <= vertexNum; i++) visited[i] = false;
	*time = 0;
}

// Deallocation of adjacency list
void Deallocation(adjList* adj)
{
	for (int i = 1; i <= adj->vertexNum; i++) {
		Node* dealloc = adj[i].nodeList;
		while (dealloc != NULL) {
			Node* temp = dealloc;
			dealloc = dealloc->next;
			free(temp);
		}
	}
	free(adj);
}


int main(void)
{
	// Read file
	FILE *fp = fopen("hw4.data", "r");
	if (fp == NULL) {
		printf("There is no file!");
		return 0;
	}

	// Remove first line
	char c = '\0';
	int vertexNum = 0;
	while ((c = fgetc(fp)) != '\n')
		if (c >= 65 && c <= 90) vertexNum++;

	// Adjacency list allocation
	adjList* adj = CreateList(vertexNum);

	// Read graph array
	int row = A, col = A;
	char vertex = '\0';
	while (fscanf(fp, "%c", &vertex) != EOF) {
		// Dummy node for connecting other nodes
		adj[row].nodeList = CreateNode(row);
		Node *current = adj[row].nodeList;
		while ((c = fgetc(fp)) != '\n' && c!=EOF) {
			if (c == '0') col++;
			else if (c == '1') {
				// Allocation and initialization
				Node* temp = CreateNode(col);
				// Set next node
				current = current->next = temp;
				col++;
			}
		}
		row++;
		col = A;
	}

	// Print original adjacency list
	PrintAdj(adj);

	// Allocation and Initialization of "visited array" to check visiting.
	// Initialization of "time"
	bool* visited = (bool*)malloc(sizeof(bool)*(vertexNum + 1));
	int time = 0;
	Init(visited, vertexNum, &time);
	
	// DFS of original adjacency list
	for (int i = 1; i <= vertexNum; i++) DFS(adj, visited, i, &time,NULL,0);

	// Print discovery/finish time of original adjacency list
	// Find vertex which has biggest finish time
	PrintDF(adj);

	// Transpose original adjacency list
	adjList* adj_transpose = Transpose(adj);
	// Print transposed adjacency list
	printf("\n==================After transposal!==================\n\n");
	PrintAdj(adj_transpose);

	// Initialization of visiting array and time
	Init(visited, vertexNum, &time);

	// SCC array allocation
	// Max SCC case is that all the vertices become SCC individually
	// I need separation sign to separate SCC ¡æ 2*vertexNum+1 is maximum! (index is start from 1, so add 1)
	int *SCC = (int*)malloc(sizeof(int)*(2 * vertexNum + 1 + 1));

	// Create sorted vertices array by latest finish time
	VF* sorted = CreateSorted(adj);

	

	// DFS of transposed adjacency list
	int k = 0;
	for (int i = 1; i <= vertexNum; i++) {
		DFS(adj_transpose, visited, sorted[i].v, &time, SCC, &k);
		if (visited[i]) SCC[++k] = -1;
	}

	// Print discovery/finish time of transposed adjacency list
	PrintDF(adj_transpose);

	// Print SCCs
	PrintSCC(SCC, k);

	// Adjacency list deallocation
	Deallocation(adj);
	Deallocation(adj_transpose);
	
	return 0;
}