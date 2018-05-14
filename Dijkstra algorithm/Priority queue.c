#include "Graph.c"

// heap ����ü
// ���� heap���� �����ϴ� heapTree�� �Ҵ�ũ���� capacity,
// �׸��� ���� �������� ������ currentSize�� ���´�.
typedef struct heap {
	int *heapTree;
	int capacity;
	int currentSize;
}Heap;

// swap �Լ�
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


// Heap�� ���� �Ҵ��ؼ� ����
Heap* CreateHeap(int size)
{
	Heap *h = (Heap*)malloc(sizeof(Heap));
	h->heapTree = (int*)malloc(sizeof(int)*size);
	h->capacity = size;
	h->currentSize = 0;
	return h;
}

// MinHeap�� ����
void Insert(Heap *heap, Graph *g, Vertex *data)
{
	// ���� ������ ��ġ
	int cur = heap->currentSize;

	// �� ��ġ�� capacity�� ���ٴ� ���� �̹� ���� �� á�ٴ� ��.
	if (cur == heap->capacity) {
		printf("���� ����á���ϴ�.");
		return;
	}

	// ���� �������� ������ ����
	int *tree = heap->heapTree;
	tree[cur] = data->v;

	// Ʈ������ �θ� ���
	int parent = (cur - 1) / 2;

	// �θ����� ���� �ڽĳ���� ������ ũ�� �ٲ� �ڿ�
	// Ʈ���� �ö󰣴�. (= �θ�� �ڽ��� �ʱ�ȭ�Ѵ�)
	while (g->adj[tree[parent]]->distance > g->adj[tree[cur]]->distance) {
		swap(&tree[parent], &tree[cur]);
		cur = parent;
		parent = (cur - 1) / 2;
	}

	// ������ ���� ����
	heap->currentSize++;
}

// MinHeap���� ����
int extractMin(Heap *heap, Graph *g)
{
	// ���� ������ ����, ������ �� currentSize�� ������Ű�� ������
	// ������ ���� 1�� ���־�� �Ѵ�. ��, 0�� �ƴ� ����̹Ƿ� �˻� �Ŀ� ���ش�.
	if (heap->currentSize == 0) {
		printf("���� ������ϴ�.");
		return -1;
	}
	heap->currentSize--;
	int last = heap->currentSize;
	int *tree = heap->heapTree;

	// ��Ʈ ����� ���� ���� ���� ���̹Ƿ� ��Ʈ ��带 �����ϸ� ������ �� ������
	// �ٽ� ������ ����µ� �����ϱ� ������ ������ ���ҿ� �ٲ۴�.
	swap(&tree[last], &tree[0]);
	// ������ ��(min) �޾ƿ´�.
	int min = tree[last];

	// ��Ʈ������ ������ ������ �ϹǷ� left child�� right child�� �ִ�.
	int cur = 0, left, right;
	left = cur * 2 + 1;
	right = cur * 2 + 2;
	int minNode = cur;

	// ������ ����� ���� (heapify)
	// currentSize�� ������ ���� ���� ���� ������ ũ��, �� �� ũ�� �ٷ� �������� ���Ұ� �����ϹǷ�
	// left�� right�� �����ϱ� ���ؼ� �̰ͺ��� �۾ƾ� �ϸ� left�� �־�� right�� �ֱ� ������ left���� �Ѵ�.
	// �ݺ��� child�� �ƿ� ���� ������.
	while (left < heap->currentSize) {
		if (g->adj[tree[cur]]->distance > g->adj[tree[left]]->distance) minNode = left;
		if (right<heap->currentSize && g->adj[tree[minNode]]->distance>g->adj[tree[right]]->distance) minNode = right;
		// cur==minNode�� �ǹ̴� child�� ���ٴ� ��
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

