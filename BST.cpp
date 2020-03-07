#include "BST.h"
#include <iostream>
using namespace std;

BST::BST()
{

}

void BST::insert (int val)
{
	if (root == nullptr)
	{
		root = new Node;
		root->data = val;
		return;
	}
	//else
	Node* y = nullptr;
	Node* node = this->root;
	while (node != nullptr)
	{
		y = node;
		if (val < node->data)
			node = node->left;
		else
			node = node->right;
	}
	if (val < y->data)
	{	
		y->left = new Node;
		y->left->data = val;
		y->left->left = nullptr;
		y->left->right = nullptr;
		y->left->parent = y;
		return;
	}
	else if (val >= y->data)
	{
		y->right = new Node;
		y->right->data = val;
		y->right->left = nullptr;
		y->right->right = nullptr;
		y->right->parent = y;
		return;
	}

}
void BST::callInOrderTraversal()
{
	InOrderTraversal(this->root);
	cout << endl;
	return;
}
void BST::InOrderTraversal(Node* node)
{
	if (root == NULL)
		return;

	while (node != nullptr)
	{
		InOrderTraversal(node->left);
		cout << node->data << " ";
		InOrderTraversal(node->right);
		
		return;
	}
}

void BST::callPreOrderTraversal()
{
	PreOrderTraversal(this->root);
	return;
}
void BST::PreOrderTraversal(Node* node)
{
	if (root == NULL)
		return;

	while (node != nullptr)
	{
		cout << node->data << " ";
		InOrderTraversal(node->left);
		InOrderTraversal(node->right);
		return;
	}
}
void BST::callPostOrderTraversal()
{
	PreOrderTraversal(this->root);
	return;
}
void BST::PostOrderTraversal(Node* node)
{
	if (root == NULL)
		return;

	while (node != nullptr)
	{
		
		InOrderTraversal(node->left);
		InOrderTraversal(node->right);
		cout << node->data << " ";
		return;
	}
}

void BST::Transplant()
{
}

int BST::getMin(Node* node)
{
	while (node->left != nullptr)
	{
		return (getMin(node->left));
	}
	return node->data;
}
int BST::minimum()
{
	return getMin(this->root);
}

int BST::getMax(Node* node)
{
	while (node->right != nullptr)
	{
		return (getMax(node->right));
	}
	return node->data;
}
int BST::maximum()
{
	return getMax(this->root);
}

Node* BST::search(int val)
{
	if (root == nullptr)
	{
		cout << "Error: Tree is empty you dummy!" << endl;
		return nullptr;
	}
	Node *node = this->root;
	
	while (node != nullptr && node->data != val)
	{
		if (val < node->data)
			node = node->left;
		else
			node = node->right;
	}
	if (node == nullptr)
		return nullptr;

	if (node->data == val)
		return node;

	return nullptr;
}
int BST::succesor(int val)
{
	Node *Me = search(val);
	if (!Me)
	{
		cout << "We dont have that value yet" << endl;
		return -1;
	}
	if (Me->right != NULL)
	{
		return getMin(Me->right);
	}
	//else: lets find the parent, which I'm on his left (as long as I'm on my parent's right, looooop)
	Node* y = Me->parent;
	while (y != nullptr && Me == y->right)
	{
		Me = y;
		y = Me->parent;
	}
	if (y)
	{
		return y->data;
	}
	cout << "Error: This is the Maximum value, no succesor exists." << endl;
	return -1;
}

int BST::presuccesor(int val)
{
	Node *Me = search(val);
	if (!Me)
	{
		cout << "We dont have that value yet" << endl;
		return -1;
	}

	if (Me->left != NULL)
	{
		return getMax(Me->left);
	}
	//else: lets find the parent, which I'm on his left (as long as I'm on my parent's right, looooop)
	Node* y = Me->parent;
	while (y != nullptr && Me == y->left)
	{
		Me = y;
		y = Me->parent;
	}
	if (y)
	{
		return y->data;
	}
	cout << "Error: This is the Maximum value, no succesor exists." << endl;
	return -1;
}


bool BST::deleteNode(int val)
{
	Node* D = search(val);
	if (!D)
	{
		cout << "Error: That node is not exist yet  "<<val << endl;
		return false;
	}
	//else: 
	//D is already a leaf
	if (D->left == nullptr && D->right == nullptr)
	{
		Node* p = D->parent;
		if (p->left == D)
		{
			p->left = nullptr;
			D = nullptr;
			return true;
		}
		else {
			p->right = nullptr;
			D = nullptr;
			return true;
		}
	}
	//else: I'm not a leaf
	//D has only a left child
	if (D->left != nullptr && D->right == nullptr)
	{
		Node* p = D->parent;
		if (!p)
		{
			root = D->right;
			root->parent = nullptr;
			delete D;
			return true;
		}
		if (p->left == D)
		{
			p->left = D->left;
			D = nullptr;
			return true;
		}
		else {
			p->right = D->left;
			D = nullptr;
			return true;
		}
	}
	if (D->left == nullptr && D->right != nullptr)
	{
		Node* p = D->parent;
		if (!p)
		{
			root = D->right;
			root->parent = nullptr;
			delete D;
			return true;
		}
		if (p->left == D)
		{
			p->left = D->right;
			D = nullptr;
			return true;
		}
		else {
			p->right = D->right;
			D = nullptr;
			return true;
		}
	}	
	//else: D has two kids
	//First: if the oldest son has no left
	if (D->left != nullptr && D->right != nullptr)
	{
		if (D->right->left == nullptr)
		{
			D->right->left = D->left;
			D->parent = D->right;
			D = nullptr;
			return true;
		}
		else {
			//The eldest son has a left kido!
			//find the first node on the left, that has no left
			int min = getMin(D->right->left);
			Node* miny = search(min);
			//Disjoiunt that miny
			if (miny->right != nullptr)
			{
				miny->parent->left = miny->right;
			}
			else {
				miny->parent->left = nullptr;
			}
			//Transplant miny
			miny->parent = D->parent;
			miny->left = D->left;
			miny->right = D->right;
			D = nullptr;
			return true;
		}

	}

}
bool BST::isempty()
{
	if (root == nullptr)
		return true;
	return false;
}