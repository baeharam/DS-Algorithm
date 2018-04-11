#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <string>

// ���� ����ü
struct item {
	int bi;
	int wi;
	double biwi;
};

// ��� ����ü
struct node {
	int level;
	int benefit;
	int weight;
	double bound;
	int vNum;
};


struct badNode {
	node _node;
	std::string error;
};

// ��尡 ������ ���� �� ���Ǵ� ==������ �����ε�
bool operator==(const node& lhs, const node& rhs)
{
	if (lhs.level == rhs.level &&
		lhs.benefit == rhs.benefit &&
		lhs.weight == rhs.weight &&
		lhs.bound == rhs.bound) return true;
	else return false;
}


// �켱���� ť�� ���� ���Լ�
struct Comparator {
	bool operator()(const node& lhs, const node& rhs) {
		if (lhs.bound == rhs.bound) return lhs.level < rhs.level;
		else return lhs.bound < rhs.bound;
	}
};

// �� item ����ü�� ������ ���� list
std::vector<item> list;

// ����� ��ȣ����� ���� �ش� ������ ��� ��尡 �ִ��� �����ϴ� �迭
int	nodeWatcher[100];
// (��尡 �������� �����ϴ� flag ����)
int max_benefit;

// nonpromising�� ������ �̱� ���� ����
std::vector<badNode> non_promising;
// nonpromising�� ������ �̱� ���� ť�� Ž���ؾ� �ϴµ� ť�� Ž���� �ȵǹǷ� ť�� �ִ� ������ ����� ����
std::vector<node> queue_backup;

// list�� biwi ���� �������� �����ϱ� ���� ���Լ�
bool compare(const item& lhs, const item& rhs) {
	return lhs.biwi > rhs.biwi;
}

// �켱���� ť ���� �Լ�
template<class T, class S, class C>
void ClearQ(std::priority_queue<T, S, C> &q)
{
	q = std::priority_queue<T, S, C>();
}

void isNonPromising(int max_benefit, int maxWeight)
{
	bool isExist = false;
	for (int i = 0; i < queue_backup.size(); i++) {
		if (queue_backup[i].weight>maxWeight || queue_backup[i].bound <= max_benefit) {
			badNode bnode; node _node = queue_backup[i];

			for (int j = 0; j < non_promising.size(); j++) {
				if (non_promising[j]._node == _node) {
					isExist = true;
					break;
				}
			}
			if (!isExist) {
				bnode._node = _node;
				if (_node.weight > maxWeight) bnode.error = "weight > W";
				else bnode.error = "max_benefit >= bound";
				non_promising.push_back(bnode);
			}
			isExist = false;
		}
	}
}

// bound ��� �Լ�
double ComputeBound(node _node, int maxWeight, std::vector<item>& itemList)
{
	int benefit = _node.benefit;
	int weight = _node.weight;
	int level = _node.level;

	// ������ ���԰� �ִ��Ѱ� ���Ը� �ʰ��� ���
	if (weight > maxWeight) return 0;
	else
	{
		int tot_weight = weight; // ��밡���� �ִ� ����
		int k = 0; // �ִ� ���� �ٷ� ������ item�� �ε��� �� (bound�� fractional�� ����ϱ� ���ؼ�)

		// itemList�� �� ���鼭 �˻��ϴµ�
		for (int i = level; i < itemList.size(); i++) {
			// ���� tot_weight�� �� ���� item�� ���Ը� ���� ���� maxWeight ���� �۰ų� ������ ���Ѵ�.
			if (tot_weight + itemList[i].wi <= maxWeight) {
				tot_weight += itemList[i].wi;
				// ���ÿ� benefit�� �����ش�. ��¼�� bound�� ���ԵǾ�� �ϹǷ�
				benefit += itemList[i].bi;
			}
			// �װ� �ƴ϶�� tot_weight>maxWeight�� �Ǵ� item�� �ε����� ���Ѵ�.
			else {
				k = i;
				break;
			}
		}

		double bound = (double)benefit;
		// bound ����. k�� ������ �������� �۰ų� ���ƾ߸� fractional�� ���� �� �ִ� bound�� �ִ�.
		// k�� ������ �������� Ŭ ��� ���� benefit�� �����Ѵ�. (���⼱ �ε����� 0�����̱� ������ k<itemList.size()��.  
		if(k!=0 && k<itemList.size())
			bound += (maxWeight - tot_weight)*(itemList[k].biwi);
		return bound;
	}
}

// branch and bound�� �̿��� knapsack ������ �ذ��Լ�
void BranchandBound(std::vector<item> &itemList, int maxWeight)
{
	std::priority_queue<node, std::vector<node>, Comparator> branchQ;
	ClearQ(branchQ);
	
	// vertex (0,0) ���� �����ϰ� ���
	node _node;
	_node.benefit = 0; _node.level = 0; _node.weight = 0;
	_node.bound = ComputeBound(_node, maxWeight, itemList);
	nodeWatcher[0] = 1;
	std::cout << "--------------------------------\n";
	std::cout << "Vertex (0, 0)�� �����Դϴ�.\n";
	std::cout << "benefit : 0\n";
	std::cout << "weight : 0\n";
	std::cout << "bound : " << _node.bound << "\n";
	std::cout << "--------------------------------\n";

	// �켱���� ť�� �ִ´�.
	branchQ.push(_node);

	

	while (!branchQ.empty())
	{
		_node = branchQ.top();
		// �Ȱ��� ť ��� ���Ϳ��� ����
		for (auto iter = queue_backup.begin(); iter != queue_backup.end(); iter++) {
			if (*iter == _node) {
				queue_backup.erase(iter);
				break;
			}
		}
		branchQ.pop(); // �ִ� bound�� ���� node�� �����Ѵ�.

		// ���� ���� ����� bound�� max_benefit ���� ũ�ٸ� �����ϹǷ� ����
		if (_node.bound > max_benefit && _node.level<itemList.size()) {
			node extend_node;
			// 1. �� ���� level�� ���(item)�� �����ϴ� ���
			extend_node.level = _node.level + 1;
			extend_node.benefit = _node.benefit + itemList[_node.level].bi;
			extend_node.weight = _node.weight + itemList[_node.level].wi;

			// Ȯ��� ��尡 knapsack ��빫�Ը� �����ʰ� benefit�� max_benefit���� ũ�ٸ�,
			// max_benefit�� �����Ѵ�.
			if (extend_node.weight <= maxWeight && extend_node.benefit > max_benefit)
				max_benefit = std::max(extend_node.benefit, max_benefit);

			// Ȯ�� ����� bound ���
			extend_node.bound = ComputeBound(extend_node, maxWeight, itemList);

			nodeWatcher[extend_node.level]++; // ��尡 �ִ� ������ ��尡 �߰��Ǿ��ٴ� ǥ��.
			extend_node.vNum = nodeWatcher[extend_node.level];
			// bound>max_benefit�̶�� ������ ����̹Ƿ� ť�� �ִ´�.
			if (extend_node.bound > max_benefit) branchQ.push(extend_node);

			queue_backup.push_back(extend_node);

			std::cout << "--------------------------------\n";
			std::cout << "Vertex (" << extend_node.level << ", " << nodeWatcher[extend_node.level] << ")�� �����Դϴ�.\n";
			std::cout << "benefit : " << extend_node.benefit << "\n";
			std::cout << "weight : " << extend_node.weight << "\n";
			std::cout << "bound : " << extend_node.bound << "\n";
			std::cout << "--------------------------------\n";
			
			// 2. �� ���� level�� ���(item)�� �������� �ʴ� ���
			extend_node = _node; extend_node.level = _node.level + 1;
			extend_node.bound = ComputeBound(extend_node, maxWeight, itemList);

			nodeWatcher[extend_node.level]++; // ��尡 �ִ� ������ ��尡 �߰��Ǿ��ٴ� ǥ��.
			extend_node.vNum = nodeWatcher[extend_node.level];
			// bound>max_benefit�̶�� ������ ����̹Ƿ� ť�� �ִ´�.
			if (extend_node.bound > max_benefit) branchQ.push(extend_node);

			queue_backup.push_back(extend_node);

			isNonPromising(max_benefit,maxWeight);

			std::cout << "--------------------------------\n";
			std::cout << "Vertex (" << extend_node.level << ", " << nodeWatcher[extend_node.level] << ")�� �����Դϴ�.\n";
			std::cout << "benefit : " << extend_node.benefit << "\n";
			std::cout << "weight : " << extend_node.weight << "\n";
			std::cout << "bound : " << extend_node.bound << "\n";
			std::cout << "--------------------------------\n";
		}

	}

}

int main(void)
{
	std::cout << "������ ������ knapsack�� �ִ� ���Ը� �Է��Ͻÿ� :";
	int n, W; std::cin >> n >> W;

	// item�� list�� ����ִ´�.
	std::cout << "������ ���ݰ� ���Ը� �Է��Ͻÿ�.\n";
	for (int i = 0; i < n; i++) {
		int bi, wi; std::cin >> bi >> wi;
		item temp = { bi,wi, (double)bi / wi };
		list.push_back(temp);
	}
	// ���� �������� ����
	std::sort(list.begin(), list.end(), compare);

	BranchandBound(list, W);

	std::cout << "\n=========================non-promising node lists================================\n\n";
	for (int i = 0; i < non_promising.size(); i++) {
		std::cout << "Vertex (" << non_promising[i]._node.level << ", "<<non_promising[i]._node.vNum<<") �� ";
		std::cout << "Benefit : "; std::cout.width(3); std::cout << non_promising[i]._node.benefit << " | ";
		std::cout << "Weight : "; std::cout.width(3); std::cout<< non_promising[i]._node.weight << " | ";
		std::cout << "Bound : "; std::cout.width(3); std::cout<< non_promising[i]._node.bound << " | ";
		std::cout << non_promising[i].error << "\n";
	}
	std::cout << "\n=========================non-promising node lists================================\n\n";

	std::cout << "���� �� = " << max_benefit << "\n\n";

	return 0;
}