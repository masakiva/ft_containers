/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:49:02 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/19 20:41:46 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_ITERATOR_HPP__
# define __VECTOR_ITERATOR_HPP__

namespace	ft
{
	template < class T, bool constness >
	struct is_const
	{
		typedef	T			type;
	};

	template < class T >
	struct is_const<T, true>
	{
		typedef	const T		type;
	};

	template < class T, bool constness = false >
	class	v_iterator
	{
		public:

			typedef	std::random_access_iterator_tag			iterator_category;
			typedef	typename is_const<T, constness>::type	value_type;
			typedef	ptrdiff_t								difference_type;
			typedef	typename is_const<T, constness>::type*	pointer;
			typedef	typename is_const<T, constness>::type&	reference;
			typedef	size_t									size_type;

		private:

			value_type*		_ptr;

		public:

			/* default constructor */
			v_iterator ( void ) : _ptr( NULL ) { }

			/* parameterized constructor */
			v_iterator ( value_type* ptr ) : _ptr( ptr ) { }

			/* copy constructor */
			v_iterator ( const v_iterator& src ) { *this = src; }

			/* copy constructor from non-const to const */
			template < class U >
			v_iterator ( const v_iterator<U, false>& src ) : _ptr( &*src ) { }

			/* destructor */
			~v_iterator ( void ) { }

			/* it_copy = it */
			v_iterator&	operator= ( const v_iterator& rhs )
			{
				if ( this == &rhs )
					return ( *this );
				_ptr = rhs._ptr;
				return ( *this );
			}

			/* const it_copy = it */
			template < class U >
			v_iterator&	operator= ( const v_iterator<U, false>& rhs )
			{ _ptr = &*rhs; return ( *this ); }

			/* *it */
			reference	operator* ( void ) const { return ( *_ptr ); }

			/* it->struct_arg */
			pointer		operator-> ( void ) const
			{ return ( &( operator*() ) ); }

			/* ++it */
			v_iterator&	operator++ ( void ) { _ptr++; return ( *this ); }

			/* --it */
			v_iterator&	operator-- ( void ) { _ptr--; return ( *this ); }

			/* it++ */
			v_iterator	operator++ ( int )
			{ v_iterator before_inc( *this ); _ptr++; return ( before_inc ); }

			/* it-- */
			v_iterator	operator-- ( int )
			{ v_iterator before_dec( *this ); _ptr--; return ( before_dec ); }

			/* it > it2 */
			bool	operator> ( const v_iterator& rhs ) const
			{ return ( _ptr > rhs._ptr ); }

			/* it > const it2 */
			template < class U >
			bool	operator> ( const v_iterator<U, true>& rhs ) const
			{ return ( _ptr > &*rhs ); }

			/* const it > it2 */
			template < class U >
			bool	operator> ( const v_iterator<U, false>& rhs ) const
			{ return ( _ptr > &*rhs ); }

			/* it < it2 */
			bool	operator< ( const v_iterator& rhs ) const
			{ return ( _ptr < rhs._ptr ); }

			/* it < const it2 */
			template < class U >
			bool	operator< ( const v_iterator<U, true>& rhs ) const
			{ return ( _ptr < &*rhs ); }

			/* const it < it2 */
			template < class U >
			bool	operator< ( const v_iterator<U, false>& rhs ) const
			{ return ( _ptr < &*rhs ); }

			/* it >= it2 */
			bool	operator>= ( const v_iterator& rhs ) const
			{ return ( _ptr >= rhs._ptr ); }

			/* it >= const it2 */
			template < class U >
			bool	operator>= ( const v_iterator<U, true>& rhs ) const
			{ return ( _ptr >= &*rhs ); }

			/* const it >= it2 */
			template < class U >
			bool	operator>= ( const v_iterator<U, false>& rhs ) const
			{ return ( _ptr >= &*rhs ); }

			/* it <= it2 */
			bool	operator<= ( const v_iterator& rhs ) const
			{ return ( _ptr <= rhs._ptr ); }

			/* it <= const it2 */
			template < class U >
			bool	operator<= ( const v_iterator<U, true>& rhs ) const
			{ return ( _ptr <= &*rhs ); }

			/* const it <= it2 */
			template < class U >
			bool	operator<= ( const v_iterator<U, false>& rhs ) const
			{ return ( _ptr <= &*rhs ); }

			/* it == it2 */
			bool	operator== ( const v_iterator& rhs ) const
			{ return ( _ptr == rhs._ptr ); }

			/* it == const it2 */
			template < class U >
			bool	operator== ( const v_iterator<U, true>& rhs ) const
			{ return ( _ptr == &*rhs ); }

			/* const it == it2 */
			template < class U >
			bool	operator== ( const v_iterator<U, false>& rhs ) const
			{ return ( _ptr == &*rhs ); }

			/* it != it2 */
			bool	operator!= ( const v_iterator& rhs ) const
			{ return ( _ptr != rhs._ptr ); }

			/* it != const it2 */
			template < class U >
			bool	operator!= ( const v_iterator<U, true>& rhs ) const
			{ return ( _ptr != &*rhs ); }

			/* const it != it2 */
			template < class U >
			bool	operator!= ( const v_iterator<U, false>& rhs ) const
			{ return ( _ptr != &*rhs ); }

			/* it += n */
			v_iterator&	operator+= ( const difference_type& n )
			{ _ptr += n; return ( *this ); }

			/* it -= n */
			v_iterator&	operator-= ( const difference_type& n )
			{ _ptr -= n; return ( *this ); }

			/* it + n */
			v_iterator	operator+ ( const difference_type& n ) const
			{ v_iterator temp( *this ); return ( temp += n ); }

			/* it - n */
			v_iterator	operator- ( const difference_type& n ) const
			{ v_iterator temp( *this ); return ( temp -= n ); }

			/* it - it2 */
			difference_type	operator- ( const v_iterator& rhs ) const
			{ return ( _ptr - rhs._ptr ); }

			/* it[i] */
			reference	operator[] ( size_type pos ) { return ( _ptr[pos] ); }


	}; // class v_iterator

	/* n + it */
	template < class T >
		v_iterator<T>
			operator+ ( const typename v_iterator<T>::difference_type& n,
					const v_iterator<T>& rhs )
	{ v_iterator<T> temp( rhs ); return ( temp += n ); }

} // namespace ft

#endif // __VECTOR_ITERATOR_HPP__
