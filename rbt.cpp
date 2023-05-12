#include "rbt.h"
#include <iostream>

using namespace std;


int Red_Black_Tree::max_depth(Node* node)
{
	if (node == nill)
	{
		return 0;
	}
	else 
	{
		int left_depth = max_depth(node->left);
		int right_depth = max_depth(node->right);

		if (right_depth < left_depth)
			return (left_depth + 1);
		else
			return (right_depth + 1);
	}
}

void Red_Black_Tree::nill_init(Node*& nil)
{
	nil->color = BLACK;
	nil->left = NULL;
	nil->right = NULL;
	nil->parent = NULL;
	nil->data = 0;
}

void Red_Black_Tree::temp_init(Node*& temp, int dane)
{
	temp->parent = nill;
	temp->left = nill;
	temp->right = nill;
	temp->data = dane;
	temp->color = BLACK;
}

void Red_Black_Tree::rotate_left(Node*node_x)
{
	Node* node_y;
	node_y = node_x->right;
	node_x->right = node_y->left;
	if (node_y->left != nill)
	{
		node_y->left->parent = node_x;
	}
	node_y->parent = node_x->parent;
	if (node_x->parent == nill)
	{
		root = node_y;
	}
	else if (node_x == node_x->parent->left)
	{
		node_x->parent->left = node_y;
	}
	else if(node_x == node_x->parent->right)
	{
		node_x->parent->right = node_y;
	}
	node_y->left = node_x;
	node_x->parent = node_y;
}

void Red_Black_Tree::rotate_right(Node*node_y)
{
	Node* node_x;
	node_x = node_y->left;
	node_y->left = node_x->right;
	if (node_x->right != nill)
	{
		node_x->right->parent = node_y;
	}
	node_x->parent = node_y->parent;
	if (node_y->parent == nill)
	{
		root = node_x;
	}
	else if (node_y == node_y->parent->right)
	{
		node_y->parent->right = node_x;
	}
	else if (node_y == node_y->parent->left)
	{
		node_y->parent->left = node_x;
	}
	node_x->right = node_y;
	node_y->parent = node_x;
}

void Red_Black_Tree::insert(struct Node* x, struct Node* y, struct Node* node) 
{
	while (x != nill) 
	{
		y = x;
		if (node->data < x->data)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	node->parent = y;
	if (y == nill)			
	{
		root = node;
	}
	else if (node->data < y->data)
	{
		y->left = node;
	}
	else                     
	{
		y->right = node;
	}
	//wstawiony regulacje
	node->left = nill;
	node->right = nill;
	node->color = RED;
	insertion_fix_up(node);   
}

void Red_Black_Tree::insertion_fix_up(Node*&node)
{
	cout << "ODPALIL" << "\n";
	struct Node* y;
	while (node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			y = node->parent->parent->right;
			if (y->color == RED)
			{
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->right)
				{
					node = node->parent;
					rotate_left(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotate_right(node->parent->parent);
			}
		}
		else if (node->parent == node->parent->parent->right)
		{
			y = node->parent->parent->left;
			if (y->color == RED)
			{
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					rotate_right(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotate_left(node->parent->parent);
			}
		}
	}
	root->color = BLACK;

}

void Red_Black_Tree::tree_print(struct Node* node, struct Node* nill)
{
	if (node != nill) {
		if (node->right != nill) 
		{
			if (node->color == BLACK) 
			{
				cout << "\033[90m" << node->data << "\033[0m";
				cout << " -> right: ";
			}
			else if (node->color == RED) 
			{
				cout << "\033[31m" << node->data << "\033[0m";
				cout << " -> right: ";
			}
			if (node->right->color == BLACK)
			{
				cout << "\033[90m" << node->right->data << "\033[0m" << "\n";
			}
			else if (node->right->color == RED) 
			{
				cout << "\033[31m" << node->right->data << "\033[0m" << "\n";
			}
			tree_print(node->right, nill);
		}
		if (node->left != nill) {
			if (node->color == BLACK)
			{
				cout << "\033[90m" << node->data << "\033[0m";
				cout << " -> left: ";
			}
			else if (node->color == RED)
			{
				cout << "\033[31m" << node->data << "\033[0m";
				cout << " -> left: ";
			}
			if (node->left->color == BLACK)
			{
				cout << "\033[90m" << node->left->data << "\033[0m" << "\n";
			}
			else if (node->left->color == RED)
			{
				cout << "\033[31m" << node->left->data << "\033[0m" << "\n";
			}
			tree_print(node->left, nill);
		}
	}
}

void Red_Black_Tree::menu()
{
	int dane = 0;
	int choice = 0;
	nill = new Node();
	nill_init(nill);
	root = nill;

	do
	{
		main_menu:
		system("cls");
		cout << "\033[95;1m--- MENU ---\033[0m" << "\n";
		cout << "1) Insert node" << "\n";
		cout << "2) Print tree" << "\n";
		cout << "3) Tree max depth" << "\n";
		cout << "4) End " << "\n";
		cin >> choice;
		switch (choice)
		{
		case 1: 
			cout << "\033[95;1mWstawianie nowej danej\033[0m" << "\n";
			cout << "Liczba: ";
			cin >> dane;
			cout<<"\n";
			if ((temp = new Node()) != NULL)
			{
				temp_init(temp, dane);
				insert(root, nill, temp);
			}
			system("pause");
			break;
		case 2: 
			cout << "\n";
			cout << "ROOT: " << "\033[90;1m" << root->data << "\033[0m" << "\n";
			tree_print(root, nill);
			cout << "\n";
			system("pause");
			break;
		case 3:
			cout << "\033[95;1mMaksymalna glebokosc drzewa: \033[0m";
			cout << max_depth(root) << "\n";
			system("pause");
			break;
		default:
			if (choice != 4)
			{
				cout << "Opcja niezawarta w menu. Sprobuj ponownie" << "\n";
				system("pause");
				goto main_menu;
			}
			break;
		}
	} while (choice != 4);
	return;
}
