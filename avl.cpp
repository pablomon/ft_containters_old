#include<iostream>
#include<cstdio>
#include<sstream>
#include<sstream>
#include<tgmath.h>
#include<algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

#define yellow "\033[0;33m"
#define blue "\033[0;36m"
#define reset "\033[0m"

#define X " "
#define SEP 4

template < typename T >
std::string sstr( T val )
{
    std::ostringstream sstr;
    // fold expression
    ( sstr << std::dec << val );
    return sstr.str();
}

template < typename K, typename V >
class avl_tree {
	public:
	int key;
	int val;
	avl_tree *left;
	avl_tree *right;

	public:
	avl_tree() {
		left = NULL;
		right = NULL;
	}
	int height const (avl_tree *root) {
		int h = 0;
		if (root != NULL) {
			int l_height = height(root->left);
			int r_height = height(root->right);
			int max_height = std::max(l_height, r_height);
			h = max_height + 1;
		}
		return h;
	}
	int difference const (avl_tree *root) {
		if (root == NULL)
			return 0;
		int l_height = height(root->left);
		int r_height = height(root->right);
		int b_factor = l_height - r_height;
		return b_factor;
	}
	avl_tree *rr_rotat(avl_tree *root) {
		avl_tree *t;
		t = root->right;
		root->right = t->left;
		t->left = root;
		std::cout<<"Right-Right Rotation";
		return t;
	}
	avl_tree *ll_rotat(avl_tree *root) {
		avl_tree *t;
		t = root->left;
		root->left = t->right;
		t->right = root;
		std::cout<<"Left-Left Rotation";
		return t;
	}
	avl_tree *lr_rotat(avl_tree *root) {
		avl_tree *t;
		t = root->left;
		root->left = rr_rotat(t);
		std::cout<<"Left-Right Rotation";
		return ll_rotat(root);
	}
	avl_tree *rl_rotate(avl_tree *root) {
		avl_tree *t;
		t = root->right;
		root->right = ll_rotat(t);
		std::cout<<"Right-Left Rotation";
		return rr_rotat(root);
	}
	avl_tree *balance(avl_tree *root) {
		int bal_factor = difference(root);
		if (bal_factor > 1) {
			if (difference(root->left) > 0)
				root = ll_rotat(root);
			else
				root = lr_rotat(root);
		} else if (bal_factor < -1) {
			if (difference(root->right) > 0)
				root = rl_rotate(root);
			else
				root = rr_rotat(root);
		}
		return root;
	}
	private:
	avl_tree *add_node(avl_tree *parent, K key, V val) {
		if (parent == NULL) {
			parent = new avl_tree;
			parent->key = key;
			parent->val = val;
			return parent;
		} else if (key< parent->key) {
			parent->left = add_node(parent->left, key, val);
			parent = balance(parent);
		} else if (key >= parent->key) {
			parent->right = add_node(parent->right, key, val);
			parent = balance(parent);
		} 
		return parent;
	}
	public:
	avl_tree *insert(avl_tree *parent, K key, V val) {
		avl_tree *t = find(parent, key);
		if (t != NULL)
			return t;
		t = add_node(parent, key, val);
		return t;
	}

	static void show(avl_tree *root, int l) {
		int i;
		if (root != NULL) {
			show(root->right, l+ 1);
			std::cout<<" ";
			for (i = 0; i < l; i++)
				std::cout << " ";
				std::cout << root->key;
				show(root->left, l + 1);
		}
	}
	static void inorder(avl_tree *root) {
		if (root == NULL)
			return;
		inorder(root->left);
		std::cout << root->key << " ";
		inorder(root->right);
	}
	static void preorder(avl_tree *root) {
		if (root == NULL)
			return;
		std::cout << root->key << " ";
		preorder(root->left);
		preorder(root->right);
	}
	static void postorder(avl_tree *root) {
		if (root == NULL)
			return;
		postorder(root ->left);
		postorder(root ->right);
		std::cout << root->key << " ";
	}
	static avl_tree* find(avl_tree *root, K key)
	{
		if (root == NULL)
			return NULL;
		if (root->key == key)
			return root;
		else if (key < root->key && root->left)
			return find(root->left, key);
		else if (key > root->key && root->right)
			return find(root->right, key);
		return NULL;
	}

	// Printing
	static void app_seps(std::string &str, float num)
	{
		for (size_t i = 0; i < num; i++)
			str.append(X);
	}
	static void print_node(avl_tree *node, int level, std::string *strings, int height)
	{
		int trail = std::pow(height - level, 2);
		strings[level].append(sstr(node->key));
		app_seps(strings[level], trail);
		if (node->left)
			print_node(node->left, level + 1, strings, height);
		if (node->right)
			print_node(node->right, level + 1, strings, height);
	}

	/* Given a non-empty binary search tree,
	return the node with minimum key value
	found in that tree. Note that the entire
	tree does not need to be searched. */
	avl_tree * minValueNode(avl_tree* node)
	{
		avl_tree* current = node;
	
		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;
	
		return current;
	}

	avl_tree* deleteNode(avl_tree *root, K key)
	{
		// STEP 1: standard bst delete
		if (root == NULL)
			return root;
		// If the key to be deleted is smaller
		// than the root's key, then it lies
		// in left subtree
		if ( key < root->key )
			root->left = deleteNode(root->right, key);
		// If the key to be deleted is greater
		// than the root's key, then it lies
		// in right subtree
		else if( key > root->key )
			root->right = deleteNode(root->right, key);
		// if key is same as root's key, then
   		// This is the node to be deleted
		else
		{
			// node with only one child or no child
			if( root->left == NULL || root->right == NULL )
			{
				avl_tree *temp = root->left ?
							root->left :
							root->right;
	
				// No child case
				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else // One child case
				*root = *temp; // Copy the contents of
							// the non-empty child
				free(temp);
			}
			else
			{
				// node with two children: Get the inorder
				// successor (smallest in the right subtree)
				avl_tree* temp = minValueNode(root->right);
	
				// Copy the inorder successor's
				// data to this node
				root->key = temp->key;
	
				// Delete the inorder successor
				root->right = deleteNode(root->right, temp->key);
			}
		}
		root = balance(root);
		return root;
	}

	static void print(avl_tree *root)
	{
		int h = avl_tree::height(root);
		std::string strings[h];
		std::cout << "height = " << h << std::endl;

		for (size_t i = 0; i < h; i++)
			app_seps(strings[i], std::pow(h - i - 1.0f, 2));
		print_node(root, 0, strings, h);

		for (size_t i = 0; i < h; i++)
			std::cout << strings[i] << std::endl;
	}
};

int main() {
   	int c, key;
   	avl_tree<int, int> avl;
	avl_tree<int, int> *root = NULL;

	srand (time(NULL));
	int keys[20];
	std::vector<int> nonrepkeys;
	while (nonrepkeys.size() != 20)
	{
		int k = rand() % 99;
		bool exists = false;
		for (size_t i = 0; i < nonrepkeys.size(); i++)
		{
			if (nonrepkeys[i] == k)
				exists = true;
		}
		if (!exists)
		{
			nonrepkeys.push_back(k);	
			root = avl.insert(root, k, k + 1);
		}
	}

	avl_tree<int,int>::print(root);
   	while (1) {
	   	std::cout << "\n";
		std::cout << "1.Insert Element into the tree" << std::endl;
		std::cout << "2.print Balanced AVL Tree" << std::endl;
		std::cout << "3.search" << std::endl;
		std::cout << "4.delete" << std::endl;
		std::cout << "Enter your Choice: ";
		std::cin >> c;
		switch (c) {
			case 1:
			{
				std::cout << "Enter key: ";
				std::cin >> key;
				int v;
				std::cout << "Enter value:";
				std::cin >> v;
				avl_tree<int,int> *t = avl.insert(root, key, v);
				avl_tree<int,int>::print(root);		
			}
			break;
			case 2:
				if (root == NULL) {
				std::cout << "Tree is Empty" << std::endl;
				continue;
				}
				std::cout << "Balanced AVL Tree:" << std::endl;
				// avl.show(root, 1);
				avl_tree<int,int>::print(root);		
				std::cout<<std::endl;
			break;
			case 3:
			{
				std::cout << "Enter key to search for: " << std::endl;
				std::cin >> key;
				avl_tree<int,int> *f = NULL;
				f = root->find(root, key);
				if (f == NULL)
					std::cout << "Not found." << std::endl;
				else
					std::cout << "Found value = " << f->val;
			}
			break;
			case 4:
			{
				std::cout << "Enter key to delete: " << std::endl;
				std::cin >> key;
				avl_tree<int,int> *f = root->deleteNode(root, key);
				if (f == NULL)
					std::cout << "Not found." << std::endl;
				else
				{
					std::cout << "Deleted" << std::endl;
					avl_tree<int,int>::print(root);		
				}
			}
			break;

			// case 3:
			// 	std::cout << "Inorder Traversal:" << std::endl;
			// 	avl.inorder(r);
			// 	std::cout << std::endl;
			// break;
			// case 4:
			// 	std::cout << "Preorder Traversal:" << std::endl;
			// 	avl.preorder(r);
			// 	std::cout << std::endl;
			// break;
			// case 5:
			// 	std::cout << "Postorder Traversal:" << std::endl;
			// 	avl.postorder(r);
			// 	std::cout << std::endl;
			// break;
			// case 6:
			// 	exit(1);
			// case 7:
			// 	avl_tree::print(r);
			default:
				std::cout << "Wrong Choice" << std::endl;
		}	
	}			
   	return 0;
}