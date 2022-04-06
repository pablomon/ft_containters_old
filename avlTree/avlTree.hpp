#if !defined(AVL_HPP)
#define AVL_HPP

#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>

#include "avlNode.hpp"
#include "avlIterator.hpp"
#include "../utils/pair.hpp"

template <typename K, typename V>
class AVLTree
{
public:
	typedef AVLNode<K,V>	node_type;
	typedef node_type		*node_pointer;
	typedef avlIterator<node_type, ft::pair<K,V> >	iterator;
	
	
	node_pointer root = NULL;

private:
	void balanceAtNode(AVLNode<K, V> *n)
	{
		int bal = n->getBalance();
		if (bal > 1)
		{
			if (n->left->getBalance() < 0)
				rotateLeft(n->left);
			rotateRight(n);
		}
		else if (bal < -1)
		{
			if (n->right->getBalance() > 0)
				rotateRight(n->right);
			rotateLeft(n);
		}
	}
	void rotateLeft(AVLNode<K, V> *n)
	{
		enum
		{
			left,
			right
		} side;
		AVLNode<K, V> *p = n->parent;
		if (p != NULL && p->left == n)
			side = left;
		else
			side = right;
		AVLNode<K, V> *temp = n->right;
		n->setRight(temp->left);
		temp->setLeft(n);
		if (p == NULL)
			setRoot(temp);
		else if (side == left)
			p->setLeft(temp);
		else
			p->setRight(temp);
	}
	void rotateRight(AVLNode<K, V> *n)
	{
		enum
		{
			left,
			right
		} side;
		AVLNode<K, V> *p = n->parent;
		if (p != NULL && p->left == n)
			side = left;
		else
			side = right;
		AVLNode<K, V> *temp = n->left;
		n->setLeft(temp->right);
		temp->setRight(n);
		if (p == NULL)
			setRoot(temp);
		else if (side == left)
			p->setLeft(temp);
		else
			p->setRight(temp);
	}
	void setRoot(AVLNode<K, V> *n)
	{
		root = n;
		if (root != NULL)
			root->removeParent();
	}

	AVLNode<K, V> *findNode(K key)
	{
		AVLNode<K, V> *temp = root;
		while (temp != NULL)
		{
			if (key == temp->content.first)
				break;
			else if (key < temp->content.first)
				temp = temp->left;
			else
				temp = temp->right;
		}
		return temp;
	}

	// debug
	void printSubtree(AVLNode<K, V> *subtree, int depth, int level, bool first)
	{
		if (depth > 0)
		{
			if (subtree == NULL)
			{
				printSubtree(subtree, depth - 1, level, first);
				printSubtree(subtree, depth - 1, level, false);
			}
			else
			{
				printSubtree(subtree->left, depth - 1, level, first);
				printSubtree(subtree->right, depth - 1, level, false);
			}
		}
		else if (subtree == NULL)
			std::cout << std::setw((first) ? spacing(level) / 2 : spacing(level)) << "-";
		else
			std::cout << std::setw((first) ? spacing(level) / 2 : spacing(level)) << subtree->content.first;
	}
	int spacing(int level)
	{
		int result = 2;
		for (int i = 0; i < level; i++)
			result += result;
		return result;
	}

public:
	AVLTree() : root(NULL) {}
	AVLTree(ft::pair<K,V> pair) {	root = new AVLNode<K, V>(pair);	}

	int getHeight() { return root->getHeight(); }
	bool insert(ft::pair<K,V> pair)
	{
		if (root == NULL)
			root = new AVLNode<K, V>(pair);
		else
		{
			AVLNode<K, V> *added_node = NULL;
			AVLNode<K, V> *temp = root;
			while (temp != NULL && added_node == NULL)
			{
				if (pair.first < temp->content.first)
				{
					if (temp->left == NULL)
						added_node = temp->setLeft(new AVLNode<K, V>(pair));
					else
						temp = temp->left;
				}
				else if (pair.first > temp->content.first)
				{
					if (temp->right == NULL)
						added_node = temp->setRight(new AVLNode<K, V>(pair));
					else
						temp = temp->right;
				}
				else
					return false;
			}

			temp = added_node;
			while (temp != NULL)
			{
				temp->updateHeight();
				balanceAtNode(temp);
				temp = temp->parent;
			}
		}
		return true;
	}
	bool remove(K key)
	{
		AVLNode<K, V> *toBeRemoved = findNode(key);
		if (toBeRemoved == NULL)
			return false;
		enum
		{
			left,
			right
		} side;
		AVLNode<K, V> *p = toBeRemoved->parent;
		if (p != NULL &&
			p->left == toBeRemoved)
			side = left;
		else
			side = right;
		if (toBeRemoved->left == NULL)
			if (toBeRemoved->right == NULL)
			{
				if (p == NULL)
				{
					setRoot(NULL);
					delete toBeRemoved;
				}
				else
				{
					if (side == left)
						p->setLeft(NULL);
					else
						p->setRight(NULL);
					delete toBeRemoved;
					p->updateHeight();
					balanceAtNode(p);
				}
			}
			else
			{
				if (p == NULL)
				{
					setRoot(toBeRemoved->right);
					delete toBeRemoved;
				}
				else
				{
					if (side == left)
						p->setLeft(toBeRemoved->right);
					else
						p->setRight(toBeRemoved->right);
					delete toBeRemoved;
					p->updateHeight();
					balanceAtNode(p);
				}
			}
		else if (toBeRemoved->right == NULL)
		{
			if (p == NULL)
			{
				setRoot(toBeRemoved->left);
				delete toBeRemoved;
			}
			else
			{
				if (side == left)
					p->setLeft(toBeRemoved->left);
				else
					p->setRight(toBeRemoved->left);
				delete toBeRemoved;
				p->updateHeight();
				balanceAtNode(p);
			}
		}
		else
		{
			AVLNode<K, V> *replacement;
			AVLNode<K, V> *replacement_parent;
			AVLNode<K, V> *temp_node;
			int bal = toBeRemoved->getBalance();
			if (bal > 0)
			{
				if (toBeRemoved->left->right == NULL)
				{
					replacement = toBeRemoved->left;
					replacement->setRight(toBeRemoved->right);
					temp_node = replacement;
				}
				else
				{
					replacement = toBeRemoved->left->right;
					while (replacement->right != NULL)
						replacement = replacement->right;
					replacement_parent = replacement->parent;
					replacement_parent->setRight(replacement->left);
					temp_node = replacement_parent;
					replacement->setLeft(toBeRemoved->left);
					replacement->setRight(toBeRemoved->right);
				}
			}
			else if (toBeRemoved->right->left == NULL)
			{
				replacement = toBeRemoved->right;
				replacement->setLeft(toBeRemoved->left);
				temp_node = replacement;
			}
			else
			{
				replacement = toBeRemoved->right->left;
				while (replacement->left != NULL)
					replacement = replacement->left;
				
				replacement_parent = replacement->parent;
				replacement_parent->setLeft(replacement->right);
				temp_node = replacement_parent;
				replacement->setLeft(toBeRemoved->left);
				replacement->setRight(toBeRemoved->right);
			}
			if (p == NULL)
				setRoot(replacement);
			else if (side == left)
				p->setLeft(replacement);
			else
				p->setRight(replacement);
			delete toBeRemoved;
			balanceAtNode(temp_node);
		}
		return true;
	}
	V getValue(K key)
	{
		AVLNode<K,V> *n = findNode(key);
		if (n == NULL)
			return 0;
		return n->content.second;
	}
	node_pointer getFirst()
	{
		if (root == NULL)
			return NULL;
		node_pointer node = root;
		while(node->left != NULL)
			node = node->left;
		return node;
	}

	iterator begin()
	{
		iterator it(root, getFirst());
		return it;
	}

	node_pointer getLast()
	{
		if (root == NULL)
			return NULL;
		node_pointer node = root;
		while(node->right != NULL)
			node = node->right;
		return node;
	}
	iterator end()
	{
		iterator it(root, getLast() + 1);
		return it;
	}

	// debug
	void print()
	{
		if (root == NULL)
		{
			std::cout << "Empty" << std::endl;
			return;
		}
		int max = root->getHeight();
		for (int depth = 0; depth <= max; depth++)
		{
			printSubtree(root, depth, max - depth + 1, true);
			std::cout << std::endl;
		}
	}
};

#endif // AVL_HPP
