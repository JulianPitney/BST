#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

struct BSTNode {

	int key;
	BSTNode *left = NULL;
	BSTNode *right = NULL;
	int balance_factor = 0;
};

struct lookup_pkg {

	BSTNode *node;
	BSTNode *parent;
};

struct lookup_pkg2 {

	BSTNode *node;
	BSTNode *parent;
	BSTNode *grandparent;
	BSTNode *greatgrandparent;
};

struct balancing_access_path_pkg {

	BSTNode* node;
	bool path_wentleft = false;

};


class BST {

private:

public:

	BSTNode *root;

	BST();
	bool insert(BSTNode *input_node); // insert(), lookup_by_key() and lookup_by_addr() all perform the "find node" function. Should reduce this to 1 function.
	void inOrder_Print(BSTNode *input_node);
	bool remove(int key); bool twoChild_useRight_subTree = true; // This bool is to keep from skewing the tree with arbitary node removals.
	lookup_pkg* lookup_by_key(int key); // Should modify this to use lookup_pkg2 and perform like lookup_by_addr
	BSTNode* find_min_node(BSTNode *subtree_root);
	BSTNode* find_max_node(BSTNode *subtree_root);
	int find_tree_height(BSTNode *subtree_root);
	lookup_pkg2* lookup_by_addr(BSTNode *subtree_root); // This returns lookup_pkg2 which gives parent and grandparent nodes
	bool check_tree_balance(BSTNode *subtree_root); // Returns true if tree is balanced, false otherwise.
	void balance_subtree(BSTNode *balance_NodeA, BSTNode *balance_NodeB, BSTNode *balance_NodeC);
};

BST::BST() {

	this->root = NULL;
}

void BST::inOrder_Print(BSTNode *input_node) {

	if (input_node == NULL) // Tree is empty
	{
		return;
	}

	inOrder_Print(input_node->left); 
	cout << input_node->key << endl;
	inOrder_Print(input_node->right);
}


bool BST::insert(BSTNode *input_node) { // Inserts supplied node into tree at appropriate location.
										// Also updates balance factor of each node in insertion path.
										// Detects if subtrees have become unbalanced by checking balance factor after each node's update.
									
	if (this->root == NULL)
	{
		this->root = input_node;
		return true;
	}

	BSTNode *temp_traversal = this->root;
	vector<balancing_access_path_pkg> node_vec;

	BSTNode *imbalanced_nodeA = NULL;
	int imbalanced_nodeA_loc;
	BSTNode *imbalanced_nodeB = NULL;
	BSTNode *imbalanced_nodeC = NULL;

	while (temp_traversal != NULL)
	{
		if (temp_traversal->key >= input_node->key)
		{
			balancing_access_path_pkg temp_pkg;
			temp_pkg.node = temp_traversal;
			node_vec.push_back(temp_pkg);

			if (temp_traversal->left == NULL)
			{
				node_vec.at(node_vec.size() - 1).node->balance_factor += 1;

				if (temp_traversal->right == NULL)
				{
					for (unsigned int i = 0; i < node_vec.size() - 1; i++)
					{

						if (node_vec.at(i).path_wentleft == true)
						{
							node_vec.at(i).node->balance_factor += 1;
						}
						else
						{
							node_vec.at(i).node->balance_factor -= 1;
						}
					}
				}
				
				for (unsigned int i = 0; i < node_vec.size() - 1; i++)
				{
					if (node_vec.at(i).node->balance_factor == 2 || node_vec.at(i).node->balance_factor == -2)
					{
						imbalanced_nodeA = node_vec.at(i).node;
						imbalanced_nodeA_loc = i;
					}
				}

				if (imbalanced_nodeA != NULL)
				{
					if (imbalanced_nodeA == node_vec.at(node_vec.size() - 2).node)
					{
						imbalanced_nodeB = node_vec.at(node_vec.size() - 1).node;
						imbalanced_nodeC = input_node;

						temp_traversal->left = input_node;
						this->balance_subtree(imbalanced_nodeA, imbalanced_nodeB, imbalanced_nodeC);
						return true;
					}
					else
					{
						imbalanced_nodeB = node_vec.at(imbalanced_nodeA_loc + 1).node;
						imbalanced_nodeC = node_vec.at(imbalanced_nodeA_loc + 2).node;

						temp_traversal->left = input_node;
						this->balance_subtree(imbalanced_nodeA, imbalanced_nodeB, imbalanced_nodeC);
						return true;
					}
				}

				temp_traversal->left = input_node;				
				return true;
			}
			else
			{
				node_vec.at(node_vec.size() - 1).path_wentleft = true;
				temp_traversal = temp_traversal->left;
			}
		}
		else if (temp_traversal->key < input_node->key)
		{
			balancing_access_path_pkg temp_pkg;
			temp_pkg.node = temp_traversal;
			node_vec.push_back(temp_pkg);

			if (temp_traversal->right == NULL)
			{
				node_vec.at(node_vec.size() - 1).node->balance_factor -= 1;

				if (temp_traversal->left == NULL) // 
				{
					for (unsigned int i = 0; i < node_vec.size() - 1; i++)
					{
						if (node_vec.at(i).path_wentleft == true)
						{
							node_vec.at(i).node->balance_factor += 1;
						}
						else
						{
							node_vec.at(i).node->balance_factor -= 1;
						}
					}
				}

				for (unsigned int i = 0; i < node_vec.size() - 1; i++)
				{
					if (node_vec.at(i).node->balance_factor == 2 || node_vec.at(i).node->balance_factor == -2)
					{
						imbalanced_nodeA = node_vec.at(i).node;
						imbalanced_nodeA_loc = i;
					}
				}

				if (imbalanced_nodeA != NULL)
				{
					if (imbalanced_nodeA == node_vec.at(node_vec.size() - 2).node)
					{
						imbalanced_nodeB = node_vec.at(node_vec.size() - 1).node;
						imbalanced_nodeC = input_node;

						temp_traversal->right = input_node;
						this->balance_subtree(imbalanced_nodeA, imbalanced_nodeB, imbalanced_nodeC);
						return true;
					}
					else
					{
						imbalanced_nodeB = node_vec.at(imbalanced_nodeA_loc + 1).node;
						imbalanced_nodeC = node_vec.at(imbalanced_nodeA_loc + 2).node;

						temp_traversal->right = input_node;
						this->balance_subtree(imbalanced_nodeA, imbalanced_nodeB, imbalanced_nodeC);
						return true;
					}
				}

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

void BST::balance_subtree(BSTNode *balance_NodeA, BSTNode *balance_NodeB, BSTNode *balance_NodeC) {

	BSTNode *temp;


	if (balance_NodeA->balance_factor == 2) // Case 1 or 2.
	{
		if (balance_NodeB->left == balance_NodeC) // Case 1.
		{
			temp = balance_NodeB->right;
			balance_NodeB->right = balance_NodeA;
			balance_NodeA->left = temp;

			if (balance_NodeA == this->root)
			{
				this->root = balance_NodeB;
			}
		}
		else if (balance_NodeB->right == balance_NodeC) // Case 2.
		{
			balance_NodeA->left = balance_NodeC;
			temp = balance_NodeC->left;
			balance_NodeC->left = balance_NodeB;
			balance_NodeB->right = temp;

			// now we have case 1
			temp = balance_NodeC->right;
			balance_NodeC->right = balance_NodeA;
			balance_NodeA->left = temp;

			if (balance_NodeA == this->root)
			{
				this->root = balance_NodeC;
			}
		}
		else // Something is very wrong.
		{
			cout << "Something bad happened :(" << endl;
		}
	}
	else if (balance_NodeA->balance_factor == -2) // Case 3 or 4.
	{
		if (balance_NodeB->right == balance_NodeC) // Case 3.
		{
			temp = balance_NodeB->left;
			balance_NodeB->left = balance_NodeA;
			balance_NodeA->right = temp;

			if (balance_NodeA == this->root)
			{
				this->root = balance_NodeB;
			}
		}
		else if (balance_NodeB->left == balance_NodeC) // Case 4.
		{
			balance_NodeA->right = balance_NodeC;
			temp = balance_NodeC->right;
			balance_NodeC->right = balance_NodeB;
			balance_NodeB->left = temp;

			// Now we have case 3.
			temp = balance_NodeC->left;
			balance_NodeC->left = balance_NodeA;
			balance_NodeA->right = temp;

			if (balance_NodeA == this->root)
			{
				this->root = balance_NodeC;
			}
		}
		else // Something is very wrong.
		{
			cout << "Something bad happened" << endl;
		}
	}
	else // Something is very wrong.
	{
	
	}

}

lookup_pkg* BST::lookup_by_key(int key) {  // Returns ptr to pkg containing ptr to first node found with key == key. Returned pkg
											// also contains ptr to parent of returned node. Parent will be null if first node found is root.
											// Object that lookup_pkg* points to has been dynamically allocated and needs cleanup later.

	if (this->root == NULL) // Tree is empty.
	{
		return NULL;
	}

	lookup_pkg *output_pkg = new lookup_pkg;
	output_pkg->node = this->root;


	if (output_pkg->node->key == key) // Key is in root
	{
		output_pkg->parent = NULL;
		return output_pkg;
	} 


	while (output_pkg->node != NULL)
	{
		if (output_pkg->node->key == key) // Key found.
		{
			return output_pkg;
		}
		else if (output_pkg->node->key >= key)
		{
			output_pkg->parent = output_pkg->node;
			output_pkg->node = output_pkg->node->left;
		}
		else if (output_pkg->node->key < key)
		{
			output_pkg->parent = output_pkg->node;
			output_pkg->node = output_pkg->node->right;
		}
	}

	cout << "Key is not in tree.\n";
	return NULL;
}

BSTNode* BST::find_min_node(BSTNode *subtree_root) { // Returns node with lowest value in subtree.

	if (subtree_root == NULL) // Tree is empty.
	{
		return NULL;
	}
	
	while (subtree_root->left != NULL)
	{
		subtree_root = subtree_root->left;
	}

	return subtree_root;
}

BSTNode* BST::find_max_node(BSTNode *subtree_root) { // Returns node with highest value in subtree.

	if (subtree_root == NULL) // Tree us empty.
	{
		return NULL;
	}

	while (subtree_root->right != NULL)
	{
		subtree_root = subtree_root->right;
	}

	return subtree_root;
}

int BST::find_tree_height(BSTNode *subtree_root) { // Returns height of tree where subtree_root is root of tree. Returns -1 if tree is empty.
	
	if (subtree_root == NULL) // Tree is empty
	{
		return -1;
	}
	
	int left_height = this->find_tree_height(subtree_root->left);
	int right_height = this->find_tree_height(subtree_root->right);

	if (left_height > right_height)
	{
		return left_height + 1;
	}
	else
	{
		return right_height + 1;
	}
}

lookup_pkg2* BST::lookup_by_addr(BSTNode *most_recently_added_node) { // Returns output_pkg2 containing stuff. Returned values
																		  // need to be checked for validity.

	// Approach i'm trying is find node by memory address (because if we lookup by key and there are duplicate keys
	// then we will not return the most recently added node). If we balance an AVL tree everytime a node is inserted
	// then we can assume that the only imbalance is at the location where the most recently inserted node is. Therefore
	// if we find the most recently inserted node and check the balance factor of it's parent and grandparent we are 
	// guaranteed to find the imbalance. This approach allows us to avoid checking the entire tree for imbalances,
	// thus saving cycles. If we integrate this approach with the insert method than we only have to lookup
	// the position of the node once (for insertion) and then check it's parent and grandparent node for balance (which
	// also lowers execution time of find_tree_height since it only needs to find the height of very small subtrees).
	
	lookup_pkg2 *output_pkg = new lookup_pkg2;
	output_pkg->node = this->root;
	output_pkg->parent = NULL;
	output_pkg->grandparent = NULL;
	output_pkg->greatgrandparent = NULL;

	while (output_pkg->node != NULL)
	{
		if (output_pkg->node == most_recently_added_node) // Tree is still balanced
		{
			return output_pkg;
		}
		else if (output_pkg->node->key >= most_recently_added_node->key)
		{
			output_pkg->greatgrandparent = output_pkg->grandparent;
			output_pkg->grandparent = output_pkg->parent;
			output_pkg->parent = output_pkg->node;
			output_pkg->node = output_pkg->node->left;
		}
		else if (output_pkg->node->key < most_recently_added_node->key)
		{
			output_pkg->greatgrandparent = output_pkg->grandparent;
			output_pkg->grandparent = output_pkg->parent;
			output_pkg->parent = output_pkg->node;
			output_pkg->node = output_pkg->node->right;
		}
	}


	cout << "Key is not in tree.\n";
	return NULL;

}

bool BST::check_tree_balance(BSTNode *subtree_root) { // This function returns true if tree rooted at subtree_root is balanced, false otherwise.
 
	return ( 2 > abs(this->find_tree_height(subtree_root->left) - this->find_tree_height(subtree_root->right)));
}

bool BST::remove(int key) { // Removes arbitrary node from tree 

	lookup_pkg *remove_node = this->lookup_by_key(key);
	
	if (remove_node == NULL) // lookup_by_key returned NULL (should mean that tree is empty).
	{
		return false; 
	}
	else if (remove_node->node == this->root && this->root->left == NULL && this->root->right == NULL) // Only 1 node in tree.
	{
		delete this->root;
		this->root = NULL;
		return true;
	}
	else if (remove_node->node->left == NULL && remove_node->node->right == NULL) // Node has no children and is not root node.
	{
		if (remove_node->parent->left == remove_node->node) 
		{
			remove_node->parent->left = NULL;
			delete remove_node->node;
		}
		else 
		{
			remove_node->parent->right = NULL;
			delete remove_node->node;
		}
	}
	else if (remove_node->node->left != NULL && remove_node->node->right == NULL) // Node has only left child.
	{
		if (remove_node->node == this->root) // Node is root.
		{
			this->root = this->root->left;
			delete remove_node->node;
			delete remove_node;
			return true;
		}
		else // Node is not root.
		{
			if (remove_node->parent->left == remove_node->node) // Node is left child.
			{
				remove_node->parent->left = remove_node->node->left;
				delete remove_node->node;
				delete remove_node;
				return true;
			}
			else // Node is right child.
			{
				remove_node->parent->right = remove_node->node->left;
				delete remove_node->node;
				delete remove_node;
				return true;
			}
		}
	}
	else if (remove_node->node->left == NULL && remove_node->node->right != NULL) // Node has only right child.
	{
		if (remove_node->node == this->root) // Node is root.
		{
			this->root = this->root->right;
			delete remove_node->node;
			delete remove_node;
			return true;
		}
		else // Node is not root.
		{
			if (remove_node->parent->left == remove_node->node) // Node is left child.
			{
				remove_node->parent->left = remove_node->node->right;
				delete remove_node->node;
				delete remove_node;
				return true;
			}
			else // Node is right child.
			{
				remove_node->parent->right = remove_node->node->right;
				delete remove_node->node;
				delete remove_node;
				return true;
			}
		}
	}
	else if (remove_node->node->left != NULL && remove_node->node->right != NULL) // Node has 2 children.
	{
			if (this->twoChild_useRight_subTree == true)
			{
				BSTNode *temp_lowest = this->find_min_node(this->root->right);
				int temp_key = temp_lowest->key;
				this->remove(temp_lowest->key);
				this->root->key = temp_key;
				this->twoChild_useRight_subTree = false;
				return true;
			}
			else
			{
				BSTNode *temp_highest = this->find_max_node(this->root->left);
				int temp_key = temp_highest->key;
				this->remove(temp_highest->key);
				this->root->key = temp_key;
				this->twoChild_useRight_subTree = true;
				return true;
			}
		
	}

	



	return false;

}
int main(int argc, char *argv[]) {


	BST *tree = new BST();

	BSTNode *node0 = new BSTNode();
	BSTNode *node1 = new BSTNode();
	BSTNode *node2 = new BSTNode();
	BSTNode *node3 = new BSTNode();
	BSTNode *node4 = new BSTNode();
	BSTNode *node5 = new BSTNode();
	node0->key = 0;
	node1->key = -15;
	node2->key = -10;
	node3->key = 5;
	node4->key = 25;
	node5->key = 100;

	tree->insert(node0);
	tree->insert(node1);
	tree->insert(node2);


	tree->inOrder_Print(tree->root);
	

	// balancing code seems to be working but needs more testing. Also haven't looked at how the rebalancing code affects 
	// the accuracy of the balance factor in each node, so that needs to be looked at and probably fixed.

	return 0;
}
