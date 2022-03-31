#if !defined(STACK_HPP)
#define STACK_HPP

# include "../containers/vector.hpp"
# include "../containers/vector_it.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
		public:
		/*
		 Member types -------------------------------------
		*/
		typedef  Container 						container_type;
		typedef  typename Container::value_type 		value_type;
		typedef  typename Container::size_type 			size_type;
		typedef  typename Container::reference 			reference;
		typedef  typename Container::const_reference 	const_reference;

		private:
		container_type m_container;

		public:
		/*
		 Constructors -------------------------------------
		*/
		// Constructor
		explicit stack (const container_type& ctnr = container_type()) : m_container(ctnr) {}
		// Copy constructor
		stack ( stack const& other) : m_container(other.m_container) {}
		// Destructor
		~stack() {} // TODO: virtual ?? 
		// Operator equal
		stack& operator=( const stack& other )
		{
			m_container = other.m_container;
			return *this;
		}

		/*
		 Member variables & Functions -----------------------
		*/
		bool empty() const { return m_container.empty(); }
		size_type size() const { return m_container.size(); }
		reference top() { return m_container.back(); }
		const_reference top() const { return m_container.back(); }
		void push (const value_type& val) { m_container.push_back(val); };
		void pop() { m_container.pop_back(); }

		/*
		 Friends so they can access private members
		*/
		friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	};

	/*
	Relational operators -------------------------------------
	*/
	template <class T, class Container>
	bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return lhs.m_container == rhs.m_container;
	}
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs.m_container == rhs.m_container);
	}
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.m_container < rhs.m_container;
	}
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.m_container <= rhs.m_container;
	}
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.m_container > rhs.m_container;
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.m_container >= rhs.m_container;
	}
	
} // namespace ft


#endif // STACK_HPP
