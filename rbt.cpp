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
		{
			return (left_depth + 1);
		}
		else
		{
			return (right_depth + 1);
		}
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

void Red_Black_Tree::print_elements(Node* node, Node* nil)
{
	if (node != nil)
	{
		print_elements(node->left, nil);
		cout << node->data << " " << node->color << endl;
		print_elements(node->right, nil);
	}
}

Node* Red_Black_Tree::successor_init(Node*& node)
{
	while (node->left != nill)
	{
		node = node->left;
	}
	return node;
}

void Red_Black_Tree::deletion_driver(Node* node, int dane)
{
	while (node != nill && dane != node->data) 
	{
		if (dane < node->data)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	if (node->data == dane)
	{
		delete_node(node, node, node);
		cout << "Usunieto! " << "\n";
	}
	else
	{
		cout << "Nie ma w drzewie wezla o danej wartosci!" << "\n";
	}
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

bool Red_Black_Tree::insert_check(Node* node, int dane)
{
	while (node != nill && dane != node->data) {
		if (dane < node->data)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	if (node->data == dane)
	{
		return true;
	}

	return false;
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

void Red_Black_Tree::delete_node(struct Node* node, struct Node* x, struct Node* y)
{
	int org_color = 0;
	org_color = y->color;
	if (node->left == nill) //jezeli node nie ma lewego dziecka
	{
		x = node->right;
		if (node->parent == nill)
		{
			root = node->right;
		}
		else if(node == node->parent->left)
		{
			node->parent->left = node->right;
		}
		else
		{
			node->parent->right = node->right;
		}
		node->right->parent = node->parent;
	}
	else if (node->right = nill)
	{
		x = node->left;
		if (node->parent == nill)
		{
			root = node->left;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = node->left;
		}
		else
		{
			node->parent->right = node->left;
		}
		node->left->parent = node->parent;
	}
	else //jezeli node ma dwoje dzieci
	{
		y = successor_init(node->right); //nastepca
		org_color = y->color;
		x = y->right;
		if (y->parent == node)
		{
			x->parent = y;
		}
		else
		{
			if (y->parent == nill)
			{
				root = y->right;
			}
			else if (y == y->parent->left)
			{
				y->parent->left = y->right;
			}
			else
			{
				y->parent->right = y->right;
			}
			y->right->parent = y->parent;
			y->right = node->right;
			y->right->parent = y;
		}
		if (node->parent == nill)
		{
			root = y;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = y;
		}
		else
		{
			node->parent->right = y;
		}
		y->parent = node->parent;
		y->left = node->left;
		y->left->parent = y;
		y->color = node->color;
	}
	if (org_color == BLACK)
	{
		deletion_fix_up(x, x);
	}
	delete node;
}

	
void Red_Black_Tree::deletion_fix_up(struct Node* x, struct Node* y)
{
	while (x != root && x->color == BLACK) 
	{
		if (x == x->parent->left) //x left kid
		{
			y = x->parent->right; //sibling
			if (y->color == RED) //case 1
			{
				y->color = BLACK;
				x->parent->color = RED;
				rotate_left(x->parent);
				y = x->parent->right;
			}
			else if (y->left->color == BLACK && y->right->color == BLACK) //case 2
			{
				y->color = RED;
				x = x->parent;
			}
			else if (y->right->color == BLACK) //case 3
			{
				y->left->color = BLACK;
				y->color = RED;
				rotate_right(y);
				y = x->parent->right;
			}
			else //case 4
			{
				y->color = x->parent->color;
				x->parent->color = BLACK;
				y->right->color = BLACK;
				rotate_left(x->parent);
				x = root;
			}
		}
		else // x right kid analogicznie
		{
			y = x->parent->left;
			if (y->color == RED) //case 1
			{
				y->color = BLACK;
				x->parent->color = RED;
				rotate_right(x->parent);
				y = x->parent->left;
			}
			else if (y->right->color == BLACK && y->left->color == BLACK) //case 2
			{
				y->color = RED;
				x = x->parent;
			}
			else if (y->left->color == BLACK) //case 3
			{
				y->right->color = BLACK;
				y->color = RED;
				rotate_left(y);
				y = x->parent->left;
			}
			else {
				y->color = x->parent->color;
				x->parent->color = BLACK;
				y->left->color = BLACK;
				rotate_right(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

void Red_Black_Tree::print_tree(struct Node* node, struct Node* nill)
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
			print_tree(node->right, nill);
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
			print_tree(node->left, nill);
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
		cout << "4) Delete node" << "\n";
		cout << "5) Printing elements stored in the tree in increasing order" << "\n";
		cout << "6) End " << "\n";
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
				if (insert_check(root, dane) == false)
				{
					temp_init(temp, dane);
					insert(root, nill, temp);
				}
				else
				{
					cout << "Wezel przechowujacy liczbe " << dane << " juz istnieje " << "\n";
					delete temp;
				}
			}
			system("pause");
			break;
		case 2: 
			cout << "\n";
			cout << "ROOT: " << "\033[90;1m" << root->data << "\033[0m" << "\n";
			print_tree(root, nill);
			cout << "\n";
			system("pause");
			break;
		case 3:
			cout << "\033[95;1mMaksymalna glebokosc drzewa: \033[0m";
			cout << max_depth(root) << "\n";
			system("pause");
			break;
		case 4:
			cout << "\033[95;1mUsuwanie wezla\033[0m" << "\n";
			cout << "Liczba do usuniecia: ";
			cin >> dane;
			deletion_driver(root, dane);
			system("pause");
			break;
		case 5:
			cout << "\033[95;1mWyswietlanie elementow rosnaco\033[0m" << "\n";
			print_elements(root, nill);
			system("pause");
			break;
		default:
			if (choice != 6)
			{
				cout << "Opcja niezawarta w menu. Sprobuj ponownie" << "\n";
				system("pause");
				goto main_menu;
			}
			break;
		}
	} while (choice != 6);

	return;
}
