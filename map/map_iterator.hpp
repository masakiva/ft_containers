/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:13:36 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/26 11:17:01 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_ITERATOR_HPP__
# define __MAP_ITERATOR_HPP__

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
	class	m_iterator
	{
		public:

			typedef	std::bidirectional_iterator_tag			iterator_category;
			typedef	typename is_const<T, constness>::type	value_type;
			typedef	std::ptrdiff_t							difference_type;
			typedef	typename is_const<T, constness>::type*	pointer;
			typedef	typename is_const<T, constness>::type&	reference;
			typedef	std::size_t								size_type;

		private:

			value_type*		_ptr;

		public:

			/* default constructor */
			m_iterator ( void ) : _ptr( NULL ) { }

			/* parameterized constructor */
			m_iterator ( value_type* ptr ) : _ptr( ptr ) { }

			/* copy constructor */
			m_iterator ( const m_iterator& src ) { *this = src; }

			/* copy constructor from non-const to const */
			template < class U >
			m_iterator ( const m_iterator<U, false>& src ) : _ptr( &*src ) { }

			/* destructor */
			~m_iterator ( void ) { }

			/* it_copy = it */
			m_iterator&	operator= ( const m_iterator& rhs )
			{
				if ( this == &rhs )
					return ( *this );
				_ptr = rhs._ptr;
				return ( *this );
			}

			/* const it_copy = it */
			template < class U >
			m_iterator&	operator= ( const m_iterator<U, false>& rhs )
			{ _ptr = &*rhs; return ( *this ); }

			/* *it */
			reference	operator* ( void ) const { return ( *_ptr ); }

			/* it->struct_arg */
			pointer		operator-> ( void ) const
			{ return ( &( operator*() ) ); }

			/* ++it */
			m_iterator&	operator++ ( void )
			{
				;
				return ( *this );
			}

			/* --it */
			m_iterator&	operator-- ( void ) { _ptr--; return ( *this ); }

			/* it++ */
			m_iterator	operator++ ( int )
			{ m_iterator before_inc( *this ); _ptr++; return ( before_inc ); }

			/* it-- */
			m_iterator	operator-- ( int )
			{ m_iterator before_dec( *this ); _ptr--; return ( before_dec ); }

			/* it == it2 */
			bool	operator== ( const m_iterator& rhs ) const
			{ return ( _ptr == rhs._ptr ); }

			/* it == const it2 */
			template < class U >
			bool	operator== ( const m_iterator<U, true>& rhs ) const
			{ return ( _ptr == &*rhs ); }

			/* const it == it2 */
			template < class U >
			bool	operator== ( const m_iterator<U, false>& rhs ) const
			{ return ( _ptr == &*rhs ); }

			/* it != it2 */
			bool	operator!= ( const m_iterator& rhs ) const
			{ return ( _ptr != rhs._ptr ); }

			/* it != const it2 */
			template < class U >
			bool	operator!= ( const m_iterator<U, true>& rhs ) const
			{ return ( _ptr != &*rhs ); }

			/* const it != it2 */
			template < class U >
			bool	operator!= ( const m_iterator<U, false>& rhs ) const
			{ return ( _ptr != &*rhs ); }

	}; // class m_iterator

} // namespace ft

#endif // __MAP_ITERATOR_HPP__
