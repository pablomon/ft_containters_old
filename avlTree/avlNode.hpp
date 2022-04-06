#if !defined(AVL_NODE_HPP)
#define AVL_NODE_HPP

#include <stdlib.h>
#include "../utils/pair.hpp"

template <class K, class V>
class AVLNode
{
public:
	typedef AVLNode<K,V>		node_type;
	typedef node_type			*node_pointer;
	typedef ft::pair<K,V>		content_type;

	content_type content;
	int height;
	node_pointer left;
	node_pointer parent;
	node_pointer right;

public:
	AVLNode(content_type pair)
	{
		this->content = pair;
		height = 0;
		parent = NULL;
		left = NULL;
		right = NULL;
	}

	int getBalance()
	{
		int result;
		if (left == NULL)
		{
			if (right == NULL)
				result = 0;
			else
				result = -right->height - 1;
		}
		else if (right == NULL)
			result = left->height + 1;
		else
			result = left->height - right->height;
		return result;
	}

	int getHeight() { return height; }
	void removeParent() { parent = NULL; }
	node_pointer setLeft(node_pointer newLeft)
	{
		if (newLeft != NULL)
			newLeft->parent = this;
		left = newLeft;
		updateHeight();
		return left;
	}
	node_pointer setRight(node_pointer newRight)
	{
		if (newRight != NULL)
			newRight->parent = this;
		right = newRight;
		updateHeight();
		return right;
	}

	int updateHeight()
	{
		if (left == NULL)
		{
			if (right == NULL)
				height = 0;
			else
				height = right->height + 1;
		}
		else if (right == NULL)
			height = left->height + 1;
		else if (left->height > right->height)
			height = left->height + 1;
		else
			height = right->height + 1;
		return height;
	}

};

#endif // AVL_NODE_HPP
