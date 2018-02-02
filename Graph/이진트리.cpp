#include <iostream>
#include <string>

// ��� Ŭ����
// �̸��� ��, ����������, �����������͸� ������.
class Node{
private:
	int data; // ��
	std::string name; // �̸�
	Node* left; // ���� �ڽ� ���
	Node* right; // ������ �ڽ� ���

public:
	Node(int _data, std::string _name) :data(_data), name(_name), left(NULL), right(NULL)
	{} // ������ 
	int getData() const { return data; } // �� ��ȯ
	void setData(int _data) { data = _data; } // �� ����
	Node* getLeft() const { return left; } // ���� �ڽ� ����� ������ ��ȯ
	Node* getRight() const{ return right; } // ������ �ڽ� ����� ������ ��ȯ
	std::string getName() const{ return name; } // �̸� ��ȯ
	void setLeft(Node* left){ this->left = left; } // ���� �ڽ� ��� ����
	void setRight(Node* right) { this->right = right; } // ������ �ڽ� ��� ����
};

// ����Ʈ�� Ŭ����
class BinaryTree{
public:
	void InsertLeftChild(Node& parent, Node& leftChild); // ���� �ڽ� ��� ����
	void InsertRightChild(Node& parent, Node& rightChild); // ������ �ڽ� ��� ����
	void DrawBinaryTree(Node& draw); // Ʈ�� �׸���
	void PreorderTraversal(Node& draw); // ������ȸ
	void InorderTraversal(Node& draw); // ������ȸ
	void PostorderTraversal(Node& draw); // ������ȸ
	void RemoveLeftSubtree(Node& left); // ���� �κ�Ʈ�� ����
	void RemoveRightSubtree(Node& right); // ������ �κ�Ʈ�� ����
};

// ���� �ڽ� ��� ���� �Լ�
// parent�� ���ʿ� leftChild ����
void BinaryTree::InsertLeftChild(Node& parent, Node& leftChild)
{
	parent.setLeft(&leftChild);
}

// ������ �ڽ� ��� ���� �Լ�
// parent�� �����ʿ� rightChild ����
void BinaryTree::InsertRightChild(Node& parent, Node& rightChild)
{
	parent.setRight(&rightChild);
}

// ���� �κ� Ʈ�� ���� �Լ�
// left�� ���� �κ� Ʈ�� ����
void BinaryTree::RemoveLeftSubtree(Node& left)
{
	left.setLeft(NULL);
}

// ������ �κ� Ʈ�� ���� �Լ�
// right�� ������ �κ� Ʈ�� ����
void BinaryTree::RemoveRightSubtree(Node& right)
{
	right.setRight(NULL);
}

// ������ȸ
// ��Ʈ ��带 �������� ��������Ʈ�� �湮 �� ������ ����Ʈ�� �湮
void BinaryTree::PreorderTraversal(Node& draw)
{
	if (&draw == NULL) return;
	else std::cout << draw.getName() << "(" << draw.getData() << ")" << " �� ";
	PreorderTraversal(*draw.getLeft());
	PreorderTraversal(*draw.getRight());
}

// ������ȸ
// ���� ������ ��带 �������� �� ����� ��Ʈ��� �湮 �� ������ ����Ʈ�� �湮
void BinaryTree::InorderTraversal(Node& draw)
{
	if (&draw == NULL) return;
	else{
		InorderTraversal(*draw.getLeft());
		std::cout << draw.getName() << "(" << draw.getData() << ")" << " �� ";
		InorderTraversal(*draw.getRight());
	}
}

// ������ȸ
// ���� ������ ��带 �������� ���� ������ ������ ��带 �湮 �� ��Ʈ ��� �湮
void BinaryTree::PostorderTraversal(Node& draw)
{
	if (&draw == NULL) return;
	else{
		PostorderTraversal(*draw.getLeft());
		PostorderTraversal(*draw.getRight());
		std::cout << draw.getName() << "(" << draw.getData() << ")" << " �� ";
	}
}

// � �͵��� ����Ǿ��ִ��� Ʈ���� ��Ÿ���ִ� �Լ�
void BinaryTree::DrawBinaryTree(Node& draw)
{
	std::cout << draw.getName() << " �� ";
	if (draw.getLeft() == NULL)
		std::cout << "�����ڽĳ�尡 �����ϴ�! \n";
	else
		std::cout << "�����ڽĳ��" << draw.getLeft()->getName() << " �� ���� "<<draw.getLeft()->getData()<<"�Դϴ�.\n";
	if (draw.getRight() == NULL)
		std::cout << "     �������ڽĳ�尡 �����ϴ�! \n";
	else
		std::cout << "     �������ڽĳ��" << draw.getRight()->getName() << " �� ���� " << draw.getRight()->getData() << "�Դϴ�.\n";

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

	std::cout << "������ȸ\n"; bt.PreorderTraversal(A); std::cout << '\n' << '\n';
	std::cout << "������ȸ\n"; bt.InorderTraversal(A); std::cout << '\n' << '\n';
	std::cout << "������ȸ\n"; bt.PostorderTraversal(A);


	return 0;
}