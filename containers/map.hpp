#if !defined(MAP_HPP)
#define MAP_HPP

#include <memory>
#include "../utils/pair.hpp"
#include "../avlTree/avlTree.hpp"
#include "../avlTree/avlIterator.hpp"
#include "../utils/reverse_iterator.hpp"

#include <iostream> // TODO remove
namespace ft
{
	/* map Container declaration */
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key key_type;
			typedef T 	mapped_type;

		private:
			typedef avlTree<key_type, mapped_type>	tree;
			typedef typename tree::node_type		node_type;
			typedef typename tree::node_pointer		node_pointer;


		public:
			typedef	Compare		key_compare;
			typedef ft::pair<const key_type, mapped_type> 	value_type;
			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type & x, const value_type & y) const	
					{
						std::cout << "Calling operator() in value_compare" << std::endl;
						return comp(x.first, y.first); 
					}
			};
			typedef Alloc											allocator_type;
			typedef typename Alloc::reference &						reference;
			typedef typename Alloc::const_reference &				const_reference;
			typedef typename Alloc::pointer &						pointer;
			typedef typename Alloc::const_pointer &					const_pointer;

			typedef typename tree::iterator							iterator;
			typedef typename tree::const_iterator					const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			// reverse const

			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;

		/* --- Member attributes --- */
		public : tree 			m_tree; //TODO hacer privado
		private:
			key_compare		m_keyCompare;
			allocator_type	m_alloc;
			size_type		m_size;
 		/* --- Member functions --- */
		public:
		// empty constructor
		explicit map(const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : 
			m_keyCompare(comp), m_alloc(alloc), m_size(0) { }
		// range constructor
		//template <class InputIterator> //TODO: cambiar a InputIterator
		map(iterator first, 
			iterator last,
			const key_compare& comp = key_compare(), 
			const allocator_type& alloc = allocator_type())
			 : m_alloc(alloc), m_keyCompare(comp)
		{
			insert(first, last);
		} 

		// copy constructor
		map(const map & x) : 
			m_tree(x.m_tree),
			m_keyCompare(x.m_keyCompare),
			m_alloc(x.m_alloc),
			m_size(x.m_size)			{ }
		// destructor
		~map() {};

		/* Iterators */
		iterator				begin(void) { return m_tree.begin(); }
		const_iterator			begin(void) const {return m_tree.cbegin(); }
		iterator				end(void) { return m_tree.end(); }
		const_iterator			end(void) const { return m_tree.cend(); }

		reverse_iterator		rbegin(void) { return m_tree.end(); }
		const_reverse_iterator	rbegin(void) const { return m_tree.cend(); }
		reverse_iterator		rend(void) { return m_tree.begin(); };
		const_reverse_iterator	rend(void) const { return m_tree.begin(); }

		 /* Operators */
		map& operator=(map const& rhs)
		{
			if (this != &rhs)
			{
				clear();
				m_alloc = rhs.m_alloc;
				m_keyCompare = rhs.m_keyCompare;
				insert(rhs.begin(), rhs.end());
			}
			return *this;
		}

		/* Element access */
		mapped_type& operator[] (const key_type& k)
		{
			node_pointer node = m_tree.findNode(k);
			if (node != NULL)
				return node->content.second;
			
			mapped_type val;
			value_type pair(k, val);
			ft::pair<iterator, bool> res = insert(pair);
			return res.first->second;
		}

		/* Capacity */
		bool		empty(void) const { return m_size == 0 ? true : false; }
		size_type	size(void) const { return m_size; }
		size_type	max_size(void) const { return m_alloc.max_size(); }

		/* Modifiers */
		ft::pair<iterator, bool> insert(const value_type & val)
		{
			 pair<node_pointer, bool> insert_res = m_tree.insert(val);
			 iterator it = iterator(m_tree.m_root, insert_res.first);
			 ft::pair<iterator, bool> res(it,insert_res.second);
			 m_size = m_tree.m_size;
			 return res;
		}
		iterator	insert(iterator position, const value_type & val)
		{
			position++; //TODO: comprobar hint

			ft::pair<iterator, bool> pair = insert(val);
			m_size = m_tree.m_size;
			return pair.first;
		}

		// template <class InputIterator> //TODO
		void	insert(iterator first, iterator last) //TODO: cambiar por InputIterator
		{
			while (first != last)
			{
			 	value_type val = *first;
				ft::pair<iterator, bool> res = insert(val);
				first++;
			}
			m_size = m_tree.m_size;
		}

		void erase(iterator position) { m_tree.remove(position); }
		size_type	erase(const key_type & k)
		{
			bool res = m_tree.remove(k);
			m_size = m_tree.m_size;
			return res == true ? 1 : 0;
		}
		void erase(iterator first, iterator last) 
		{
			while (first != last)
			{
				key_type key = first->first;
				++first;
				erase(key);
			}
		}

		void swap(map& x)
		{
			map tmp = *this;
			//*this = x;
			if (this != &x)
			{
				clear();
				m_alloc = x.m_alloc;
				m_keyCompare = x.m_keyCompare;
				insert(x.begin(), x.end());
			}
			x.clear();
			x.m_alloc = tmp.m_alloc;
			x.m_keyCompare = tmp.m_keyCompare;
			x.insert(tmp.begin(), tmp.end());
		}

		void clear()
		{
			iterator it1 = begin();
			iterator it2 = end();
			erase(it1, it2);
		}

		/* Observers */
		key_compare		key_comp(void) const { return m_keyCompare; }
		value_compare	value_comp(void) const { return value_compare(m_keyCompare); }

		 /* Operations */
		iterator		find(const key_type& k)
		{
			node_pointer node = m_tree.findNode(k);
			if (node)
				return iterator(m_tree.m_root, node);
			else
				return m_tree.end();
		}
		const_iterator	find(const key_type& k) const
		{
			node_pointer node = m_tree.findNode(k);
			if (node)
				return const_iterator(m_tree.m_root, node);
			else
				return m_tree.cend();
		}

		size_type		count(const key_type& k) const
		{
			node_pointer node = m_tree.findNode(k);
			return node == NULL ? 0 : 1;
		}

		iterator		lower_bound(const key_type& k)
		{
			iterator it = begin();			
			while (it != end())
			{
				bool res = m_keyCompare(it->first, k);
				if (!res)
					break;
				it++;
			}
			return it;
		}
		const_iterator	lower_bound(const key_type & k) const;

		iterator 		upper_bound(const key_type & k)
		{
			iterator it = begin();			
			while (it != end())
			{
				bool isless = m_keyCompare(it->first, k);
				bool isgreater = m_keyCompare(k, it->first);
				if (!isless && !isgreater) // is equal
				{
					it++;
					continue;
				}
				bool res = m_keyCompare(k, it->first);
				if (res)
					break;
				it++;
			}
			return it;				
		}
		const_iterator	upper_bound(const key_type & k) const;

		ft::pair<iterator, iterator>				equal_range (const key_type & k)
		{
			iterator lower = lower_bound(k);
			iterator upper = upper_bound(k);
			ft::pair<iterator, iterator> pair;
			pair.first = lower;
			pair.second = upper;			
			return pair;
		}
		ft::pair<const_iterator, const_iterator>	equal_range (const key_type & k) const;

	};
}


#endif // MAP_HPP
