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
	bool insert_check(Node* node, int dane);
	void print_tree(struct Node* aux, struct Node* nill);
	void insertion_fix_up(Node*&node);
	void delete_node(struct Node* node, struct Node* x, struct Node* y);
	void deletion_fix_up(struct Node* x, struct Node* y);
	int max_depth(Node* n);
	void nill_init(Node*& n);
	void temp_init(Node*& n, int);
	void print_elements(Node* node, Node* nill);
	Node* successor_init(Node*& n);
	void deletion_driver(Node* n, int dane);

	void menu();
	Red_Black_Tree(){};
	~Red_Black_Tree() {};
};

