#include <cstdio>
#include <queue>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>


using namespace std;

struct node {	
	string code;
	int fre;
	node* left;
	node* right;
};

struct cmp {
	bool operator()(const node* lhs, const node* rhs) {
		return lhs->fre > rhs->fre;
	}
};

std::priority_queue<node*, vector<node*>, cmp> q;

node* Insert(node* root, node* left, node* right) {
	root->left = left;
	root->right = right;
	return root;
}

node* Create(string code, int fre)
{
	node* newNode = new node;
	newNode->code = code;
	newNode->fre = fre;
	newNode->left = newNode->right = NULL;
	return newNode;
}

void Destroy(node* root)
{
	node* current = root;
	while (current != NULL) {
		if (current->left != NULL) Destroy(root->left);
		if (current->right != NULL) Destroy(root->right);
		delete current; current = NULL;
	}
}

std::map<string, string> zip;

void HuffmanCode(node* root, string zo)
{
	if (root->code.compare("")) {
		std::cout << root->code << " : " << zo << '\n';
		zip.insert(std::make_pair(root->code, zo));
	}
	string temp = zo;
	if (root->left != NULL) HuffmanCode(root->left, zo.append("0"));
	if (root->right != NULL) HuffmanCode(root->right, temp.append("1"));
}

int main(void)
{
	printf("입력할 문자의 개수는? : "); int n; scanf("%d", &n);
	printf("문자와 빈도수를 입력하시오 : \n");
	
	int f;
	// 문자와 빈도수를 구조체로 묶어서 큐로 집어넣는데 기준은 빈도수가 작은 것이다.
	for (int i = 1; i <= n; i++) {
		string c;
		std::cin >> c >> f;
		node* huffman = Create(c, f);
		q.push(huffman);
	}

	node* root = NULL;
	
	for (int i = 1; i <= n - 1; i++) {
		node *z = Create("", 0);
		int left = q.top()->fre; node *l = q.top(); q.pop();
		int right = q.top()->fre; node *r = q.top(); q.pop();
		z->fre = left + right;
		z->code = "";

		root=Insert(z, l, r);
		q.push(z);
	}
	printf("-------------------------------\n");
	HuffmanCode(root, "");
	printf("-------------------------------\n");
	string s;
	std::cout << "위 허프만 코드에 적용할 문자열을 입력하시오 : ";
	std::cin >> s;

	for (int i = 0; i < s.size(); i++) {
		string key(1, s[i]);
		std::cout << zip[key];
	}

	Destroy(root);
	system("pause");
	
	return 0;
}