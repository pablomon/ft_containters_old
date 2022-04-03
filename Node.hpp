#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>
#include <memory>
#include <stdexcept>

#include "./Iterator.hpp"

namespace ft
{
	/* DLNode - Doubly-linked node struct declaration */
	template <class Type, class Alloc = std::allocator<Type> >
	class DLNode : public ft::iterator_traits<Type>
	{
		/* --- Member types --- */
			typedef	DLNode<Type, Alloc>		node;
			typedef typename ft::iterator_traits<Type>::reference	reference;
			typedef typename ft::iterator_traits<Type>::pointer		pointer;

		/* --- Member functions --- */
		public:
		/* Constructor */
			/*	default	(1)	*/	DLNode(void);
			/*	fill	(2)	*/	DLNode(const Type & val, node * prev = NULL, node * next = NULL);
			/*	copy	(3)	*/	DLNode(node const & cpy);
		
		/* Destructor */
			~DLNode(void);

		/* Operators */
			/* assignation		(1)	*/	node &	operator=(node const & rhs);

			/* dereference		(4)	*/	reference	operator*(void);
			/* reference		(5)	*/	pointer		operator->(void);

			/* pre-increment	(6)	*/	node &	operator++(void);
			/* post-increment	(7)	*/	node	operator++(int);
			/* pre-decrement	(8)	*/	node &	operator--(void);
			/* post-decrement	(9)	*/	node	operator--(int);

		/* --- Member attributes --- */
			Type	val;
			node *	prev;
			node *	next;
	};


	/* PNode - Paired key-value node struct declaration */
	template <class Key, class Type, class Compare = std::less<Key>, class Alloc = std::allocator<Type> >
	class PNode
	{
		/* --- Member types --- */
			typedef	PNode<Key, Type, Compare, Alloc>					node;
			typedef std::pair<const Key, Type>							value_type;
			typedef typename ft::iterator_traits<value_type>::reference	reference;
			typedef typename ft::iterator_traits<value_type>::pointer	pointer;

		/* --- Member functions --- */
		public:
		/* Constructor */
			/*	default	(1)	*/	PNode(void);
			/*	fill	(2)	*/	PNode(const Key & key, const Type & val, bool is_end = 0, node * parent = NULL, node * left = NULL, node * right = NULL);
			/*	copy	(3)	*/	PNode(node const & cpy);
		
		/* Destructor */
			~PNode(void);

		/* Operators */
			/* assignation		(1)	*/	node &	operator=(PNode const & rhs);

			/* dereference		(4)	*/	reference	operator*(void);
			/* reference		(5)	*/	pointer		operator->(void);

			/* pre-increment	(6)	*/	node &	operator++(void);
			/* post-increment	(7)	*/	node	operator++(int);
			/* pre-decrement	(8)	*/	node &	operator--(void);
			/* post-decrement	(9)	*/	node	operator--(int);

		/* --- Member attributes --- */
			value_type	pair;
			bool		is_end;
			node *		parent;
			node *		left;
			node *		right;
	};
}

#include "./Node.tpp"

#endif