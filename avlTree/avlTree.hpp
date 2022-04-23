#if !defined(AVL_HPP)
#define AVL_HPP

#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>

#include "avlNode.hpp"
#include "avlIterator.hpp"
#include "../utils/pair.hpp"

namespace ft
{
	template <typename K, typename V, typename alloc = std::allocator<avlNode <K,V> > >
	class avlTree
	{
	public:
		typedef alloc				allocator_type;
		typedef avlNode<K, V> 		node_type;
		typedef node_type 			*node_pointer;
		typedef ft::pair<K,V>		content_type;
		typedef avlIterator<node_type, content_type> 			iterator;
		typedef avlIterator<node_type, const content_type>		const_iterator;

		allocator_type	m_alloc;
		node_pointer	m_root;
		std::size_t		m_size;

	public:
		avlTree() : m_root(NULL), m_size(0) {}
		avlTree(const avlTree & x) : m_root(NULL), m_size(0)
		{
			if (x.m_size > 0)
			{
				iterator it = x.begin();
				while(it != x.end())
				{
					content_type pair = *it;
					insert(pair);
					it++;
				}
			}
		}
		~avlTree()
		{
			delete_branch(m_root);
		}

		int getHeight() { return m_root->getHeight(); }

		node_pointer create_node(content_type content)
		{
			node_pointer node = m_alloc.allocate(1);
			m_alloc.construct(node, node_type(content, &m_root));
			m_size++;
			return node;
		}

		void delete_node(node_pointer node)
		{
			m_alloc.destroy(node);
			m_alloc.deallocate(node, 1);
			m_size--;
		}
		
		void delete_branch(node_pointer node)
		{
			if (node == NULL)
				return;
			delete_branch(node->left);
			delete_branch(node->right);
			delete_node(node);
		}

		ft::pair<node_pointer, bool> insert(content_type pair)
		{
			ft::pair<node_pointer, bool> res;
			if (m_root == NULL)
			{
				m_root = create_node(pair);
				res.first = m_root;
				res.second = true;
			}
			else
			{
				node_pointer added_node = NULL;
				node_pointer temp = m_root;
				while (temp != NULL && added_node == NULL)
				{
					if (pair.first < temp->content.first)
					{
						if (temp->left == NULL)
						{
							added_node = temp->setLeft(create_node(pair));
							res.first = added_node;					
							res.second = true;
						}
						else
							temp = temp->left;
					}
					else if (pair.first > temp->content.first)
					{
						if (temp->right == NULL)
						{
							added_node = temp->setRight(create_node(pair));
							res.first = added_node;
							res.second = true;
						}
						else
							temp = temp->right;
					}
					else
					{
						res.first = temp;
						res.second = false;
						return res;
					}
				}

				temp = added_node;
				while (temp != NULL)
				{
					temp->updateHeight();
					balanceAtNode(temp);
					temp = temp->parent;
				}
			}
			return res;
		}
	
		void remove(iterator it)
		{
			content_type cnt = *it;
			remove(cnt.first);
		}
		bool remove(K key)
		{
			node_pointer toBeRemoved = findNode(key);
			if (toBeRemoved == NULL)
				return false;
			bool isLeft;
			node_pointer p = toBeRemoved->parent;
			if (p != NULL && p->left == toBeRemoved)
				isLeft = true;
			else
				isLeft = false;
			if (toBeRemoved->left == NULL)
				if (toBeRemoved->right == NULL)
				{
					if (p == NULL)
					{
						setRoot(NULL);
						delete_node(toBeRemoved);
					}
					else
					{
						if (isLeft)
							p->setLeft(NULL);
						else
							p->setRight(NULL);
						delete_node(toBeRemoved);
						p->updateHeight();
						balanceAtNode(p);
					}
				}
				else
				{
					if (p == NULL)
					{
						setRoot(toBeRemoved->right);
						delete_node(toBeRemoved);
					}
					else
					{
						if (isLeft)
							p->setLeft(toBeRemoved->right);
						else
							p->setRight(toBeRemoved->right);
						delete_node(toBeRemoved);
						p->updateHeight();
						balanceAtNode(p);
					}
				}
			else if (toBeRemoved->right == NULL)
			{
				if (p == NULL)
				{
					setRoot(toBeRemoved->left);
					delete_node(toBeRemoved);
				}
				else
				{
					if (isLeft)
						p->setLeft(toBeRemoved->left);
					else
						p->setRight(toBeRemoved->left);
					delete_node(toBeRemoved);
					p->updateHeight();
					balanceAtNode(p);
				}
			}
			else
			{
				node_pointer replacement;
				node_pointer replacement_parent;
				node_pointer temp_node;
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
				else if (isLeft)
					p->setLeft(replacement);
				else
					p->setRight(replacement);
				delete_node(toBeRemoved);
				balanceAtNode(temp_node);
			}
			return true;
		}
		V getValue(K key)
		{
			node_pointer n = findNode(key);
			if (n == NULL)
				return 0;
			return n->content.second;
		}
		node_pointer getFirst() const
		{
			if (m_root == NULL)
				return NULL;
			node_pointer node = m_root;
			while (node->left != NULL)
				node = node->left;
			return node;
		}

		iterator begin() const
		{
			iterator it(m_root, getFirst());
			return it;
		}

		const_iterator cbegin() const
		{
			const_iterator it(m_root, getFirst());
			return it;
		}

		node_pointer getLast() const
		{
			if (m_root == NULL)
				return NULL;
			node_pointer node = m_root;
			while (node->right != NULL)
				node = node->right;
			return node;
		}
		iterator end() const
		{
			node_pointer end = getLast();
			if (end != NULL)
				end = end + 1;
			iterator it(m_root, end);
			return it;
		}
		const_iterator cend() const
		{
			const_iterator it(m_root, getLast() + 1);
			return it;
		}

		node_pointer findNode(K key) const
		{
			node_pointer temp = m_root;
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
		void print()
		{
			if (m_root == NULL)
			{
				std::cout << "Empty" << std::endl;
				return;
			}
			int max = m_root->getHeight();
			for (int depth = 0; depth <= max; depth++)
			{
				printSubtree(m_root, depth, max - depth + 1, true);
				std::cout << std::endl;
			}
		}

	private:
		void balanceAtNode(node_pointer n)
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
		void rotateLeft(node_pointer n)
		{
			bool isLeft;
			node_pointer p = n->parent;
			if (p != NULL && p->left == n)
				isLeft = true;
			else
				isLeft = false;
			node_pointer temp = n->right;
			n->setRight(temp->left);
			temp->setLeft(n);
			if (p == NULL)
				setRoot(temp);
			else if (isLeft)
				p->setLeft(temp);
			else
				p->setRight(temp);
		}
		void rotateRight(node_pointer n)
		{
			bool isLeft;
			node_pointer p = n->parent;
			if (p != NULL && p->left == n)
				isLeft = true;
			else
				isLeft = false;
			node_pointer temp = n->left;
			n->setLeft(temp->right);
			temp->setRight(n);
			if (p == NULL)
				setRoot(temp);
			else if (isLeft)
				p->setLeft(temp);
			else
				p->setRight(temp);
		}
		void setRoot(node_pointer n)
		{
			m_root = n;
			if (m_root != NULL)
				m_root->removeParent();
		}

		// debug
		void printSubtree(node_pointer subtree, int depth, int level, bool first)
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
	};

} // ft
#endif // AVL_HPP
