#pragma once
#define RED 0
#define BLACK 1

struct Node
{
	int color;
	int data;
	Node* left;
	Node* right;
	Node* parent;
};

class Red_Black_Tree
{
private:
	struct Node* nill;
	struct Node* root;
	struct Node* temp;
public:
	void rotate_left(Node*node_x);
	void rotate_right(Node*node_y);
	void insert(struct Node* x, struct Node* y, struct Node* temp);
	void tree_print(struct Node* node, struct Node* nill);
	void insertion_fix_up(Node*&node);
	int max_depth(Node* n);
	void nill_init(Node*& n);
	void temp_init(Node*&, int);
	void menu();
	Red_Black_Tree(){};
	~Red_Black_Tree(){};
};
