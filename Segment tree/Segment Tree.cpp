#include <iostream>
#include <cmath>

typedef long long ll;

ll sum(ll tree[], int node, int start, int end, int left, int right)
{
	if (left > end || right < start) return 0;
	if (left <= start && right >= end) return tree[node];

	int mid = (start + end) / 2;
	return sum(tree, node * 2, start, mid, left, right) + sum(tree, node * 2 + 1, mid + 1, end, left, right);
}


// 세그먼트 트리의 어떤 노드 값을 변경했을 때 그에 관련된 모든 노드의 값을 갱신하는 함수
void update(ll tree[], int node, int start, int end, int index, ll diff)
{
	// 부분합 범위에 index가 포함되지 않을 경우 함수를 종료한다.
	if (start > index || end < index) return;

	// 포함될 경우 diff(바꾼 숫자와 기존 숫자의 차이)를 더해주어 갱신한다.
	tree[node] += diff;

	// 숫자를 변경한 노드를 만날때까지 지속한다.
	if (start != end) {
		// 이것도 init함수의 원리와 동일하게 자식노드들로 index 범위에 포함되면 갱신하는 형태
		int mid = (start + end) / 2;
		update(tree, node * 2, start, mid, index, diff);
		update(tree, node * 2 + 1, mid + 1, end, index, diff);
	}
}

// 부분합 노드로 세그먼트 트리를 초기화하는 함수
ll init(ll tree[], ll arr[], int node, int start, int end)
{
	std::cout << start << " ~ " << end << "의 부분합 구하기!, 현재노드 : " << node << '\n';

	// 리프노드일 경우 배열 값이므로 그대로 초기화
	if (start == end) return tree[node] = arr[start];

	// 구간을 나눠야 하는데 그 기준을 mid로 잡는다.
	int mid = (start + end) / 2;

	// 다시 init함수를 호출하여 현재 노드의 자식노드들 즉 node*2와 node*2+1로 부분합을 구하게 한다.
	// 이 호출로 인해 결국 리프노드까지 도달하게 되며 호출이 종료되고 루트노드까지 올라오는 방식이다.
	return tree[node] = init(tree, arr, node * 2, start, mid) + init(tree, arr, node * 2 + 1, mid + 1, end);
}

void PrintTree(ll tree[], int tree_size)
{
	for (int i = 1; i <= tree_size; i++) 
		if(tree[i]!=0)
			std::cout << tree[i] << ' ';
}



int main(void)
{
	int n; std::cin >> n;
	ll *arr = new ll[n];
	for (int i = 1; i <= n; i++) arr[i - 1] = i;

	int h = static_cast<int>(std::ceil(std::log2(n)) + 1);
	int tree_size = static_cast<int>(std::pow(2.0, h) - 1);

	ll *tree = new ll[tree_size + 1]; // 노드번호 1부터 시작이므로 +1
	for (int i = 1; i <= tree_size; i++) tree[i] = 0;

	init(tree, arr, 1, 0, n - 1);
	int left, right; std::cin >> left >> right;

	std::cout << sum(tree, 1, 0, n - 1, left, right);

	return 0;
}