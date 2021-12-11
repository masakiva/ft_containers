/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.template.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:21:39 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/28 00:51:17 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EQUAL_TEMPLATE_HPP__
# define __EQUAL_TEMPLATE_HPP__

namespace	ft
{

	// are the contents in a range of iterators equal to the ones
	// in another range
	template < class InputIt1, class InputIt2 >
	bool equal ( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
	{
		for ( ; first1 != last1; ++first1, ++first2 )
		{
			if ( !( *first1 == *first2 ) )
			{
				return ( false );
			}
		}
		return ( true );
	}

	template < class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal ( InputIt1 first1, InputIt1 last1, InputIt2 first2,
			BinaryPredicate p )
	{
		for ( ; first1 != last1; ++first1, ++first2 )
		{
			if ( !p( *first1, *first2 ) )
			{
				return ( false );
			}
		}
		return ( true );
	}

} // namespace ft

#endif // __EQUAL_TEMPLATE_HPP__
