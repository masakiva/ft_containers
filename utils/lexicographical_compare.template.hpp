/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.template.hpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:42:38 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/28 00:52:12 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEXICOGRAPHICAL_COMPARE_TEMPLATE_HPP__
# define __LEXICOGRAPHICAL_COMPARE_TEMPLATE_HPP__

namespace	ft
{

	// lexicographically compare the contents in a range of iterators
	// with the ones in another range
	template < class InputIt1, class InputIt2 >
		bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2 )
		{
			for ( ; ( first1 != last1 ) && ( first2 != last2 );
					++first1, ++first2 )
			{
				if ( *first1 < *first2 )
					return ( true );
				if ( *first2 < *first1 )
					return ( false );
			}
			return ( ( first1 == last1 ) && ( first2 != last2 ) );
		}

	template < class InputIt1, class InputIt2, class Compare >
		bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2, Compare comp )
		{
			for ( ; ( first1 != last1 ) && ( first2 != last2 );
					++first1, ++first2 )
			{
				if ( comp( *first1, *first2 ) )
					return ( true );
				if ( comp( *first2, *first1 ) )
					return ( false );
			}
			return ( ( first1 == last1 ) && ( first2 != last2 ) );
		}

} // namespace ft

#endif // __LEXICOGRAPHICAL_COMPARE_TEMPLATE_HPP__
