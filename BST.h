#ifndef BST.H
#define BST_H


struct Node {
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
	int data;
};

class BST
{
private:
	
	int getMin(Node* node = nullptr);
	int getMax(Node* node = nullptr);
	void InOrderTraversal(Node* node);
	void PreOrderTraversal(Node* node);
	void PostOrderTraversal(Node* node);
	void Transplant();
public:
	Node* root = nullptr;
	BST();
	void insert(int val);
	void callInOrderTraversal();
	void callPreOrderTraversal();
	void callPostOrderTraversal();
	int minimum();
	int maximum();
	Node* search(int val);
	int succesor(int val);
	int presuccesor(int val);
	bool deleteNode(int val);
	bool isempty();

};

#endif