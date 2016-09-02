#include <iostream>


using namespace std;

struct BSTNode {

	int key;
	BSTNode *left;
	BSTNode *right;
};


class BST {

private:

public:

	BSTNode *root;

	BST();
	bool insert(BSTNode *input_node);
	void inOrder_Print(BSTNode *input_node);
	//bo0l remove(int key);
	BSTNode* lookup_by_key(int key);
};

BST::BST() {

	this->root = NULL;
}

void BST::inOrder_Print(BSTNode *input_node) {

	if (input_node == NULL)
	{
		return;
	}

	inOrder_Print(input_node->left);
	cout << input_node->key << endl;
	inOrder_Print(input_node->right);
}

bool BST::insert(BSTNode *input_node) { // Inserts supplied node into tree at appropriate location.
										// Returns true is insertion successful and false otherwise.
	if (this->root == NULL)
	{
		this->root = input_node;
		return true;
	}

	BSTNode *temp_traversal = this->root;

	while (temp_traversal != NULL) 
	{
		if (temp_traversal->key >= input_node->key) 
		{

			if (temp_traversal->left == NULL) 
			{
				temp_traversal->left = input_node;
				return true;
			}
			else 
			{
				temp_traversal = temp_traversal->left;
			}
		}
		else if (temp_traversal->key < input_node->key) 
		{
			if (temp_traversal->right == NULL) 
			{
				temp_traversal->right = input_node;
				return true;
			}
			else 
			{
				temp_traversal = temp_traversal->right;
			}
		}
	}


	return false;
}

BSTNode* BST::lookup_by_key(int key) {

	if (this->root == NULL) // Tree is empty.
	{
		return NULL;
	}

	BSTNode *temp_node = this->root;

	while (temp_node != NULL)
	{
		if (temp_node->key == key) // Key found.
		{
			return temp_node;
		}
		else if (temp_node->key >= key)
		{
			temp_node = temp_node->left;
		}
		else if (temp_node->key < key)
		{
			temp_node = temp_node->right;
		}
	}

	cout << "Key is not in tree.\n";
	return NULL;
}



int main (int argc, char *argv[]) {


	BST *tree = new BST();

	BSTNode *node0 = new BSTNode();
	BSTNode *node1 = new BSTNode();
	BSTNode *node2 = new BSTNode();
	BSTNode *node3 = new BSTNode();
	BSTNode *node4 = new BSTNode();
	BSTNode *node5 = new BSTNode();
	node0->key = 10;
	node1->key = 0;
	node2->key = 20;
	node3->key = -100;
	node4->key = 10;
	node5->key = 300;

	tree->insert(node0);
	tree->insert(node1);
	tree->insert(node2);
	tree->insert(node3);
	tree->insert(node4);
	tree->insert(node5);

	tree->inOrder_Print(tree->root);

	node0 = tree->lookup_by_key(-100);
	cout << "key:" << node0->key << endl;

	node0 = tree->lookup_by_key(300);
	cout << "key:" << node0->key << endl;

	
	 

	return 0;
}