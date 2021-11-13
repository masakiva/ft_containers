/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:49:02 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/13 17:55:56 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_ITERATOR_HPP__
# define __VECTOR_ITERATOR_HPP__

namespace	ft
{
	template <	class Category,
				class T,
				class Distance = ptrdiff_t,
				class Pointer = T*,
				class Reference = T& >
	class	v_iterator
	{
		public:

			typedef	Category	iterator_category;
			typedef	T			value_type;
			typedef	Distance	difference_type;
			typedef	Pointer		pointer;
			typedef	Reference	reference;

		private:

			T*		_ptr;

		public:

			/* default constructor */
			v_iterator ( void ) : _ptr(NULL) { }

			/* parameterized constructor */
			v_iterator ( T* ptr ) : _ptr(ptr) { }

			/* copy constructor */
			v_iterator ( const v_iterator& src ) { *this = src; }

			/* destructor */
			~v_iterator ( void ) { }

			/* = */
			v_iterator&	operator= ( const v_iterator &rhs )
			{
				if ( this == &rhs )
					return ( *this );
				_ptr = rhs._ptr;
				return ( *this );
			}

			/* * */
			reference	operator* ( void ) const { return ( *_ptr ); }

			/* -> */
			pointer		operator-> ( void ) const
			{ return ( &( operator*() ) ); }

			/* ++i */
			v_iterator&	operator++ ( void ) { _ptr++; return ( *this ); }

			/* --i */
			v_iterator&	operator-- ( void ) { _ptr--; return ( *this ); }

			/* i++ */
			v_iterator	operator++ ( int )
			{ v_iterator before_inc( *this ); _ptr++; return ( before_inc ); }

			/* i-- */
			v_iterator	operator-- ( int )
			{ v_iterator before_dec( *this ); _ptr--; return ( before_dec ); }

			/* > */
			bool	operator> ( const v_iterator &rhs ) const
			{ return ( _ptr > rhs._ptr ); }

			/* < */
			bool	operator< ( const v_iterator &rhs ) const
			{ return ( _ptr < rhs._ptr ); }

			/* >= */
			bool	operator>= ( const v_iterator &rhs ) const
			{ return ( _ptr >= rhs._ptr ); }

			/* <= */
			bool	operator<= ( const v_iterator &rhs ) const
			{ return ( _ptr <= rhs._ptr ); }

			/* == */
			bool	operator== ( const v_iterator &rhs ) const
			{ return ( _ptr == rhs._ptr ); }

			/* != */
			bool	operator!= ( const v_iterator &rhs ) const
			{ return ( _ptr != rhs._ptr ); }

			/* += */
			v_iterator&	operator+= ( const difference_type& n )
			{ _ptr += n; return ( *this ); }

			/* -= */
			v_iterator&	operator-= ( const difference_type& n )
			{ _ptr -= n; return ( *this ); }

			/* + */
			v_iterator	operator+ ( const difference_type& n ) const
			{ v_iterator temp( *this ); return ( temp += n ); }

			/* - */
			v_iterator	operator- ( const difference_type& n ) const
			{ v_iterator temp( *this ); return ( temp -= n ); }

	};
}

#endif // __VECTOR_ITERATOR_HPP__
