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


// ���׸�Ʈ Ʈ���� � ��� ���� �������� �� �׿� ���õ� ��� ����� ���� �����ϴ� �Լ�
void update(ll tree[], int node, int start, int end, int index, ll diff)
{
	// �κ��� ������ index�� ���Ե��� ���� ��� �Լ��� �����Ѵ�.
	if (start > index || end < index) return;

	// ���Ե� ��� diff(�ٲ� ���ڿ� ���� ������ ����)�� �����־� �����Ѵ�.
	tree[node] += diff;

	// ���ڸ� ������ ��带 ���������� �����Ѵ�.
	if (start != end) {
		// �̰͵� init�Լ��� ������ �����ϰ� �ڽĳ���� index ������ ���ԵǸ� �����ϴ� ����
		int mid = (start + end) / 2;
		update(tree, node * 2, start, mid, index, diff);
		update(tree, node * 2 + 1, mid + 1, end, index, diff);
	}
}

// �κ��� ���� ���׸�Ʈ Ʈ���� �ʱ�ȭ�ϴ� �Լ�
ll init(ll tree[], ll arr[], int node, int start, int end)
{
	std::cout << start << " ~ " << end << "�� �κ��� ���ϱ�!, ������ : " << node << '\n';

	// ��������� ��� �迭 ���̹Ƿ� �״�� �ʱ�ȭ
	if (start == end) return tree[node] = arr[start];

	// ������ ������ �ϴµ� �� ������ mid�� ��´�.
	int mid = (start + end) / 2;

	// �ٽ� init�Լ��� ȣ���Ͽ� ���� ����� �ڽĳ��� �� node*2�� node*2+1�� �κ����� ���ϰ� �Ѵ�.
	// �� ȣ��� ���� �ᱹ ���������� �����ϰ� �Ǹ� ȣ���� ����ǰ� ��Ʈ������ �ö���� ����̴�.
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

	ll *tree = new ll[tree_size + 1]; // ����ȣ 1���� �����̹Ƿ� +1
	for (int i = 1; i <= tree_size; i++) tree[i] = 0;

	init(tree, arr, 1, 0, n - 1);
	int left, right; std::cin >> left >> right;

	std::cout << sum(tree, 1, 0, n - 1, left, right);

	return 0;
}