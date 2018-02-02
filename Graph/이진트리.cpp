#include <iostream>
#include <string>

// 노드 클래스
// 이름과 값, 왼쪽포인터, 오른쪽포인터를 가진다.
class Node{
private:
	int data; // 값
	std::string name; // 이름
	Node* left; // 왼쪽 자식 노드
	Node* right; // 오른쪽 자식 노드

public:
	Node(int _data, std::string _name) :data(_data), name(_name), left(NULL), right(NULL)
	{} // 생성자 
	int getData() const { return data; } // 값 반환
	void setData(int _data) { data = _data; } // 값 대입
	Node* getLeft() const { return left; } // 왼쪽 자식 노드의 포인터 반환
	Node* getRight() const{ return right; } // 오른쪽 자식 노드의 포인터 반환
	std::string getName() const{ return name; } // 이름 반환
	void setLeft(Node* left){ this->left = left; } // 왼쪽 자식 노드 설정
	void setRight(Node* right) { this->right = right; } // 오른쪽 자식 노드 설정
};

// 이진트리 클래스
class BinaryTree{
public:
	void InsertLeftChild(Node& parent, Node& leftChild); // 왼쪽 자식 노드 삽입
	void InsertRightChild(Node& parent, Node& rightChild); // 오른쪽 자식 노드 삽입
	void DrawBinaryTree(Node& draw); // 트리 그리기
	void PreorderTraversal(Node& draw); // 전위순회
	void InorderTraversal(Node& draw); // 중위순회
	void PostorderTraversal(Node& draw); // 후위순회
	void RemoveLeftSubtree(Node& left); // 왼쪽 부분트리 제거
	void RemoveRightSubtree(Node& right); // 오른쪽 부분트리 제거
};

// 왼쪽 자식 노드 삽입 함수
// parent의 왼쪽에 leftChild 삽입
void BinaryTree::InsertLeftChild(Node& parent, Node& leftChild)
{
	parent.setLeft(&leftChild);
}

// 오른쪽 자식 노드 삽입 함수
// parent의 오른쪽에 rightChild 삽입
void BinaryTree::InsertRightChild(Node& parent, Node& rightChild)
{
	parent.setRight(&rightChild);
}

// 왼쪽 부분 트리 제거 함수
// left의 왼쪽 부분 트리 제거
void BinaryTree::RemoveLeftSubtree(Node& left)
{
	left.setLeft(NULL);
}

// 오른쪽 부분 트리 제거 함수
// right의 오른쪽 부분 트리 제거
void BinaryTree::RemoveRightSubtree(Node& right)
{
	right.setRight(NULL);
}

// 전위순회
// 루트 노드를 시작으로 왼쪽하위트리 방문 후 오른쪽 하위트리 방문
void BinaryTree::PreorderTraversal(Node& draw)
{
	if (&draw == NULL) return;
	else std::cout << draw.getName() << "(" << draw.getData() << ")" << " → ";
	PreorderTraversal(*draw.getLeft());
	PreorderTraversal(*draw.getRight());
}

// 중위순회
// 왼쪽 최하위 노드를 시작으로 그 노드의 루트노드 방문 후 오른쪽 하위트리 방문
void BinaryTree::InorderTraversal(Node& draw)
{
	if (&draw == NULL) return;
	else{
		InorderTraversal(*draw.getLeft());
		std::cout << draw.getName() << "(" << draw.getData() << ")" << " → ";
		InorderTraversal(*draw.getRight());
	}
}

// 후위순회
// 왼쪽 최하위 노드를 시작으로 같은 레벨의 오른쪽 노드를 방문 후 루트 노드 방문
void BinaryTree::PostorderTraversal(Node& draw)
{
	if (&draw == NULL) return;
	else{
		PostorderTraversal(*draw.getLeft());
		PostorderTraversal(*draw.getRight());
		std::cout << draw.getName() << "(" << draw.getData() << ")" << " → ";
	}
}

// 어떤 것들이 연결되어있는지 트리를 나타내주는 함수
void BinaryTree::DrawBinaryTree(Node& draw)
{
	std::cout << draw.getName() << " → ";
	if (draw.getLeft() == NULL)
		std::cout << "왼쪽자식노드가 없습니다! \n";
	else
		std::cout << "왼쪽자식노드" << draw.getLeft()->getName() << " 의 값은 "<<draw.getLeft()->getData()<<"입니다.\n";
	if (draw.getRight() == NULL)
		std::cout << "     오른쪽자식노드가 없습니다! \n";
	else
		std::cout << "     오른쪽자식노드" << draw.getRight()->getName() << " 의 값은 " << draw.getRight()->getData() << "입니다.\n";

	std::cout << "------------------------------------------------------------\n";

	if (draw.getLeft()) DrawBinaryTree(*draw.getLeft());
	if (draw.getRight()) DrawBinaryTree(*draw.getRight());
}

int main(void)
{
	Node A(1, "A"), B(2, "B"), C(3, "C"), D(4, "D"), E(5, "E");
	BinaryTree bt;
	
	bt.InsertLeftChild(A,B);
	bt.InsertRightChild(A,C);

	bt.InsertLeftChild(B, D);
	bt.InsertRightChild(B, E);

	bt.DrawBinaryTree(A);

	std::cout << "전위순회\n"; bt.PreorderTraversal(A); std::cout << '\n' << '\n';
	std::cout << "중위순회\n"; bt.InorderTraversal(A); std::cout << '\n' << '\n';
	std::cout << "후위순회\n"; bt.PostorderTraversal(A);


	return 0;
}