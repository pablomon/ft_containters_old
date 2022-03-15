#if !defined(VECTOR_HPP)
#define VECTOR_HPP

# include <iostream> // TODO remove
# include <stdio.h>  // TODO remove
# include <exception>
# include "randIt.hpp"

# define logn(x) std::cout << x << std::endl
# define log(x) std::cout << x

namespace ft
{
	template <typename vector>
	class vectorIterator
	{
		public:
		typedef typename vector::value_type value_type;
		typedef value_type* pointer_type;
		typedef value_type& reference_type;

		public:
		vectorIterator(pointer_type ptr) : m_ptr(ptr) {};

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
		vectorIterator operator--()
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
		reference_type operator[](int index)
		{
			return *(m_ptr + index);
		}
		pointer_type operator->()
		{
			return m_ptr;
		}
		reference_type operator*()
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
			// return (!(*this == other));
		}

		private:
		pointer_type m_ptr;
	};
} // namespace ft


namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
		/* 
		 Member types -------------------------------------
		*/
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef typename ft::vectorIterator<ft::vector<value_type> >		iterator;
		typedef typename ft::vectorIterator<ft::vector<const value_type> >	const_iterator;
		//typedef typename reverse_iterator
		//typedef typename const_reverse_iterator
		typedef std::ptrdiff_t								difference_type;
		typedef typename allocator_type::size_type			size_type;

		private:
		/*
		 Member variables & Functions -----------------------
		*/
		size_t m_capacity;
		size_t m_size;
		T* m_data;
		Alloc m_alloc;

		void realloc(size_t newCapacity)
		{
			std::cout << "Realloc new capacity = " << newCapacity << "\n";
			T* newBlock = m_alloc.allocate(newCapacity);

			if (newCapacity < m_size)
				m_size = newCapacity;

			for (size_t i = 0; i < m_size; i++)
				m_alloc.construct(newBlock + i, m_data[i]);

			if (m_data)
			{
				for (size_t i = 0; i < m_size; i++)
					m_alloc.destroy(m_data + i);
				m_alloc.deallocate(m_data, m_size);
			}

			m_data = newBlock;
			m_capacity = newCapacity;			
		}

		public:
		/*
		 Constructors -------------------------------------
		*/
		
		// default constructor
		explicit vector (const allocator_type& alloc = allocator_type())
		{
			std::cout << "Constructor default\n";
			m_alloc = alloc;
			m_capacity = 0;
			m_size = 0;
			m_data = NULL;
			realloc(2); // empiezo con 2 siempre		
		}
		
		// fill constructor
		explicit vector (size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type())
		{
			std::cout << "Constructor fill\n";
			m_alloc = alloc;
			m_capacity = 0;
			m_size = 0;
			m_data = NULL;
			for (size_t i = 0; i < n; i++)
			{
				push_back(val); //TODO cambiar por construct
			}
		}

		// range constructor
        vector (iterator first, iterator last,
        	const allocator_type& alloc = allocator_type()) //TODO enable_if
		{
			std::cout << "Range constructor\n";
			m_alloc = alloc;
			m_capacity = 0;
			m_data = NULL;
			m_size = 0;
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		// copy constructor
		vector (const vector& other)
		{
			std::cout << "Constructor copy\n";
			m_alloc = other.m_alloc;
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_data = m_alloc.allocate(m_capacity);
			for(size_t i=0; i<m_size; i++)
			{
				m_alloc.construct(m_data + i, other.m_data[i]);
			}
		}

		~vector()
		{
			std::cout << "Destructor called\n";
			clear();
			if (m_capacity > 0)
			{
				m_alloc.deallocate(m_data, m_capacity);
				m_capacity = 0;
			}
		}

		vector &operator= (const vector& other)
		{
			std::cout << "Assignment operator\n";
			if (other == *this)
				return *this;
			return this->vector(other);
		}

		/* 
		 Iterators ---------------------------------
		*/
		iterator begin()
		{
			return iterator(m_data);
		}


		// const_iterator begin() const;
		iterator end()
		{
			return iterator(m_data + m_size);
		}
		// const_iterator end() const;
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;
		/* 
		 Element access ----------------------------
		*/
		
		// if index is out of range => undefined behaviour
		reference operator[](size_t index) { return m_data[index]; }
		const_reference operator[](size_t index) const { return m_data[index]; }
		reference at (size_type n)
		{
			if (n >= m_size)
				throw std::out_of_range("index n exceeds the vector size");
			return m_data[n];
		}
		const_reference at (size_type n) const
		{
			if (n >= m_size)
				throw std::out_of_range("index n exceeds the vector size");
			return m_data(n);
		}
		// if vector is empty => undefined behaviour
		reference front() { return m_data[0]; }
		const_reference front() const { return m_data[m_size]; }
		// if vector is empty => undefined behaviour
		reference back() { return m_data[m_size - 1]; }
		const_reference back() const { return m_data[m_size - 1]; }
		
		/*
		 Modifiers -----------------------------------------
		*/
		void push_back(const T& value)
		{
			if (m_size >= m_capacity)
				realloc((1 + m_capacity) * 1.5f);
			
			m_data[m_size] = value;
			m_size++;
		}

		// template <class InputIterator>
  		void assign (iterator first, iterator last) // TODO template, enable_if
		{
			clear();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		void assign (size_type n, const value_type& val)
		{
			clear();
			for (size_type i = 0; i < n; i++)
			{
				push_back(val);
			}
			
		}
		void pop_back()	
		{
			m_size--;
			std::cout << "popping " << m_data[m_size] << std::endl;
			m_alloc.destroy(m_data + m_size);
		}

		//TODO: insert
		iterator insert (iterator position, const value_type& val)
		{
			int dist = 0;
			iterator it = begin();
			while (it != position)
			{
				dist++;
				it++;
			}
			int newCapacity = (m_size + 1) * 1.5f;
			T* newBlock = m_alloc.allocate(newCapacity);
			for (int i = 0; i < dist; i++)
			{
				m_alloc.construct(newBlock + i, m_data[i]);
				m_alloc.destroy(m_data + i);
			}
			m_alloc.construct(newBlock + dist, val);
			for (int i = dist + 1; i < m_size + 1; i++)
			{
				m_alloc.construct(newBlock + i, m_data[i - 1]);
				m_alloc.destroy(m_data + i - 1);
			}
			
			m_alloc.deallocate(m_data, m_size);
			m_size++;
			m_capacity = newCapacity;
			m_data = newBlock;
			return position;
		}
		void insert (iterator position, size_type n, const value_type& val)
		{

		}
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last)
		{

		}
		//TODO: erase
		//TODO: swap
		void clear()
		{
			for (size_t i = 0; i < m_size; i++)
			{
				m_alloc.destroy(m_data + i);
			}
			m_size = 0;
		}

		/*
		 Capacity ------------------------------------------
		*/
		size_t size() const { return m_size; };


	};

} // ft namespace

#endif // VECTOR_HPP
