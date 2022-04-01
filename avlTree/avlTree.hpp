#if !defined(AVL_HPP)
#define AVL_HPP

#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>

#include "avlNode.hpp"

template <typename K, typename V>
class AVLTree
{
private:
	AVLNode<K, V> *root;

private:
	void balanceAtNode(AVLNode<K, V> *n)
	{
		int bal = n->getBalance();
		if (bal > 1)
		{
			if (n->getLeftChild()->getBalance() < 0)
				rotateLeft(n->getLeftChild());
			rotateRight(n);
		}
		else if (bal < -1)
		{
			if (n->getRightChild()->getBalance() > 0)
				rotateRight(n->getRightChild());
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
		AVLNode<K, V> *p = n->getParent();
		if (p != NULL && p->getLeftChild() == n)
			side = left;
		else
			side = right;
		AVLNode<K, V> *temp = n->getRightChild();
		n->setRightChild(temp->getLeftChild());
		temp->setLeftChild(n);
		if (p == NULL)
			setRoot(temp);
		else if (side == left)
			p->setLeftChild(temp);
		else
			p->setRightChild(temp);
	}

	void rotateRight(AVLNode<K, V> *n)
	{
		enum
		{
			left,
			right
		} side;
		AVLNode<K, V> *p = n->getParent();
		if (p != NULL && p->getLeftChild() == n)
			side = left;
		else
			side = right;
		AVLNode<K, V> *temp = n->getLeftChild();
		n->setLeftChild(temp->getRightChild());
		temp->setRightChild(n);
		if (p == NULL)
			setRoot(temp);
		else if (side == left)
			p->setLeftChild(temp);
		else
			p->setRightChild(temp);
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
			if (key == temp->getKey())
				break;
			else if (key < temp->getKey())
				temp = temp->getLeftChild();
			else
				temp = temp->getRightChild();
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
				printSubtree(subtree->getLeftChild(), depth - 1,
							 level, first);
				printSubtree(subtree->getRightChild(), depth - 1,
							 level, false);
			}
		}
		else if (subtree == NULL)
			std::cout << std::setw((first) ? spacing(level) / 2 : spacing(level)) << "-";

		else
			std::cout << std::setw((first) ? spacing(level) / 2 : spacing(level)) << subtree->getKey();
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
	AVLTree(K key, V val) {	root = new AVLNode<K, V>(key, val);	}

	int getHeight() { return root->getHeight(); }
	bool insert(K key, V val)
	{
		if (root == NULL)
			root = new AVLNode<K, V>(key, val);
		else
		{
			AVLNode<K, V> *added_node = NULL;
			AVLNode<K, V> *temp = root;
			while (temp != NULL && added_node == NULL)
			{
				if (key < temp->getKey())
				{
					if (temp->getLeftChild() == NULL)
						added_node = temp->setLeftChild(new AVLNode<K, V>(key, val));
					else
						temp = temp->getLeftChild();
				}
				else if (key > temp->getKey())
				{
					if (temp->getRightChild() == NULL)
						added_node = temp->setRightChild(new AVLNode<K, V>(key, val));
					else
						temp = temp->getRightChild();
				}
				else
					return false;
			}

			temp = added_node;
			while (temp != NULL)
			{
				temp->updateHeight();
				balanceAtNode(temp);
				temp = temp->getParent();
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
		AVLNode<K, V> *p = toBeRemoved->getParent();
		if (p != NULL &&
			p->getLeftChild() == toBeRemoved)
			side = left;
		else
			side = right;
		if (toBeRemoved->getLeftChild() == NULL)
			if (toBeRemoved->getRightChild() == NULL)
			{
				if (p == NULL)
				{
					setRoot(NULL);
					delete toBeRemoved;
				}
				else
				{
					if (side == left)
						p->setLeftChild(NULL);
					else
						p->setRightChild(NULL);
					delete toBeRemoved;
					p->updateHeight();
					balanceAtNode(p);
				}
			}
			else
			{
				if (p == NULL)
				{
					setRoot(toBeRemoved->getRightChild());
					delete toBeRemoved;
				}
				else
				{
					if (side == left)
						p->setLeftChild(toBeRemoved->getRightChild());
					else
						p->setRightChild(toBeRemoved->getRightChild());
					delete toBeRemoved;
					p->updateHeight();
					balanceAtNode(p);
				}
			}
		else if (toBeRemoved->getRightChild() == NULL)
		{
			if (p == NULL)
			{
				setRoot(toBeRemoved->getLeftChild());
				delete toBeRemoved;
			}
			else
			{
				if (side == left)
					p->setLeftChild(toBeRemoved->getLeftChild());
				else
					p->setRightChild(toBeRemoved->getLeftChild());
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
				if (toBeRemoved->getLeftChild()->getRightChild() == NULL)
				{
					replacement = toBeRemoved->getLeftChild();
					replacement->setRightChild(toBeRemoved->getRightChild());
					temp_node = replacement;
				}
				else
				{
					replacement = toBeRemoved->getLeftChild()->getRightChild();
					while (replacement->getRightChild() != NULL)
						replacement = replacement->getRightChild();
					replacement_parent = replacement->getParent();
					replacement_parent->setRightChild(replacement->getLeftChild());
					temp_node = replacement_parent;
					replacement->setLeftChild(toBeRemoved->getLeftChild());
					replacement->setRightChild(toBeRemoved->getRightChild());
				}
			}
			else if (toBeRemoved->getRightChild()->getLeftChild() == NULL)
			{
				replacement = toBeRemoved->getRightChild();
				replacement->setLeftChild(toBeRemoved->getLeftChild());
				temp_node = replacement;
			}
			else
			{
				replacement = toBeRemoved->getRightChild()->getLeftChild();
				while (replacement->getLeftChild() != NULL)
					replacement = replacement->getLeftChild();
				
				replacement_parent = replacement->getParent();
				replacement_parent->setLeftChild(replacement->getRightChild());
				temp_node = replacement_parent;
				replacement->setLeftChild(toBeRemoved->getLeftChild());
				replacement->setRightChild(toBeRemoved->getRightChild());
			}
			if (p == NULL)
				setRoot(replacement);
			else if (side == left)
				p->setLeftChild(replacement);
			else
				p->setRightChild(replacement);
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
		return n->getValue();
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
