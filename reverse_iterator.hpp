/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:07:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/13 17:22:00 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __REVERSE_ITERATOR_HPP__
# define __REVERSE_ITERATOR_HPP__

#include "iterator_traits.hpp"

namespace	ft
{
	template < class Iterator >
	class reverse_iterator
	{
		public:

			typedef	Iterator
				iterator_type;
			typedef	typename iterator_traits<Iterator>::iterator_category
				iterator_category;
			typedef	typename iterator_traits<Iterator>::value_type
				value_type;
			typedef	typename iterator_traits<Iterator>::difference_type
				difference_type;
			typedef	typename iterator_traits<Iterator>::pointer
				pointer;
			typedef	typename iterator_traits<Iterator>::reference
				reference;

		private:

			Iterator	_it;

		public:

			/* default constructor */
			reverse_iterator ( void ) { }

			/* parameterized constructor */
			explicit reverse_iterator ( iterator_type it ) : _it(it - 1) { }

			/* copy constructor */
			reverse_iterator ( const reverse_iterator<Iterator>& src )
			{ *this = src; }

			/* destructor */
			~reverse_iterator ( void ) { }

			/* = */
			reverse_iterator&	operator= ( const reverse_iterator& rhs )
			{
				if ( this == &rhs )
					return ( *this );
				_it = rhs._it;
				return ( *this );
			}

			/* base */
			iterator_type		base( void ) const { return ( _it + 1 ); }

			/* * */
			reference			operator* ( void ) const { return ( *_it ); }

			/* -> */
			pointer		operator-> ( void ) const
			{ return ( &( operator*() ) ); }

			/* ++i */
			reverse_iterator&	operator++( void ) { _it--; return ( *this ); }

			/* i++ */
			reverse_iterator 	operator++( int )
			{
				reverse_iterator	before_inc( *this );
				_it--;
				return ( before_inc );
			}

			/* i-- */
			reverse_iterator 	operator--( int )
			{
				reverse_iterator	before_dec( *this );
				_it++;
				return ( before_dec );
			}

			/* += */
			reverse_iterator&	operator+= ( difference_type n )
			{ _it -= n; return ( *this ); }

			/* -= */
			reverse_iterator&	operator-= ( difference_type n )
			{ _it += n; return ( *this ); }

			/* + */
			reverse_iterator	operator+ ( difference_type n ) const
			{ reverse_iterator temp( *this ); return ( temp.operator+=( n ) ); }

			/* - */
			reverse_iterator	operator- ( difference_type n ) const
			{ reverse_iterator temp( *this ); return ( temp.operator-=( n ) ); }

			/* [] */
			reference			operator[] ( difference_type n ) const
			{ return ( base()[-1 * n - 1] ); }

	};

	/* == */
	template < class Iterator >
		bool operator== ( const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs )
		{ return ( lhs.base() == rhs.base() ); }

	/* != */
	template < class Iterator >
		bool operator!= ( const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs )
		{ return ( lhs.base() != rhs.base() ); }

	/* < */
	template < class Iterator >
		bool operator<  ( const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs )
		{ return ( lhs.base() > rhs.base() ); }

	/* <= */
	template < class Iterator >
		bool operator<= ( const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs )
		{ return ( lhs.base() >= rhs.base() ); }

	/* > */
	template < class Iterator >
		bool operator>  ( const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs )
		{ return ( lhs.base() < rhs.base() ); }

	/* >= */
	template < class Iterator >
		bool operator>= ( const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs )
		{ return ( lhs.base() <= rhs.base() ); }

	/* + */
	template < class Iterator >
		reverse_iterator<Iterator>	operator+ (
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rhs )
		{ return ( rhs + n ); }

	/* - */
	template < class Iterator >
		typename reverse_iterator<Iterator>::difference_type operator- (
				const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{ return ( rhs.base() - lhs.base() ); }

}


#endif // __REVERSE_ITERATOR_HPP__
