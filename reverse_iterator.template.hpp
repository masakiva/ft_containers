/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.template.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:07:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/02 16:16:42 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __REVERSE_ITERATOR_TEMPLATE_HPP__
# define __REVERSE_ITERATOR_TEMPLATE_HPP__

#include "iterator_traits.template.hpp"

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
			reverse_iterator ( void ) : _it( Iterator() ) { }

			/* parameterized constructor */
			explicit reverse_iterator ( iterator_type it ) : _it( it ) { }

			/* copy constructor */
			template < class U >
			reverse_iterator ( const reverse_iterator<U>& src ) :
				_it( src.base() ) { }

			/* destructor */
			~reverse_iterator ( void ) { }

			/* rit_copy = rit */
			reverse_iterator&	operator= ( const reverse_iterator& rhs )
			{
				if ( this == &rhs )
					return ( *this );
				_it = rhs._it;
				return ( *this );
			}

			/* base */
			iterator_type	base( void ) const { return ( _it ); }

			/* *rit */
			reference		operator* ( void )
			{
				--_it;
				reverse_iterator	prev_elem( *this );
				++_it;
				return ( *(prev_elem._it) );
			}

			/* rit->struct_arg */
			pointer		operator-> ( void )
			{ return ( &( operator*() ) ); }

			/* ++rit */
			reverse_iterator&	operator++( void ) { --_it; return ( *this ); }

			/* --rit */
			reverse_iterator&	operator--( void ) { ++_it; return ( *this ); }

			/* rit++ */
			reverse_iterator 	operator++( int )
			{
				reverse_iterator	before_inc( *this );
				--_it;
				return ( before_inc );
			}

			/* rit-- */
			reverse_iterator 	operator--( int )
			{
				reverse_iterator	before_dec( *this );
				++_it;
				return ( before_dec );
			}

			/* rit += n */
			reverse_iterator&	operator+= ( difference_type n )
			{ _it -= n; return ( *this ); }

			/* rit -= n */
			reverse_iterator&	operator-= ( difference_type n )
			{ _it += n; return ( *this ); }

			/* rit + n */
			reverse_iterator	operator+ ( difference_type n ) const
			{ reverse_iterator temp( *this ); return ( temp.operator+=( n ) ); }

			/* rit - n */
			reverse_iterator	operator- ( difference_type n ) const
			{ reverse_iterator temp( *this ); return ( temp.operator-=( n ) ); }

			/* rit[i] */
			reference			operator[] ( difference_type n ) const
			{ return ( this->base()[-1 * n - 1] ); }

	}; // class reverse_iterator

	/* rit == rit2 */
	template < class Iterator1, class Iterator2 >
		bool	operator== ( const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs )
		{ return ( lhs.base() == rhs.base() ); }

	/* rit != rit2 */
	template < class Iterator1, class Iterator2 >
		bool	operator!= ( const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs )
		{ return ( lhs.base() != rhs.base() ); }

	/* rit < rit2 */
	template < class Iterator1, class Iterator2 >
		bool	operator< ( const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs )
		{ return ( lhs.base() > rhs.base() ); }

	/* rit <= rit2 */
	template < class Iterator1, class Iterator2 >
		bool	operator<= ( const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs )
		{ return ( lhs.base() >= rhs.base() ); }

	/* rit > rit2 */
	template < class Iterator1, class Iterator2 >
		bool	operator> ( const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs )
		{ return ( lhs.base() < rhs.base() ); }

	/* rit >= rit2 */
	template < class Iterator1, class Iterator2 >
		bool	operator>= ( const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs )
		{ return ( lhs.base() <= rhs.base() ); }

	/* rit + n */
	template < class Iterator >
		reverse_iterator<Iterator>
				operator+ (
				typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rhs )
		{ return ( rhs + n ); }

	/* rit - rit2 */
	template < class Iterator1, class Iterator2 >
		typename reverse_iterator<Iterator1>::difference_type
				operator- ( const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{ return ( rhs.base() - lhs.base() ); }

} // namespace ft


#endif // __REVERSE_ITERATOR_TEMPLATE_HPP__
