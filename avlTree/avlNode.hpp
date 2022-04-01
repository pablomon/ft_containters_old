#if !defined(AVL_NODE_HPP)
#define AVL_NODE_HPP

#include <stdlib.h>

template <class K, class V>
class AVLNode
{
private:
	K key;
	V value;
	int height;
	AVLNode<K, V> *left_child;
	AVLNode<K, V> *parent;
	AVLNode<K, V> *right_child;

public:
	AVLNode(K key, V value)
	{
		this->key = key;
		this->value = value;
		height = 0;
		parent = NULL;
		left_child = NULL;
		right_child = NULL;
	}

	int getBalance()
	{
		int result;
		if (left_child == NULL)
		{
			if (right_child == NULL)
				result = 0;
			else
				result = -right_child->height - 1;
		}
		else if (right_child == NULL)
			result = left_child->height + 1;
		else
			result = left_child->height - right_child->height;
		return result;
	}

	K getKey() { return key; }
	V getValue() { return value; }
	int getHeight() { return height; }
	AVLNode<K, V> *getLeftChild() { return left_child; }
	AVLNode<K, V> *getParent() { return parent; }
	AVLNode<K, V> *getRightChild() { return right_child; }
	void removeParent() { parent = NULL; }
	AVLNode<K, V> *setLeftChild(AVLNode<K, V> *newLeft)
	{
		if (newLeft != NULL)
			newLeft->parent = this;
		left_child = newLeft;
		updateHeight();
		return left_child;
	}
	AVLNode<K, V> *setRightChild(AVLNode<K, V> *newRight)
	{
		if (newRight != NULL)
			newRight->parent = this;
		right_child = newRight;
		updateHeight();
		return right_child;
	}
	int updateHeight()
	{
		if (left_child == NULL)
		{
			if (right_child == NULL)
				height = 0;
			else
				height = right_child->height + 1;
		}
		else if (right_child == NULL)
			height = left_child->height + 1;
		else if (left_child->height > right_child->height)
			height = left_child->height + 1;
		else
			height = right_child->height + 1;
		return height;
	}
};

#endif // AVL_NODE_HPP
