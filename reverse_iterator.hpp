#if !defined(REVERSE_ITERATOR_HPP)
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iterator>
	class reverse_iterator
	{
	private:
		Iterator m_baseit;

	public:
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

		// default constructor
		reverse_iterator() : m_baseit() { }
		// initialization constructor
		reverse_iterator(iterator_type it) : m_baseit(it) { }
		// copy constructor
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &other) : m_baseit(other.m_baseit) { }
		// destructor
		~reverse_iterator() { }

		iterator_type base() const { return m_baseit; }

		reference operator*() const
		{
			Iterator newIt(m_baseit);
			--newIt;
			return *newIt;
		}

		reverse_iterator operator+ (difference_type n)
		{
			m_baseit -= n;
			return *this;
		}

		reverse_iterator<Iterator> &operator++()
		{
			--m_baseit;
			return *this;
		}

		reverse_iterator<Iterator> operator++(int)
		{
			reverse_iterator<Iterator> it(m_baseit--);
			return it;
		}

		reverse_iterator<Iterator> &operator+=(difference_type offset)
		{
			m_baseit -= offset;
			return *this;
		}

		reverse_iterator operator- (difference_type n)
		{
			m_baseit += n;
			return *this;
		}

		reverse_iterator<Iterator> &operator--()
		{
			++m_baseit;
			return *this;
		}

		reverse_iterator<Iterator> operator--(int)
		{
			reverse_iterator<Iterator> it(m_baseit++);
			return it;
		}

		reverse_iterator<Iterator> &operator-=(difference_type offset)
		{
			m_baseit += offset;
			return *this;
		}

		pointer operator->() const
		{
			Iterator it(m_baseit);
			--it;
			return it.operator->();
		}

		reverse_iterator<Iterator> &operator=(const reverse_iterator<Iterator> &other)
		{
			m_baseit = other.m_baseit;
			return *this;
		}

		reference operator[] (difference_type n) const
		{
			return m_baseit[-n-1];
		}

	};

	template <typename Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename Iterator>
	reverse_iterator<Iterator> operator+(const reverse_iterator<Iterator> &it, size_t n)
	{
		reverse_iterator<Iterator> r(it.base() - n);
		return r;
	}

	template <typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &it)
	{
		reverse_iterator<Iterator> r(it.base() - n);
		return r;
	}

	template <typename Iterator>
	reverse_iterator<Iterator> operator-(const reverse_iterator<Iterator> &it, typename reverse_iterator<Iterator>::difference_type n)
	{
		reverse_iterator<Iterator> r(it.base() + n);
		return r;
	}

	template <typename Iterator>
	ptrdiff_t operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return rhs.base() - lhs.base();
	}

	// // Operators

	// template <typename T>
	// struct Less
	// {
	// 	bool operator()(const T &lhs, const T &rhs) const
	// 	{
	// 		return lhs < rhs;
	// 	}
	// };

	// template <typename T>
	// void swap(Less<T> const &x, Less<T> const &y)
	// {
	// 	(void)x;
	// 	(void)y;
	// }

	// template <typename T>
	// struct Equal
	// {
	// 	bool operator()(const T &lhs, const T &rhs) const
	// 	{
	// 		return lhs == rhs;
	// 	}
	// };

	// template <typename T>
	// void swap(Equal<T> const &x, Equal<T> const &y)
	// {
	// 	(void)x;
	// 	(void)y;
	// }

	// // lexicographical compare

	// template <
	// 	typename InputIt1,
	// 	typename InputIt2,
	// 	typename Compare = Less<typename IteratorTraits<InputIt1>::value_type>>
	// bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
	// 							 InputIt2 first2, InputIt2 last2,
	// 							 Compare comp = Compare())
	// {
	// 	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	// 	{
	// 		if (comp(*first1, *first2))
	// 			return true;
	// 		if (comp(*first2, *first1))
	// 			return false;
	// 	}
	// 	return (first1 == last1) && (first2 != last2);
	// }

	// // equal

	// template <typename InputIt1, typename InputIt2>
	// bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	// {
	// 	for (; first1 != last1; ++first1, ++first2)
	// 		if (*first1 != *first2)
	// 			return false;
	// 	return true;
	// }

	// // min / max

	// template <typename T>
	// const T &min(const T &a, const T &b)
	// {
	// 	return a < b ? a : b;
	// }

	// template <typename T>
	// const T &max(const T &a, const T &b)
	// {
	// 	return a < b ? b : a;
	// }

	// // copy / move / fill

	// template <typename InputIt1, typename InputIt2>
	// InputIt2 copy(InputIt1 first, InputIt1 last, InputIt2 dest_first)
	// {
	// 	while (first != last)
	// 		*dest_first++ = *first++;
	// 	return dest_first;
	// }

	// template <typename InputIt1, typename InputIt2>
	// InputIt2 move(InputIt1 first, InputIt1 last, InputIt2 dest_first)
	// {
	// 	return copy(first, last, dest_first);
	// }

	// template <typename InputIt1, typename InputIt2>
	// InputIt2 copy_backward(InputIt1 first, InputIt1 last, InputIt2 dest_last)
	// {
	// 	while (first != last)
	// 		*(--dest_last) = *(--last);
	// 	return dest_last;
	// }

	// template <typename InputIt1, typename InputIt2>
	// InputIt2 move_backward(InputIt1 first, InputIt1 last, InputIt2 dest_last)
	// {
	// 	return copy_backward(first, last, dest_last);
	// }

	// template <typename InputIt, typename T>
	// void fill(InputIt first, InputIt last, const T &val)
	// {
	// 	for (; first != last; ++first)
	// 	{
	// 		*first = val;
	// 	}
	// }

	// template <typename InputIt1, typename InputIt2>
	// InputIt2 uninitialized_copy(InputIt1 first, InputIt1 last, InputIt2 dest_first)
	// {
	// 	typedef typename IteratorTraits<InputIt2>::value_type Value;
	// 	for (; first != last; ++first, ++dest_first)
	// 	{
	// 		::new (static_cast<void *>(&*dest_first)) Value(*first);
	// 	}
	// 	return dest_first;
	// }

	// template <typename InputIt1, typename InputIt2>
	// InputIt2 uninitialized_move(InputIt1 first, InputIt1 last, InputIt2 dest_first)
	// {
	// 	return uninitialized_copy(first, last, dest_first);
	// }

	// template <typename InputIt, typename T>
	// void uninitialized_fill(InputIt first, InputIt last, const T &val)
	// {
	// 	typedef typename IteratorTraits<InputIt>::value_type Value;
	// 	for (; first != last; ++first)
	// 	{
	// 		::new (static_cast<void *>(&*first)) Value(val);
	// 	}
	// }
} // namespace ft


#endif // REVERSE_ITERATOR_HPP
