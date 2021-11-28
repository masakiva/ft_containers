/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.template.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:43:38 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/28 00:44:24 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR_TEMPLATE_HPP__
# define __PAIR_TEMPLATE_HPP__

namespace	ft
{
	template < class T1, class T2 >
	struct	pair
	{
		typedef	T1		first_type;
		typedef	T2		second_type;

		T1		first;
		T2		second;

		/* default constructor */
		pair( void ) :
			first( first_type() ),
			second( second_type() )
		{ }

		/* copy constructor */
		template< class U1, class U2 >
			pair ( const pair<U1,U2>& src ) :
				first( src.first ),
				second( src.second )
		{ }

		/* initialization constructor */
		pair ( const first_type& a, const second_type& b ) :
			first( a ),
			second( b )
		{ }

		/* = */
		pair&	operator= ( const pair& rhs )
		{
			if ( this == &rhs )
				return ( *this );
			first = rhs.first;
			second = rhs.second;
			return ( *this );
		}

	}; // struct pair

	/* == */
	template < class T1, class T2 >
		bool	operator== ( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{ return ( lhs.first == rhs.first && lhs.second == rhs.second ); }

	/* != */
	template < class T1, class T2 >
		bool	operator!= ( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{ return ( !( lhs == rhs ) ); }

	/* < */
	template < class T1, class T2 >
		bool	operator<  ( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{ return ( lhs.first < rhs.first
				|| ( !( rhs.first < lhs.first )
					&& lhs.second < rhs.second ) ); }

	/* <= */
	template < class T1, class T2 >
		bool	operator<= ( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{ return ( !( rhs < lhs ) ); }

	/* > */
	template < class T1, class T2 >
		bool	operator>  ( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{ return ( rhs < lhs ); }

	/* >= */
	template < class T1, class T2 >
		bool	operator>= ( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{ return ( !( lhs < rhs ) ); }

	/* make_pair */
	template < class T1, class T2 >
		pair<T1,T2>		make_pair ( T1 x, T2 y )
		{
			return ( pair<T1,T2>( x, y ) );
		}

} // namespace ft

#endif // __PAIR_TEMPLATE_HPP__
