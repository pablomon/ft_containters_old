#if !defined(VECTOR_HPP)
#define VECTOR_HPP

# include <iostream> // TODO remove
# include <exception>


// namespace ft
// {
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
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
			// TODO usar custom allocator
			T* newBlock = new T[newCapacity];

			if (newCapacity < m_size)
				m_size = newCapacity;

			for (size_t i = 0; i < m_size; i++)
			{
				newBlock[i] = m_data[i];
			}

			if (m_data)
				delete[] m_data;
			m_data = newBlock;
			m_capacity = newCapacity;			
		}

		public:
		/* 
		 Member types -------------------------------------
		*/
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		// typedef random_access_iterator<value_type> iterator;
		
		
		typedef typename allocator_type::size_type          size_type;
		
		/*
		 Constructors -------------------------------------
		*/
		explicit vector (const allocator_type& alloc = allocator_type())
		{
			std::cout << "Constructor no args\n";
			m_alloc = alloc;
			m_capacity = 0;
			m_size = 0;
			m_data = NULL;
			realloc(2); // empiezo con 2 siempre			
		}

		vector (const vector& other)
		{
			std::cout << "Constructor copy\n";
			m_capacity = 0;
			m_size = 0;
			m_data = NULL;
			clear();
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_data = new T[other.m_capacity];
			for(size_t i=0; i<m_size; i++)
				m_data[i] = other.m_data[i];
		}
		~vector()
		{
			std::cout << "Destructor called\n";
			clear();
			//TODO deallocate allocator
		}
		vector &operator= (const vector& other)
		{
			std::cout << "Assignment operator\n";
			if (other == *this)
				return *this;
			clear();
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_data = new T[other.m_capacity];
			for(size_t i=0; i<m_size; i++)
				m_data[i] = other.m_data[i];
		}

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
				realloc(m_capacity * 1.5f);
			
			m_data[m_size] = value;
			m_size++;
		}

		//TODO: assign
		void pop_back()	{ m_size--;	}
		//TODO: insert
		//TODO: erase
		//TODO: swap
		void clear()
		{
			delete[] m_data;
			m_size = 0;
			m_capacity = 0;
		}

		/*
		 Capacity ------------------------------------------
		*/
		size_t size() const { return m_size; };


	};

// }

#endif // VECTOR_HPP


template <typename T>
void PrintVector(const vector<T>& vector)
{
	std::cout << "---------" << std::endl;
	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << std::endl;
	}
	std::cout << "---------" << std::endl;
}
