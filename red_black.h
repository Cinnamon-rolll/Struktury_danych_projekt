#pragma once
#include <iostream>

using namespace std;

class Node
{
public:
	Node()
	{
		this->data = data;
		this->key = key;
		this->color = color;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		root = nullptr;
	};
	~Node(){};

	void change_color(Node* node);
	Node* left_rotate(Node* node);
	Node* right_rotate(Node* node);

private:
	int color;
	int data;
	int key;
	Node* left;
	Node* right;
	Node* parent;
	Node* root;
};