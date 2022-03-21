#if !defined(VECTOR_ITERATOR_HPP)
#define VECTOR_ITERATOR_HPP

# include <iostream> // TODO remove
# include <stdio.h>  // TODO remove
# include <limits>	
# include <exception>
# include "iterator.hpp" 
# include "iterator_traits.hpp"

# define logn(x) std::cout << x << std::endl
# define log(x) std::cout << x

namespace ft
{
	template <typename vector>
	struct vectorIterator
	{
		public:
		typedef typename vector::value_type 		value_type;
		typedef value_type				*pointer;
		typedef value_type const 		*const_pointer;
		typedef value_type				&reference;
		typedef value_type const 		&const_reference;
		typedef std::ptrdiff_t 			difference_type;
		typedef std::random_access_iterator_tag 	iterator_category;

		public:
		vectorIterator(pointer ptr) : m_ptr(ptr) {};

		vectorIterator& operator++() {
			m_ptr++;
			return *this;
		}
		vectorIterator operator++(int)
		{
			vectorIterator it = *this;
			++(*this);
			return it;
		}
		vectorIterator& operator--()
		{
			m_ptr--;
			return *this;
		}
		vectorIterator operator--(int)
		{
			vectorIterator it = *this;
			--(*this);
			return it;
		}
		vectorIterator &operator+=(int value) 
		{
			m_ptr += value;
			return *this;
		}
		vectorIterator &operator-=(int value) 
		{
			m_ptr -= value;
			return *this;
		}	
		vectorIterator operator+(int value)
		{
			vectorIterator it = *this;
			it += value;
			return it;			
		}
		vectorIterator operator-(int value)
		{
			vectorIterator it = *this;
			it -= value;
			return it;			
		}
		difference_type operator-(vectorIterator const &other) const 
		{
			return (m_ptr - other.m_ptr);
		}
		reference operator[](int index)
		{
			return *(m_ptr + index);
		}
		pointer operator->()
		{
			return m_ptr;
		}
		reference operator*()
		{
			return *m_ptr;
		}
		bool operator==(const vectorIterator& other) const
		{
			return (other.m_ptr == m_ptr);
		}
		bool operator!=(const vectorIterator& other) const
		{
			return (other.m_ptr != m_ptr);
		}

		private:
		pointer m_ptr;
	};
} // namespace ft

#endif