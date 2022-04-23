#if !defined(AVLTREE_IT_HPP)
#define AVLTREE_IT_HPP

#include "avlTree.hpp"

namespace ft
{
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
		node_pointer root; //TODO refactor to remove root
		bool isBeforeBegin;
		bool isLast;
		bool isPastLast;
		node_pointer *tree_root;

		public:
		avlIterator() : current(NULL), prev(NULL), root(NULL), isBeforeBegin(false), isPastLast(false) {}
		//Default constructor
		avlIterator(node_pointer root, node_pointer current)
		{
			tree_root = NULL;
			this->root = root;
			if (root)
				tree_root = root->tree_root;
			this->current = current;
			prev = current;
			isBeforeBegin = false;
			isLast = false;
			isPastLast = current == getEnd() + 1 ? true : false;
		}
		//Copy
		avlIterator(avlIterator<node_type, value_type> const &other)
		{
			root = other.root;
			tree_root = other.tree_root;
			current = other.current;
			prev = other.prev;
			isBeforeBegin = other.isBeforeBegin;
			isPastLast = other.isPastLast;
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
			if (other.isPastLast && isPastLast)
				return true;
			return (other.current == current);
		}
		bool operator!=(const avlIterator& other) const
		{
			return (other.current != current);
		}

		void print(std::string str)
		{
			std::cout << "printing iterator " << str << ":\n"
				<< "outofrange = " << isBeforeBegin << std::endl;
			if (!isBeforeBegin)
			{
				std::cout << "current = " << current->content.first << std::endl;
				std::cout << "getEnd() = " << getEnd()->content.first << std::endl;
			}
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

		void updateRoot()
		{
			root = NULL;
			if (tree_root)
				root = *tree_root;
			/*node_pointer node = root;
			while (node->parent)
				node = node->parent;
			root = node;*/
		}

		node_pointer getEnd()
		{
			updateRoot();
			node_pointer node = root;
			if (node == NULL)
				return NULL;
			while (node->right)
				node = node->right;
			return node;
		}
		node_pointer getBegin()
		{
			updateRoot();
			node_pointer node = root;
			if (node == NULL)
				return NULL;
			while (node->left)
				node = node->left;
			return node;
		}

		void moveForward()
		{
			if (isPastLast)
			{
				current = getEnd() + 1;
				prev = current;
				isBeforeBegin = false;
				return;
			}
			if (current == getEnd())
			{
				isPastLast = true;
				isBeforeBegin = false;
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
			if (isPastLast)
			{
				isPastLast = false;
				current = getEnd();
				isBeforeBegin = false;
				prev = NULL;
				return;
			}
			if (isBeforeBegin)
			{
				current = getEnd();
				prev = current;
				isBeforeBegin = false;
				return;
			}
			if (current == getBegin())
			{
				current = getEnd() + 1;
				prev = current;
				isBeforeBegin = true;
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
			if (current->parent && prev == NULL)
			{
				prev = current;
				current = current->parent;
				return;
			}
			while (current->parent)
			{
				if (prev == NULL)
				{
					prev = current;
					current = current->parent;
					return;
				}
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
	
} // namespace ft


#endif // AVLTREE_IT_HPP
