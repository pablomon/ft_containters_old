#include "./Node.hpp"

/* DLNode - Doubly-linked node struct declaration */
/* --- Member functions --- */
/* Constructor */
/*	default	(1)	*/
	template <class Type, class Alloc>
	ft::DLNode<Type, Alloc>::DLNode(void) : val(), prev(NULL), next(NULL) {}

/*	fill	(2)	*/
	template <class Type, class Alloc>
	ft::DLNode<Type, Alloc>::DLNode(Type const & val, DLNode * prev, DLNode * next) : val(val), prev(prev), next(next) {}

/*	copy	(3)	*/
	template <class Type, class Alloc>
	ft::DLNode<Type, Alloc>::DLNode(DLNode const & cpy) : val(cpy.val), prev(cpy.prev), next(cpy.next) {}

/* Destructor */
	template <class Type, class Alloc>
	ft::DLNode<Type, Alloc>::~DLNode(void) {}

/* Operators */
/* assignation		(1)	*/
	template <class Type, class Alloc>
	ft::DLNode<Type, Alloc> &	ft::DLNode<Type, Alloc>::operator=(DLNode const & rhs)
	{
		if (this != &rhs)
		{
			val = rhs.val;
			prev = rhs.prev;
			next = rhs.next;
		}
		return (*this);
	}

/* dereference		(4)	*/
	template <class Type, class Alloc>
	typename ft::DLNode<Type, Alloc>::reference	ft::DLNode<Type, Alloc>::operator*(void)
	{
		return (this->val);
	}

/* reference		(5)	*/
	template <class Type, class Alloc>
	typename ft::DLNode<Type, Alloc>::pointer	ft::DLNode<Type, Alloc>::operator->(void)
	{
		return (&this->val);
	}

/* pre-increment	(6)	*/
	template <class Type, class Alloc>
	ft::DLNode<Type, Alloc> &	ft::DLNode<Type, Alloc>::operator++(void)
	{
		return (*this->next);
	}

/* post-increment	(7)	*/
	template <class Type, class Alloc>
	ft::DLNode<Type, Alloc>	ft::DLNode<Type, Alloc>::operator++(int)
	{
		DLNode<Type, Alloc> tmp(*this);
		++*this;
		return (tmp);
	}

/* pre-decrement	(8)	*/
	template <class Type, class Alloc>
	ft::DLNode<Type, Alloc> &	ft::DLNode<Type, Alloc>::operator--(void)
	{
		return (*this->prev);
	}

/* post-decrement	(9)	*/
	template <class Type, class Alloc>
	ft::DLNode<Type, Alloc>	ft::DLNode<Type, Alloc>::operator--(int)
	{
		DLNode<Type, Alloc> tmp(*this);
		--*this;
		return (tmp);
	}



/* PNode - Paired key-value node struct declaration */
/* --- Member functions --- */
/* Constructor */
/*	default	(1)	*/
	template <class Key, class Type, class Compare, class Alloc>
	ft::PNode<Key, Type, Compare, Alloc>::PNode(void) : pair(), is_end(0), parent(NULL), left(NULL), right(NULL) {}

/*	fill	(2)	*/
	template <class Key, class Type, class Compare, class Alloc>
	ft::PNode<Key, Type, Compare, Alloc>::PNode(const Key & key, const Type & val, bool is_end, PNode * parent, PNode * left, PNode * right) :
	pair(std::pair<Key const, Type>(key, val)), is_end(is_end), parent(parent), left(left), right(right) {}

/*	copy	(3)	*/
	template <class Key, class Type, class Compare, class Alloc>
	ft::PNode<Key, Type, Compare, Alloc>::PNode(PNode const & cpy) : pair(cpy.pair) { *this = cpy; }

/* Destructor */
	template <class Key, class Type, class Compare, class Alloc>
	ft::PNode<Key, Type, Compare, Alloc>::~PNode(void) {}

/* Operators */
/* assignation		(1)	*/
	template <class Key, class Type, class Compare, class Alloc>
	ft::PNode<Key, Type, Compare, Alloc> &	ft::PNode<Key, Type, Compare, Alloc>::operator=(PNode const & rhs)
	{
		if (this != &rhs)
		{
			is_end = rhs.is_end;
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
		}
		return (*this);
	}

/* dereference		(4)	*/
	template <class Key, class Type, class Compare, class Alloc>
	typename ft::PNode<Key, Type, Compare, Alloc>::reference	ft::PNode<Key, Type, Compare, Alloc>::operator*(void)
	{
		return (this->pair);
	}

/* reference		(5)	*/
	template <class Key, class Type, class Compare, class Alloc>
	typename ft::PNode<Key, Type, Compare, Alloc>::pointer	ft::PNode<Key, Type, Compare, Alloc>::operator->(void)
	{
		return (&this->pair);
	}

/* pre-increment	(6)	*/
	template <class Key, class Type, class Compare, class Alloc>
	ft::PNode<Key, Type, Compare, Alloc> &	ft::PNode<Key, Type, Compare, Alloc>::operator++(void)
	{
		PNode<Key, Type, Compare, Alloc> *	closest_par;
		PNode<Key, Type, Compare, Alloc> *	old_closest_par;

		PNode<Key, Type, Compare, Alloc> *	most_left;
	
		if (this->right)
		{
			most_left = this->right->left;
			if (most_left)
			{
				while (most_left->left)
					most_left = most_left->left;
				return (*most_left);
			}
			else
				return (*this->right);
		}
		old_closest_par = this;
		closest_par = this->parent;
		while (closest_par)
		{
			if (closest_par->left == old_closest_par)
			{
				return (*closest_par);
			}
			old_closest_par = closest_par;
			closest_par = closest_par->parent;
		}
		return (*closest_par);
	}

/* post-increment	(7)	*/
	template <class Key, class Type, class Compare, class Alloc>
	ft::PNode<Key, Type, Compare, Alloc>	ft::PNode<Key, Type, Compare, Alloc>::operator++(int)
	{
		PNode<Key, Type, Compare, Alloc> tmp(*this);
		++*this;
		return (tmp);
	}

/* pre-decrement	(8)	*/
	template <class Key, class Type, class Compare, class Alloc>
	ft::PNode<Key, Type, Compare, Alloc> &	ft::PNode<Key, Type, Compare, Alloc>::operator--(void)
	{
		PNode<Key, Type, Compare, Alloc> *	closest_par;
		PNode<Key, Type, Compare, Alloc> *	old_closest_par;
		PNode<Key, Type, Compare, Alloc> *	most_right;

		if (this->left)
		{
			most_right = this->left->right;
			if (most_right)
			{
				while (most_right->right)
					most_right = most_right->right;
				return (*most_right);
			}
			else
				return (*this->left);
		}
		old_closest_par = this;
		closest_par = this->parent;
		while (closest_par)
		{
			if (closest_par->right == old_closest_par)
				return (*closest_par);
			old_closest_par = closest_par;
			closest_par = closest_par->parent;
		}
		return (*closest_par);
	}

/* post-decrement	(9)	*/
	template <class Key, class Type, class Compare, class Alloc>
	ft::PNode<Key, Type, Compare, Alloc>	ft::PNode<Key, Type, Compare, Alloc>::operator--(int)
	{
		PNode<Key, Type, Compare, Alloc> tmp(*this);
		--*this;
		return (tmp);
	}

