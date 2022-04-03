#include "./Vector.hpp"
#include <limits>

/* Constructor */
/* default	(1)	*/
template <typename Type, class Alloc>
ft::vector<Type, Alloc>::vector(const allocator_type & alloc) : _alloc(alloc), _size(0), _head(NULL), _tail(NULL), _end(NULL)
{}

/* fill		(2)	*/
template <typename Type, class Alloc>
ft::vector<Type, Alloc>::vector(size_type n, const value_type & val, const allocator_type & alloc) : _alloc(alloc), _size(0), _head(NULL), _tail(NULL), _end(NULL)
{
	_add_n_values_from_int(n, val);
}

/* range	(3)	*/
template <typename Type, class Alloc>
template <class InputIterator>
ft::vector<Type, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type & alloc) : _alloc(alloc), _size(0), _head(NULL), _tail(NULL), _end(NULL)
{
	_add_values_from_iterators(first, last, typename ft::is_integral<InputIterator>::type());
}

/* copy		(4)	*/
template <typename Type, class Alloc>
ft::vector<Type, Alloc>::vector(const vector& x) : _alloc(x._alloc), _size(0), _head(NULL), _tail(NULL), _end(NULL)
{
	_head = _alloc.allocate(x.size());
	_size = x.size();
	for (size_type i = 0; i < size(); ++i)
		_alloc.construct(_head + i, x[i]);
	_tail = _head + _size;
	_end = _tail;
}


/* Destructor */
template <typename Type, class Alloc>
ft::vector<Type, Alloc>::~vector(void)
{
	clear();
	_alloc.deallocate(_head, capacity());
}


/* Operators */
/* assignation	(1)	*/
template <typename Type, class Alloc>
ft::vector<Type, Alloc> &	ft::vector<Type, Alloc>::operator=(vector const & rhs)
{
	if (this != &rhs)
	{
		if (rhs.size() > capacity())
			_reallocate(rhs.size(), 0);
		else
			clear();

		Type * this_tmp = this->_head;
		Type * rhs_tmp = rhs._head;

		while (rhs_tmp != rhs._tail)
		{
			this->_alloc.construct(this_tmp, *rhs_tmp);
			++this_tmp;
			++rhs_tmp;
		}
		_tail = this_tmp;
		_size = rhs._size;

	}
	return (*this);
}


/* Iterators */
template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::iterator	ft::vector<Type, Alloc>::begin(void)
{ return (iterator(_head)); }

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::const_iterator	ft::vector<Type, Alloc>::begin(void) const
{ return (const_iterator(_head)); }

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::iterator	ft::vector<Type, Alloc>::end(void)
{ return (iterator(_tail)); }

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::const_iterator	ft::vector<Type, Alloc>::end(void) const
{ return (const_iterator(_tail)); }

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::reverse_iterator	ft::vector<Type, Alloc>::rbegin(void)
{ return (reverse_iterator(_tail - 1)); }

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::const_reverse_iterator	ft::vector<Type, Alloc>::rbegin(void) const
{ return (const_reverse_iterator(_tail - 1)); }

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::reverse_iterator	ft::vector<Type, Alloc>::rend(void)
{ return (reverse_iterator(_head - 1)); }

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::const_reverse_iterator	ft::vector<Type, Alloc>::rend(void) const
{ return (const_reverse_iterator(_head - 1)); }


/* Capacity */
template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::size_type	ft::vector<Type, Alloc>::size(void) const
{
	return (_size);
}

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::size_type	ft::vector<Type, Alloc>::max_size(void) const
{
	return (std::min(_alloc.max_size(), static_cast<unsigned long>(std::numeric_limits<difference_type>::max())));
}

template <typename Type, class Alloc>
void	ft::vector<Type, Alloc>::resize(size_type n, value_type val)
{
	if (n >= capacity())
	{
		if (n == capacity())
			_reallocate(n, 0);
		else if (n <= 2 * size())
			_reallocate(n, -1);
		else
			_reallocate(n, 0);
		while (n > size())
		{
			_alloc.construct(_tail, val);
			++_tail;
			++_size;
		}
	}
	else
	{
		while (n < size())
			pop_back();
	}
}

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::size_type	ft::vector<Type, Alloc>::capacity(void) const
{
	return (static_cast<size_type>(_end - _head));
}

template <typename Type, class Alloc>
bool	ft::vector<Type, Alloc>::empty(void) const
{
	return (_size == 0);
}

template <typename Type, class Alloc>
void	ft::vector<Type, Alloc>::reserve(size_type n)
{
	if (n > capacity())
	{
		size_type new_size = size();
		if (n > size())
		{
			Type * head_tmp = _alloc.allocate(n);
			_check_max_size(n);
			for (size_type i = 0; i < size(); i++)
				_alloc.construct(head_tmp + i, _head[i]);
			clear();
			_alloc.deallocate(_head, capacity());
			_head = head_tmp;
			_tail = _head + new_size;
			_end = _head + n;
			_size = new_size;
		}
	}
}

/* Element access */
template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::reference	ft::vector<Type, Alloc>::operator[](size_type n)
{
	return (_head[n]);
}

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::const_reference	ft::vector<Type, Alloc>::operator[](size_type n) const
{
	return (_head[n]);
}

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::reference	ft::vector<Type, Alloc>::at(size_type n)
{
	_check_out_of_bound(n);
	return (_head[n]);
}

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::const_reference	ft::vector<Type, Alloc>::at(size_type n) const
{
	_check_out_of_bound(n);
	return (_head[n]);
}

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::reference	ft::vector<Type, Alloc>::front(void)
{
	return (*_head);
}

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::const_reference	ft::vector<Type, Alloc>::front(void) const
{
	return (*_head);
}

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::reference	ft::vector<Type, Alloc>::back(void)
{
	return (*(_tail - 1));
}

template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::const_reference	ft::vector<Type, Alloc>::back(void) const
{
	return (*(_tail - 1));
}


/* Modifiers */
/* range	(1)	*/
template <typename Type, class Alloc>
template <class InputIterator>
void	ft::vector<Type, Alloc>::assign(InputIterator first, InputIterator last)
{
	ft::vector<Type, Alloc> tmp(first, last, _alloc);
	
	if (tmp.size() > capacity())
		_reallocate(tmp.size(), 0);
	else
		clear();

	Type * this_tmp = this->_head;
	Type * rhs_tmp = tmp._head;

	while (rhs_tmp != tmp._tail)
	{
		this->_alloc.construct(this_tmp, *rhs_tmp);
		++this_tmp;
		++rhs_tmp;
	}
	_tail = this_tmp;
	_size = tmp._size;
}
	
/* fill		(2)	*/
template <typename Type, class Alloc>
void	ft::vector<Type, Alloc>::assign(size_type n, const value_type & val)
{
	ft::vector<Type, Alloc> tmp(n, val, _alloc);
	if (tmp.size() > capacity())
		_reallocate(tmp.size(), 0);
	else
		clear();

	Type * this_tmp = this->_head;
	Type * rhs_tmp = tmp._head;

	while (rhs_tmp != tmp._tail)
	{
		this->_alloc.construct(this_tmp, *rhs_tmp);
		++this_tmp;
		++rhs_tmp;
	}
	_tail = this_tmp;
	_size = tmp._size;
}

template <typename Type, class Alloc>
void	ft::vector<Type, Alloc>::push_back(const value_type & val)
{
	if (_tail == _end)
		_reallocate(size() + 1, 1);
	_alloc.construct(_tail, val);
	++_size;
	++_tail;
}

template <typename Type, class Alloc>
void	ft::vector<Type, Alloc>::pop_back(void)
{
	--_size;
	--_tail;
	_alloc.destroy(_tail);
}

/* single element	(1)	*/
template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::iterator	ft::vector<Type, Alloc>::insert(iterator position, const value_type & val)
{
	difference_type	diff = iterator(_tail) - position;
	size_type d = static_cast<size_type>(diff);

	if (size() + 1 > capacity())
		_reallocate(size() + 1, 1);

	size_type i = 0;

	while (i < d)
	{
		memmove(static_cast<void*>(&(operator[](size() - i))), static_cast<void*>(&(operator[](size() - i - 1))), sizeof(Type));
		++i;
	}
	_alloc.construct(&(operator[](size() - i)), val);
	iterator ret(&(operator[](size() - i)));
	++_size;
	_head = &_head[0];
	_tail = &_head[size()];
	position++;
	return (ret);
}

/* fill				(2)	*/
template <typename Type, class Alloc>
void		ft::vector<Type, Alloc>::insert(iterator position, size_type n, const value_type & val)
{
	iterator tmp(position);
	for (size_type i = 0; i < n; i++)
		tmp = insert(tmp, val);
}

/* range			(3)	*/
template <typename Type, class Alloc>
template <class InputIterator>
void		ft::vector<Type, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
{
	_insert_values_from_iterators(position, first, last, typename ft::is_integral<InputIterator>::type());
}

/* single element	(1)	*/
template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::iterator	ft::vector<Type, Alloc>::erase(iterator position)
{
	iterator ret = erase(position, position + 1);
	return (ret);
}

/* range			(2)	*/
template <typename Type, class Alloc>
typename ft::vector<Type, Alloc>::iterator	ft::vector<Type, Alloc>::erase(iterator first, iterator last)
{
	difference_type	diff = last - first;
	iterator tmp;
	iterator ret = first;

	while (first != last)
	{
		tmp = first;
		first++;
		_alloc.destroy(&(*tmp));
		if (tmp + diff < end())
			_alloc.construct(&(*tmp), *(tmp + diff));
	}
	if (end() - last - diff > 0)
		memmove(static_cast<void*>(&(*last)), static_cast<void*>(&(*(last + diff))), static_cast<size_type>((end() - last) - diff) * sizeof(Type));
	_tail -= diff;
	_size -= static_cast<size_type>(diff);
	return (ret);
}

template <typename Type, class Alloc>
void	ft::vector<Type, Alloc>::swap(vector & x)
{
	Type * head_tmp;
	Type * tail_tmp;
	Type * end_tmp;
	size_t size_tmp;

	head_tmp = x._head;
	tail_tmp = x._tail;
	end_tmp = x._end;
	size_tmp = x._size;

	x._head = this->_head;
	x._tail = this->_tail;
	x._end = this->_end;
	x._size = this->_size;

	this->_head = head_tmp;
	this->_tail = tail_tmp;
	this->_end = end_tmp;
	this->_size = size_tmp;
}

template <typename Type, class Alloc>
void	ft::vector<Type, Alloc>::clear(void)
{
	Type * tmp(_head);
	while (tmp != _end)
	{
		Type * to_destroy = tmp;
		tmp++;
		_alloc.destroy(to_destroy);
	}
	_size = 0;
	_tail = _head;
}

/* Observers -- not implemented -- */
// allocator_type	get_allocator(void) const;

/* --- Private functions --- */
template <class Type, class Alloc>
void	ft::vector<Type, Alloc>::_reallocate(size_type n, int twice)
{
	size_type new_capacity = n;
	size_type new_size = size();

	if (n > size())
	{
		if (twice == 1 && n <= 2 * size())
			new_capacity = 2 * size();
		else if (twice == -1 && n <= 2 * size())
			new_capacity = 2 * capacity();
		
		Type * head_tmp = _alloc.allocate(new_capacity);
		for (size_type i = 0; i < size(); ++i)
			_alloc.construct(head_tmp + i, _head[i]);
		clear();
		_alloc.deallocate(_head, capacity());
		_head = head_tmp;
		_tail = _head + new_size;
		_end = _head + new_capacity;
		_size = new_size;
	}
	else if (n < size())
	{
		Type * head_tmp = _alloc.allocate(new_capacity);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(head_tmp + i, _head[i]);
		clear();
		_alloc.deallocate(_head, capacity());
		_head = head_tmp;
		_tail = _head + n;
		_end = _head + new_capacity;
		_size = n;
	}
}

template <class T, class Alloc>
void	ft::vector<T, Alloc>::_check_max_size(size_type n) const throw(std::length_error)
{
	if (n > max_size())
		throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
}

template <class T, class Alloc>
void	ft::vector<T, Alloc>::_check_out_of_bound(size_type n) const throw(std::out_of_range)
{
	if (n > size())
		throw std::out_of_range("vector");
}

template <typename Type, class Alloc>
void	ft::vector<Type, Alloc>::_add_n_values_from_int(size_type n, const value_type & val)
{
	_head = _alloc.allocate(n);
	for (size_type i = 0; i < n; i++)
		_alloc.construct(_head + i, val);
	_size += n;
	_end = _tail = (_head + _size);
}

template <typename Type, class Alloc>
template <class InputIterator>
void	ft::vector<Type, Alloc>::_add_values_from_iterators(InputIterator & first, InputIterator & last, void *)
{
	_head = _alloc.allocate(static_cast<size_type>(last - first));
	size_type n = 0;
	while (first != last)
	{
		_alloc.construct(_head + n, *first);
		++first;
		++n;
	}
	_size += n;
	_end = _tail = (_head + _size);
}

template <typename Type, class Alloc>
template <class InputIterator>
void	ft::vector<Type, Alloc>::_add_values_from_iterators(InputIterator & first, InputIterator & last, int)
{
	_add_n_values_from_int(static_cast<size_t>(first), static_cast<value_type>(last));
}

template <typename Type, class Alloc>
template <class InputIterator>
void	ft::vector<Type, Alloc>::_insert_values_from_iterators(iterator position, InputIterator & first, InputIterator & last, void *)
{
	iterator tmp(position);
	while (first != last)
	{
		tmp = insert(tmp, *first);
		first++;
	}
}

template <typename Type, class Alloc>
template <class InputIterator>
void	ft::vector<Type, Alloc>::_insert_values_from_iterators(iterator position, InputIterator & first, InputIterator & last, int)
{
	insert(position, static_cast<size_type>(first), static_cast<value_type>(last));
}


/* --- Non-member function overloads --- */
/*	(1)	*/
template <class T, class Alloc>
bool	ft::operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	
	typename ft::vector<T, Alloc>::const_iterator lhs_begin = lhs.begin();
	typename ft::vector<T, Alloc>::const_iterator lhs_end = lhs.end();
	typename ft::vector<T, Alloc>::const_iterator rhs_begin = rhs.begin();
	while (lhs_begin != lhs_end)
	{
		if (!(*lhs_begin == *rhs_begin))
			return (false);
		++lhs_begin;
		++rhs_begin;
	}
	return (true);
}

/*	(2)	*/
template <class T, class Alloc>
bool	ft::operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{ return (!(lhs == rhs)); }

/*	(3)	*/
template <class T, class Alloc>
bool	ft::operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	typename ft::vector<T, Alloc>::const_iterator lhs_begin = lhs.begin();
	typename ft::vector<T, Alloc>::const_iterator lhs_end = lhs.end();
	typename ft::vector<T, Alloc>::const_iterator rhs_begin = rhs.begin();
	typename ft::vector<T, Alloc>::const_iterator rhs_end = rhs.end();

	/* Lexicographical_compare */
	while (lhs_begin != lhs_end)
	{
		if (rhs_begin == rhs_end || *rhs_begin < *lhs_begin)
			return (false);
		else if (*lhs_begin < *rhs_begin)
			return (true);
		++lhs_begin;
		++rhs_begin;
	}
	return (rhs_begin != rhs_end);
}

/*	(4)	*/
template <class T, class Alloc>
bool	ft::operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{ return (!(rhs < lhs)); }

/*	(5)	*/
template <class T, class Alloc>
bool	ft::operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{ return (rhs < lhs); }

/*	(6)	*/
template <class T, class Alloc>
bool	ft::operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{ return (!(lhs < rhs)); }

template <class T, class Alloc>
void	ft::swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
{
	x.swap(y);
}