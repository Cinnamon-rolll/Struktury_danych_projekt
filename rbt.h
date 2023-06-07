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
	void rotate_left(Node* node_x);
	void rotate_right(Node* node_y);
	void insert(Node* x, Node* y, Node* temp);
	bool insert_check(Node* node, int dane);
	void print_tree(Node* node, Node* nill);
	void insertion_fix_up(Node* node);
	void delete_node(Node* node, Node* x, Node* y);
	void deletion_fix_up(Node* x, Node* y);
	int max_depth(Node* n);
	Node* nill_init(Node* n);
	Node* temp_init(Node* n, int);
	void print_elements(Node* node, Node* nill);
	Node* successor_init(Node* node);
	void deletion_driver(Node* node, int dane);
	void tree_move(Node* node,  Node* child_node);
	void menu();

	void generate(int* tab, int amount);

	Red_Black_Tree() {};
	~Red_Black_Tree() {};
};
