#if !defined(RAND_IT_HPP)
#define RAND_IT_HPP

// namespace ft
// {
	
	// iterator category
	struct random_access_iterator_tag {};
	
	// iterator traits
	template <class Iterator> 
	class iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

// } // namespace ft


#endif // RAND_IT_HPP
