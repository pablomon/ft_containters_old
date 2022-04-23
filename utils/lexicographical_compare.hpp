#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft 
{
	template < class InputIt1 , class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt1 last2 )
	{
		for(; ( first1 != last1 ) && ( first2 != last2 ); first1++, first2++)
		{
			if ( *first1 < *first2 ) return true;
			if ( *first2 < *first1 ) return false;
		}
		if (first1 == last1 && first2 != last2)
			return true;
		return false;
	}

	template < class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2,
								InputIt2 last2, Compare compare )
	{
		for(; ( first1 != last1 ) && ( first2 != last2 ); first1++, first2++ )
		{
			if ( compare( *first1, *first2 ) ) 
				return true;
			if ( compare( *first2, *first1 ) ) 
				return false;
		}
		if (first1 == last1 && first2 != last2)
			return true;
		return false;
	}
}

#endif