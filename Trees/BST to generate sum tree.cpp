#include <iostream>
#include<map>
#include <vector>
using namespace std;

struct Node {

	int data;
	int data2;
	Node* left = NULL;
	Node* right = NULL;
	Node* parent = NULL;

};


//void inOrderPrint(Node* node)
//{
//	while (node != NULL)
//	{
//		inOrderPrint(node->left);
//		cout << node->data2 << " ";
//		inOrderPrint(node->right);
//		return;
//	}
//
//	return;
//}

void inOrderSave(Node* node,vector<int> &saveTree)
{
	while (node != NULL)
	{
		inOrderSave(node->left, saveTree);
		saveTree.push_back(node->data);
		inOrderSave(node->right, saveTree);
		return;
	}

	return;
}

Node* getMax(Node* node)
{
	while (node->right != nullptr)
	{
		return (getMax(node->right));
	}
	return node;
}

Node* search(int val,Node* root)
{
	Node *node = root;

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

Node* presuccesor(int val,Node* root)
{
	Node *Me = search(val,root);
	if (!Me)
		return NULL;
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
		return y;
	}
	
	return NULL;
}

int main()
{
	int n, e;
	cin >> n;

	if (n == 0)
		return 0;

	Node* nodes = new Node[n];
	Node* nodes_mod = new Node[n];

	int x;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		nodes[i].data = x;
		nodes_mod[i].data = x;
	}
	cin >> e;
	char pos;
	int dad;
	int me;
	for (int i = 0; i < e; i++)
	{
		cin >> pos >> dad >> me;
		nodes[me].parent = &nodes[dad];
		nodes_mod[me].parent = &nodes_mod[dad];
		if (pos == 'L')
		{
			nodes[dad].left = &nodes[me];
			nodes_mod[dad].left = &nodes_mod[me];
		}
		else {
			nodes[dad].right = &nodes[me];
			nodes_mod[dad].right = &nodes_mod[me];
		}
	}
	vector<int> newArr;
	inOrderSave(&nodes[0], newArr);
	int size = newArr.size();
	int max = 0;
	for (int i = size-1; i >= 0; i--)
	{
		int temp = newArr[i];
		newArr[i] = max;
		max += temp;
	}
	
	for (int i=0; i<size; i++)
	{
		cout << newArr[i] << " ";
	}
	cout << endl;

	/*int max = 0;
	Node* temp = getMax(&nodes[0]);
	int last = temp->data;
	temp->data2 = max;

	for (int i = 1; i < n; i++)
	{
		temp = presuccesor(last, &nodes[0]);
		max += last;
		temp->data2 = max;
		last = temp->data;
	}
	inOrderPrint(&nodes[0]);*/

	//Modify the nodes_mod tree
	/*int max_old = 0;
	int last;

	Node* temp = getMax(&nodes[0]);
	Node* temp2 = getMax(&nodes_mod[0]);
	
	int max_new = temp->data;
	last = temp->data;
	
	for (int i = 1; i < n; i++)
	{
		temp = presuccesor(last, &nodes[0]);
		Node* temp3 = presuccesor(last, &nodes_mod[0]);

		temp2->data = max_old;
		temp2 = temp3;
		max_old = max_new;
		max_new += temp->data;
		last = temp->data;
	}
	temp2->data = max_old;*/
	//inOrderPrint(&nodes_mod[0]);
	return 0;
}