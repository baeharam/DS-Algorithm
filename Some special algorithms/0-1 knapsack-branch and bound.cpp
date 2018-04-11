#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <string>

// 보석 구조체
struct item {
	int bi;
	int wi;
	double biwi;
};

// 노드 구조체
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

// 노드가 같은지 비교할 때 사용되는 ==연산자 오버로딩
bool operator==(const node& lhs, const node& rhs)
{
	if (lhs.level == rhs.level &&
		lhs.benefit == rhs.benefit &&
		lhs.weight == rhs.weight &&
		lhs.bound == rhs.bound) return true;
	else return false;
}


// 우선순위 큐에 사용될 비교함수
struct Comparator {
	bool operator()(const node& lhs, const node& rhs) {
		if (lhs.bound == rhs.bound) return lhs.level < rhs.level;
		else return lhs.bound < rhs.bound;
	}
};

// 각 item 구조체를 가지는 벡터 list
std::vector<item> list;

// 노드의 번호출력을 위해 해당 레벨에 몇개의 노드가 있는지 감시하는 배열
int	nodeWatcher[100];
// (노드가 유망한지 점검하는 flag 역할)
int max_benefit;

// nonpromising한 노드들을 뽑기 위한 벡터
std::vector<badNode> non_promising;
// nonpromising한 노드들을 뽑기 위해 큐를 탐색해야 하는데 큐는 탐색이 안되므로 큐에 있는 노드들을 백업할 벡터
std::vector<node> queue_backup;

// list를 biwi 기준 내림차순 정렬하기 위한 비교함수
bool compare(const item& lhs, const item& rhs) {
	return lhs.biwi > rhs.biwi;
}

// 우선순위 큐 비우는 함수
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

// bound 계산 함수
double ComputeBound(node _node, int maxWeight, std::vector<item>& itemList)
{
	int benefit = _node.benefit;
	int weight = _node.weight;
	int level = _node.level;

	// 보석의 무게가 최대한계 무게를 초과할 경우
	if (weight > maxWeight) return 0;
	else
	{
		int tot_weight = weight; // 허용가능한 최대 무게
		int k = 0; // 최대 무게 바로 직후의 item의 인덱스 값 (bound로 fractional을 사용하기 위해서)

		// itemList를 쭉 돌면서 검사하는데
		for (int i = level; i < itemList.size(); i++) {
			// 만약 tot_weight에 그 다음 item의 무게를 더한 값이 maxWeight 보다 작거나 같으면 더한다.
			if (tot_weight + itemList[i].wi <= maxWeight) {
				tot_weight += itemList[i].wi;
				// 동시에 benefit도 더해준다. 어쩌피 bound에 포함되어야 하므로
				benefit += itemList[i].bi;
			}
			// 그게 아니라면 tot_weight>maxWeight이 되는 item의 인덱스를 구한다.
			else {
				k = i;
				break;
			}
		}

		double bound = (double)benefit;
		// bound 계산식. k가 보석의 개수보다 작거나 같아야만 fractional로 구할 수 있는 bound가 있다.
		// k가 보석의 개수보다 클 경우 기존 benefit만 리턴한다. (여기선 인덱스가 0부터이기 때문에 k<itemList.size()임.  
		if(k!=0 && k<itemList.size())
			bound += (maxWeight - tot_weight)*(itemList[k].biwi);
		return bound;
	}
}

// branch and bound를 이용한 knapsack 문제의 해결함수
void BranchandBound(std::vector<item> &itemList, int maxWeight)
{
	std::priority_queue<node, std::vector<node>, Comparator> branchQ;
	ClearQ(branchQ);
	
	// vertex (0,0) 부터 생성하고 출력
	node _node;
	_node.benefit = 0; _node.level = 0; _node.weight = 0;
	_node.bound = ComputeBound(_node, maxWeight, itemList);
	nodeWatcher[0] = 1;
	std::cout << "--------------------------------\n";
	std::cout << "Vertex (0, 0)의 값들입니다.\n";
	std::cout << "benefit : 0\n";
	std::cout << "weight : 0\n";
	std::cout << "bound : " << _node.bound << "\n";
	std::cout << "--------------------------------\n";

	// 우선순위 큐에 넣는다.
	branchQ.push(_node);

	

	while (!branchQ.empty())
	{
		_node = branchQ.top();
		// 똑같이 큐 백업 벡터에서 제거
		for (auto iter = queue_backup.begin(); iter != queue_backup.end(); iter++) {
			if (*iter == _node) {
				queue_backup.erase(iter);
				break;
			}
		}
		branchQ.pop(); // 최대 bound를 가진 node를 제거한다.

		// 만약 현재 노드의 bound가 max_benefit 보다 크다면 유망하므로 진행
		if (_node.bound > max_benefit && _node.level<itemList.size()) {
			node extend_node;
			// 1. 그 다음 level의 노드(item)를 선택하는 경우
			extend_node.level = _node.level + 1;
			extend_node.benefit = _node.benefit + itemList[_node.level].bi;
			extend_node.weight = _node.weight + itemList[_node.level].wi;

			// 확장된 노드가 knapsack 허용무게를 넘지않고 benefit이 max_benefit보다 크다면,
			// max_benefit을 갱신한다.
			if (extend_node.weight <= maxWeight && extend_node.benefit > max_benefit)
				max_benefit = std::max(extend_node.benefit, max_benefit);

			// 확장 노드의 bound 계산
			extend_node.bound = ComputeBound(extend_node, maxWeight, itemList);

			nodeWatcher[extend_node.level]++; // 노드가 있는 레벨에 노드가 추가되었다는 표시.
			extend_node.vNum = nodeWatcher[extend_node.level];
			// bound>max_benefit이라면 유망한 노드이므로 큐에 넣는다.
			if (extend_node.bound > max_benefit) branchQ.push(extend_node);

			queue_backup.push_back(extend_node);

			std::cout << "--------------------------------\n";
			std::cout << "Vertex (" << extend_node.level << ", " << nodeWatcher[extend_node.level] << ")의 값들입니다.\n";
			std::cout << "benefit : " << extend_node.benefit << "\n";
			std::cout << "weight : " << extend_node.weight << "\n";
			std::cout << "bound : " << extend_node.bound << "\n";
			std::cout << "--------------------------------\n";
			
			// 2. 그 다음 level의 노드(item)를 선택하지 않는 경우
			extend_node = _node; extend_node.level = _node.level + 1;
			extend_node.bound = ComputeBound(extend_node, maxWeight, itemList);

			nodeWatcher[extend_node.level]++; // 노드가 있는 레벨에 노드가 추가되었다는 표시.
			extend_node.vNum = nodeWatcher[extend_node.level];
			// bound>max_benefit이라면 유망한 노드이므로 큐에 넣는다.
			if (extend_node.bound > max_benefit) branchQ.push(extend_node);

			queue_backup.push_back(extend_node);

			isNonPromising(max_benefit,maxWeight);

			std::cout << "--------------------------------\n";
			std::cout << "Vertex (" << extend_node.level << ", " << nodeWatcher[extend_node.level] << ")의 값들입니다.\n";
			std::cout << "benefit : " << extend_node.benefit << "\n";
			std::cout << "weight : " << extend_node.weight << "\n";
			std::cout << "bound : " << extend_node.bound << "\n";
			std::cout << "--------------------------------\n";
		}

	}

}

int main(void)
{
	std::cout << "보석의 개수와 knapsack의 최대 무게를 입력하시오 :";
	int n, W; std::cin >> n >> W;

	// item을 list에 집어넣는다.
	std::cout << "보석의 가격과 무게를 입력하시오.\n";
	for (int i = 0; i < n; i++) {
		int bi, wi; std::cin >> bi >> wi;
		item temp = { bi,wi, (double)bi / wi };
		list.push_back(temp);
	}
	// 이후 내림차순 정렬
	std::sort(list.begin(), list.end(), compare);

	BranchandBound(list, W);

	std::cout << "\n=========================non-promising node lists================================\n\n";
	for (int i = 0; i < non_promising.size(); i++) {
		std::cout << "Vertex (" << non_promising[i]._node.level << ", "<<non_promising[i]._node.vNum<<") → ";
		std::cout << "Benefit : "; std::cout.width(3); std::cout << non_promising[i]._node.benefit << " | ";
		std::cout << "Weight : "; std::cout.width(3); std::cout<< non_promising[i]._node.weight << " | ";
		std::cout << "Bound : "; std::cout.width(3); std::cout<< non_promising[i]._node.bound << " | ";
		std::cout << non_promising[i].error << "\n";
	}
	std::cout << "\n=========================non-promising node lists================================\n\n";

	std::cout << "최종 답 = " << max_benefit << "\n\n";

	return 0;
}