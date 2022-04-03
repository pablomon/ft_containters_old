#include "Iterator.hpp"

/* ========= Basic Iterators : Class declarations ========= */

/* BaseIterator Class declaration */
/* --- Member functions --- */
/* Constructor */
	/* default	(1)	*/
	template <class Type, class Alloc, class Node>
	ft::BaseIterator<Type, Alloc, Node>::BaseIterator(Node * node) : _current(node) {}

	/* copy		(2)	*/
	template <class Type, class Alloc, class Node>
	ft::BaseIterator<Type, Alloc, Node>::BaseIterator(BaseIterator<value_type, Alloc, Node> const & cpy) : _current(cpy.getCurrent()) {}

/* Destructor */
	template <class Type, class Alloc, class Node>
	ft::BaseIterator<Type, Alloc, Node>::~BaseIterator(void) {}

/* Element access */
	template <class Type, class Alloc, class Node>
	Node *	ft::BaseIterator<Type, Alloc, Node>::getCurrent(void) const
	{ return (_current);}

/* Operators */
	/* assignation	(1)	*/
	template <class Type, class Alloc, class Node>
	ft::BaseIterator<Type, Alloc, Node> &	ft::BaseIterator<Type, Alloc, Node>::operator=(BaseIterator const & rhs)
	{
		if (this != &rhs)
			this->_current = rhs._current;
		return (*this);
	}

	/* equality		(2)	*/
	template <class Type, class Alloc, class Node>
	bool	ft::BaseIterator<Type, Alloc, Node>::operator==(BaseIterator const & rhs) const
	{ return (this->_current == rhs._current); }

	/* inequality	(3)	*/
	template <class Type, class Alloc, class Node>
	bool	ft::BaseIterator<Type, Alloc, Node>::operator!=(BaseIterator const & rhs) const
	{ return (this->_current != rhs._current); }

/* --- Non-member function overloads --- */
/* relationnal Operators (BaseIterator) */
/*	(1)	*/
template <class Type, class Alloc, class Node>
bool	ft::operator==(const BaseIterator<Type, Alloc, Node>& lhs, const BaseIterator<Type, Alloc, Node>& rhs)
{ return (lhs.getCurrent() == rhs.getCurrent()); }

/*	(2)	*/
template <class Type, class Alloc, class Node>
bool	ft::operator!=(const BaseIterator<Type, Alloc, Node>& lhs, const BaseIterator<Type, Alloc, Node>& rhs)
{ return (!(lhs.getCurrent() == rhs.getCurrent())); }

/*	(3)	*/
template <class Type, class Alloc, class Node>
bool	ft::operator<(const BaseIterator<Type, Alloc, Node>& lhs, const BaseIterator<Type, Alloc, Node>& rhs)
{ return (lhs.getCurrent() < rhs.getCurrent()); }

/*	(4)	*/
template <class Type, class Alloc, class Node>
bool	ft::operator<=(const BaseIterator<Type, Alloc, Node>& lhs, const BaseIterator<Type, Alloc, Node>& rhs)
{ return (lhs.getCurrent() <= rhs.getCurrent()); }

/*	(5)	*/
template <class Type, class Alloc, class Node>
bool	ft::operator>(const BaseIterator<Type, Alloc, Node>& lhs, const BaseIterator<Type, Alloc, Node>& rhs)
{ return (lhs.getCurrent() > rhs.getCurrent()); }

/*	(6)	*/
template <class Type, class Alloc, class Node>
bool	ft::operator>=(const BaseIterator<Type, Alloc, Node>& lhs, const BaseIterator<Type, Alloc, Node>& rhs)
{ return (lhs.getCurrent() >= rhs.getCurrent()); }




/* Bidirectionnal Class declaration */
/* --- Member functions --- */
/* Constructor */
	/* default	(1)	*/
	template <class Type, class Alloc, class Node>
	ft::Bidirectional<Type, Alloc, Node>::Bidirectional(Node * node) : BaseIterator<typename ft::iterator_traits<Type>::value_type, Alloc, Node>(node)
	{
		this->_current = node;
	}

	/* copy		(2)	*/
	template <class Type, class Alloc, class Node>
	ft::Bidirectional<Type, Alloc, Node>::Bidirectional(Bidirectional<value_type, alloc_type, node_type> const & cpy) : BaseIterator<typename ft::iterator_traits<Type>::value_type, Alloc, Node>(cpy) {}

/* Destructor */
	template <class Type, class Alloc, class Node>
	ft::Bidirectional<Type, Alloc, Node>::~Bidirectional(void) {}


/* Conversions before operations  */
	template <class Type, class Alloc, class Node>
	typename ft::Bidirectional<Type, Alloc, Node>::reference	ft::Bidirectional<Type, Alloc, Node>::_deref_val(value_type * type) const
	{
		return (*type);
	}

	template <class Type, class Alloc, class Node>
	template <class OtherClass>
	typename ft::Bidirectional<Type, Alloc, Node>::reference	ft::Bidirectional<Type, Alloc, Node>::_deref_val(OtherClass * other_class) const
	{
		return (other_class->operator*());
	}

	template <class Type, class Alloc, class Node>
	typename ft::Bidirectional<Type, Alloc, Node>::pointer	ft::Bidirectional<Type, Alloc, Node>::_ref_val(value_type * type) const
	{
		return (type);
	}

	template <class Type, class Alloc, class Node>
	template <class OtherClass>
	typename ft::Bidirectional<Type, Alloc, Node>::pointer	ft::Bidirectional<Type, Alloc, Node>::_ref_val(OtherClass * other_class) const
	{
		return (other_class->operator->());
	}

	template <class Type, class Alloc, class Node>
	void	ft::Bidirectional<Type, Alloc, Node>::_pre_incr(value_type *)
	{
		++this->_current;
	}

	template <class Type, class Alloc, class Node>
	template <class OtherClass>
	void	ft::Bidirectional<Type, Alloc, Node>::_pre_incr(OtherClass *)
	{
		this->_current = &(++(*this->_current));
	}

	template <class Type, class Alloc, class Node>
	void	ft::Bidirectional<Type, Alloc, Node>::_pre_decr(value_type *)
	{
		--this->_current;
	}

	template <class Type, class Alloc, class Node>
	template <class OtherClass>
	void	ft::Bidirectional<Type, Alloc, Node>::_pre_decr(OtherClass *)
	{
		this->_current = &(--(*this->_current));
	}

/* Operators */

	/* dereference	(4)	*/
	template <class Type, class Alloc, class Node>
	typename ft::Bidirectional<Type, Alloc, Node>::reference	ft::Bidirectional<Type, Alloc, Node>::operator*(void) const
	{
		return (this->_deref_val(this->_current));
	}

	/* reference	(5)	*/
	template <class Type, class Alloc, class Node>
	typename ft::Bidirectional<Type, Alloc, Node>::pointer	ft::Bidirectional<Type, Alloc, Node>::operator->(void) const
	{
		return (this->_ref_val(this->_current));
	}

	/* pre-increment	(6)	*/
	template <class Type, class Alloc, class Node>
	typename ft::Bidirectional<Type, Alloc, Node> &	ft::Bidirectional<Type, Alloc, Node>::operator++(void)
	{
		this->_pre_incr(this->_current);
		return (*this);
	}

	/* post-increment	(7)	*/
	template <class Type, class Alloc, class Node>
	typename ft::Bidirectional<Type, Alloc, Node>	ft::Bidirectional<Type, Alloc, Node>::operator++(int)
	{
		Bidirectional<Type, Alloc, Node> tmp(*this);
		++(*this);
		return (tmp);
	}

	/* pre-decrement	(8)	*/
	template <class Type, class Alloc, class Node>
	typename ft::Bidirectional<Type, Alloc, Node> &	ft::Bidirectional<Type, Alloc, Node>::operator--(void)
	{
		this->_pre_decr(this->_current);
		return (*this);
	}

	/* post-decrement	(9)	*/
	template <class Type, class Alloc, class Node>
	typename ft::Bidirectional<Type, Alloc, Node>	ft::Bidirectional<Type, Alloc, Node>::operator--(int)
	{
		Bidirectional<Type, Alloc, Node> tmp(*this);
		--(*this);
		return (tmp);
	}



/* RandomAccess Class declaration */
/* --- Member functions --- */
/* Constructor */
	/* default	(1)	*/
	template <class Type, class Alloc, class Node>
	ft::RandomAccess<Type, Alloc, Node>::RandomAccess(Node * node) : Bidirectional<typename ft::iterator_traits<Type>::value_type, Alloc, Node>(node) {}

	/* copy		(2)	*/
	template <class Type, class Alloc, class Node>
	ft::RandomAccess<Type, Alloc, Node>::RandomAccess(RandomAccess<value_type, Alloc, Node> const & cpy) : Bidirectional<typename ft::iterator_traits<Type>::value_type, Alloc, Node>(cpy) {}

	/* copy		(3)	*/
	template <class Type, class Alloc, class Node>
	ft::RandomAccess<Type, Alloc, Node>::RandomAccess(Bidirectional<value_type, Alloc, Node> const & cpy) : Bidirectional<typename ft::iterator_traits<Type>::value_type, Alloc, Node>(cpy) {}

/* Destructor */
	template <class Type, class Alloc, class Node>
	ft::RandomAccess<Type, Alloc, Node>::~RandomAccess(void) {}

/* Operators */
	/* unary plus				(10)	*/
	template <class Type, class Alloc, class Node>
	typename ft::RandomAccess<Type, Alloc, Node>	ft::RandomAccess<Type, Alloc, Node>::operator+(difference_type n) const
	{
		RandomAccess<Type, Alloc, Node> tmp(*this);
		tmp._current = this->_current + n;
		return (tmp);
	}
	
	/* unary minus				(12)	*/
	template <class Type, class Alloc, class Node>
	typename ft::RandomAccess<Type, Alloc, Node>	ft::RandomAccess<Type, Alloc, Node>::operator-(difference_type n) const
	{
		RandomAccess<Type, Alloc, Node> tmp(*this);
		tmp._current = this->_current - n;
		return (tmp);
	}
	
	/* subtraction				(13)	*/
	template <class Type, class Alloc, class Node>
	typename ft::RandomAccess<Type, Alloc, Node>::difference_type	ft::RandomAccess<Type, Alloc, Node>::operator-(RandomAccess const & b) const
	{
		return (this->getCurrent() - b.getCurrent());
	}

	/* less than				(14)	*/
	template <class Type, class Alloc, class Node>
	bool	ft::RandomAccess<Type, Alloc, Node>::operator<(RandomAccess const & b) const
	{
		return (this->getCurrent() < b.getCurrent());
	}
	
	/* greater than 			(15)	*/
	template <class Type, class Alloc, class Node>
	bool	ft::RandomAccess<Type, Alloc, Node>::operator>(RandomAccess const & b) const
	{
		return (this->getCurrent() > b.getCurrent());
	}
	
	/* less than or equal to	(16)	*/
	template <class Type, class Alloc, class Node>
	bool	ft::RandomAccess<Type, Alloc, Node>::operator<=(RandomAccess const & b) const
	{
		return (this->getCurrent() <= b.getCurrent());
	}
	
	/* greater than or equal to	(17)	*/
	template <class Type, class Alloc, class Node>
	bool	ft::RandomAccess<Type, Alloc, Node>::operator>=(RandomAccess const & b) const
	{
		return (this->getCurrent() >= b.getCurrent());
	}
	
	/* addition-assignement		(18)	*/
	template <class Type, class Alloc, class Node>
	ft::RandomAccess<Type, Alloc, Node> &	ft::RandomAccess<Type, Alloc, Node>::operator+=(difference_type n)
	{
		this->_current += n;
		return (*this);
	}
	
	/* subtraction-assignement	(19)	*/
	template <class Type, class Alloc, class Node>
	ft::RandomAccess<Type, Alloc, Node> &	ft::RandomAccess<Type, Alloc, Node>::operator-=(difference_type n)
	{
		this->_current -= n;
		return (*this);
	}
	
	/* subscript				(20)	*/
	template <class Type, class Alloc, class Node>
	typename ft::RandomAccess<Type, Alloc, Node>::reference	ft::RandomAccess<Type, Alloc, Node>::operator[](difference_type n) const
	{
		return (this->_current[n]);
	}



/* Reverse_Iterator Class declaration */
/* --- Member functions --- */
/* Constructor */
	/* default			(1)	*/
	template <class Iterator>
	ft::Reverse_Iterator<Iterator>::Reverse_Iterator(void) : _base(iterator_type()) {}

	/* initialization	(2)	*/
	template <class Iterator>
	ft::Reverse_Iterator<Iterator>::Reverse_Iterator(iterator_type const & init) : _base(init) {}

	/* copy				(3)	*/
	template <class Iterator>
	template <class It>
	ft::Reverse_Iterator<Iterator>::Reverse_Iterator(const Reverse_Iterator<It> & cpy) : _base(cpy.base()) {}


/* Destructor */
	template <class Iterator>
	ft::Reverse_Iterator<Iterator>::~Reverse_Iterator(void) {}

/* Element access */
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::iterator_type	ft::Reverse_Iterator<Iterator>::base(void) const
	{ return (_base); }

/* Operators */
	/* assignation				(0)	*/
	template <class Iter>
	ft::Reverse_Iterator<Iter> &	ft::Reverse_Iterator<Iter>::operator=(Reverse_Iterator const & rhs)
	{
		if (this != &rhs)
			this->_base = rhs._base;
		return (*this);
	}

	/* dereference				(1)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::reference	ft::Reverse_Iterator<Iterator>::operator*(void) const
	{
		return (*_base);
	}

	/* unary plus				(2)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>	ft::Reverse_Iterator<Iterator>::operator+(difference_type n) const
	{
		return (Reverse_Iterator(_base.operator-(n)));
	}
	
	/* pre-increment			(3)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator> &	ft::Reverse_Iterator<Iterator>::operator++(void)
	{
		_base.operator--();
		return (*this);
	}

	/* post-increment			(4)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>	ft::Reverse_Iterator<Iterator>::operator++(int)
	{
		Reverse_Iterator<Iterator> tmp(*this);
		++(*this);
		return (tmp);
	}

	/* addition-assignement		(5)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator> &	ft::Reverse_Iterator<Iterator>::operator+=(difference_type n)
	{
		_base.operator-=(n);
		return (*this);
	}

	/* unary minus				(6)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>	ft::Reverse_Iterator<Iterator>::operator-(difference_type n) const
	{
		return (Reverse_Iterator(_base.operator+(n)));
	}

	/* pre-decrement			(7)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator> &	ft::Reverse_Iterator<Iterator>::operator--(void)
	{
		_base.operator++();
		return (*this);
	}

	/* post-decrement			(8)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>	ft::Reverse_Iterator<Iterator>::operator--(int)
	{
		Reverse_Iterator<Iterator> tmp(*this);
		--(*this);
		return (tmp);
	}

	/* subtraction-assignement	(9)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator> &	ft::Reverse_Iterator<Iterator>::operator-=(difference_type n)
	{
		_base.operator+=(n);
		return (*this);
	}

	/* reference				(10)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::pointer	ft::Reverse_Iterator<Iterator>::operator->(void) const
	{
		return (&(operator*()));
	}

	/* subscript				(11)	*/
	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::reference	ft::Reverse_Iterator<Iterator>::operator[](difference_type n) const
	{
		return (_base[-n]);
	}

/* --- Non-member function overloads --- */
/* relationnal Operators (Reverse_Iterator) */
/*	(1)	*/
template <class Iter>
bool	ft::operator==(const ft::Reverse_Iterator<Iter>& lhs, const ft::Reverse_Iterator<Iter>& rhs)
{ return (lhs.base() == rhs.base()); }

/*	(2)	*/
template <class Iter>
bool	ft::operator!=(const ft::Reverse_Iterator<Iter>& lhs, const ft::Reverse_Iterator<Iter>& rhs)
{ return (lhs.base() != rhs.base()); }

/*	(3)	*/
template <class Iter>
bool	ft::operator<(const ft::Reverse_Iterator<Iter>& lhs, const ft::Reverse_Iterator<Iter>& rhs)
{ return (lhs.base() > rhs.base()); }

/*	(4)	*/
template <class Iter>
bool	ft::operator<=(const ft::Reverse_Iterator<Iter>& lhs, const ft::Reverse_Iterator<Iter>& rhs)
{ return (lhs.base() >= rhs.base()); }

/*	(5)	*/
template <class Iter>
bool	ft::operator>(const ft::Reverse_Iterator<Iter>& lhs, const ft::Reverse_Iterator<Iter>& rhs)
{ return (lhs.base() < rhs.base()); }

/*	(6)	*/
template <class Iter>
bool	ft::operator>=(const ft::Reverse_Iterator<Iter>& lhs, const ft::Reverse_Iterator<Iter>& rhs)
{ return (lhs.base() <= rhs.base()); }
