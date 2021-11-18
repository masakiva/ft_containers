/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:21:39 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/18 18:27:52 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EQUAL_HPP__
# define __EQUAL_HPP__

namespace	ft
{
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
}

#endif // __EQUAL_HPP__
