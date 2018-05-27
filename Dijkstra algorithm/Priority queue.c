#include "Graph.h"

// heap 구조체
// 실제 heap으로 동작하는 heapTree와 할당크기인 capacity,
// 그리고 현재 데이터의 개수인 currentSize를 갖는다.
typedef struct heap {
	int *heapTree;
	int capacity;
	int currentSize;
}Heap;

// swap 함수
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


// Heap을 동적 할당해서 리턴
Heap* CreateHeap(int size)
{
	Heap *h = (Heap*)malloc(sizeof(Heap));
	h->heapTree = (int*)malloc(sizeof(int)*size);
	h->capacity = size;
	h->currentSize = 0;
	return h;
}

// MinHeap에 삽입
void Insert(Heap *heap, Graph *g, Vertex *data)
{
	// 힙의 마지막 위치
	int cur = heap->currentSize;

	// 그 위치가 capacity랑 같다는 것은 이미 힙이 다 찼다는 것.
	if (cur == heap->capacity) {
		printf("힙이 가득찼습니다.");
		return;
	}

	// 가장 마지막에 데이터 삽입
	int *tree = heap->heapTree;
	tree[cur] = data->v;

	// 트리에서 부모 노드
	int parent = (cur - 1) / 2;

	// 부모노드의 값이 자식노드의 값보다 크면 바꾼 뒤에
	// 트리를 올라간다. (= 부모와 자식을 초기화한다)
	while (g->adj[tree[parent]]->distance > g->adj[tree[cur]]->distance) {
		swap(&tree[parent], &tree[cur]);
		cur = parent;
		parent = (cur - 1) / 2;
	}

	// 원소의 개수 증가
	heap->currentSize++;
}

// MinHeap에서 제거
int extractMin(Heap *heap, Graph *g)
{
	// 힙의 마지막 원소, 삽입할 때 currentSize를 증가시키기 때문에
	// 삭제할 때는 1을 빼주어야 한다. 단, 0이 아닐 경우이므로 검사 후에 빼준다.
	if (heap->currentSize == 0) {
		printf("힙이 비었습니다.");
		return -1;
	}
	heap->currentSize--;
	int last = heap->currentSize;
	int *tree = heap->heapTree;

	// 루트 노드의 값이 제일 작은 값이므로 루트 노드를 제거하면 간단할 것 같지만
	// 다시 힙으로 만드는데 복잡하기 때문에 마지막 원소와 바꾼다.
	swap(&tree[last], &tree[0]);
	// 리턴할 값(min) 받아온다.
	int min = tree[last];

	// 루트노드부터 힙으로 만들어야 하므로 left child와 right child가 있다.
	int cur = 0, left, right;
	left = cur * 2 + 1;
	right = cur * 2 + 2;
	int minNode = cur;

	// 힙으로 만드는 과정 (heapify)
	// currentSize는 힙에서 제일 작은 값이 삭제된 크기, 즉 이 크기 바로 직전까지 원소가 존재하므로
	// left와 right이 존재하기 위해선 이것보다 작아야 하며 left가 있어야 right이 있기 때문에 left부터 한다.
	// 반복은 child가 아예 없을 때까지.
	while (left < heap->currentSize) {
		if (g->adj[tree[cur]]->distance > g->adj[tree[left]]->distance) minNode = left;
		if (right<heap->currentSize && g->adj[tree[minNode]]->distance>g->adj[tree[right]]->distance) minNode = right;
		// cur==minNode의 의미는 child가 없다는 뜻
		if (cur == minNode) break;
		else {
			swap(&tree[cur], &tree[minNode]);
			cur = minNode;
			left = cur * 2 + 1;
			right = cur * 2 + 2;
		}
	}

	return min;
}

