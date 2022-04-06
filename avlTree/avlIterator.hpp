#if !defined(AVLTREE_IT_HPP)
#define AVLTREE_IT_HPP

#include "avlTree.hpp"

template <class N, class P>
class avlIterator
{
	public:
	typedef N 						node_type;
	typedef node_type 				*node_pointer;

	typedef P						value_type;
	typedef value_type				*pointer;
	typedef value_type const 		*const_pointer;
	typedef value_type				&reference;
	typedef value_type const 		&const_reference;
	typedef std::ptrdiff_t 			difference_type;
	typedef std::bidirectional_iterator_tag 	iterator_category;

	private:
	node_pointer current;
	node_pointer prev;
	node_pointer root;
	int outOfRange = 0;

	public:
	//Default constructor
    avlIterator(node_pointer root, node_pointer current)
    {
        this->root = root;
		this->current = current;
		prev = current;
		if (current == getEnd() + 1)
			outOfRange = 1;
    }
	//Copy
	avlIterator(avlIterator<node_type, value_type> const &other)
	{
		root = other.root;
		current = other.current;
		prev = other.prev;
		outOfRange = other.outOfRange;
	}
	//Destructor
	~avlIterator() {}

	//Operators
    reference operator*() const { return current->content; }
	pointer operator->() const { return &current->content; }
	avlIterator& operator++()
	{
		moveForward();
        return *this;
	}
	avlIterator operator++(int)
	{
		avlIterator ret = *this;
   		this->operator++();
   		return ret;
	}
	avlIterator& operator--()
	{
		moveBackwards();
		return *this;
	}
	avlIterator operator--(int)
	{
		avlIterator ret = *this;
		this->operator--();
		return ret;
	}
	bool operator==(const avlIterator& other) const
	{
		return (other.current == current);
	}
	bool operator!=(const avlIterator& other) const
	{
		return (other.current != current);
	}

	// member functions
	private:
	node_pointer goFullLeft(node_pointer node)
	{
		while (node->left)
			node = node->left;
		return node;
	}
	node_pointer goFullRight(node_pointer node)
	{
		while (node->right)
			node = node->right;
		return node;
	}
	node_pointer getEnd()
	{
		node_pointer node = root;
		while (node->right)
			node = node->right;
		return node;
	}
	node_pointer getBegin()
	{
		node_pointer node = root;
		while (node->left)
			node = node->left;
		return node;
	}

	void moveForward()
	{
		if (outOfRange)
		{
			current = getEnd();
			prev = current;
			outOfRange = 0;
			return;
		}
		if (current == getEnd())
		{
			outOfRange = 1;
			current++;
			return;
		}
		if (current->right && current->right != prev)
		{
			node_pointer node = goFullLeft(current->right);
			prev = node;
			current = node;
			return;
		}
		while (current->parent)
		{
			if (current->parent->content.first > prev->content.first)
			{
				prev = current;
				current = current->parent;
				return;
			}
			current = current->parent;
		}
	}
 
	void moveBackwards()
	{
		if (outOfRange)
		{
			current = getEnd();
			prev = current;
			outOfRange = 0;
			return;
		}
		if (current == getBegin())
		{
			current = getEnd() + 1;
			prev = current;
			outOfRange = 1;
			return;
		}
		if (current->right && current->right != prev)
		{
			prev = current;
			current = goFullRight(current);
			return;
		}
		if (current->left && current->left != prev)
		{
			if (current->left->right)
			{
				prev = current;
				current = goFullRight(current->left->right);
				return;
			}
			prev = current;
			current = current->left;
			return;
		}
		while (current->parent)
		{
			if (current->parent->content.first < prev->content.first)
			{
				prev = current;
				current = current->parent;
				return;
			}
			current = current->parent;
		}
	}
};

#endif // AVLTREE_IT_HPP
