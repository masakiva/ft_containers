/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.template.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:13:36 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/28 14:52:04 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_ITERATOR_TEMPLATE_HPP__
# define __MAP_ITERATOR_TEMPLATE_HPP__

#include "is_const.template.hpp"
#include "RBnode.class.hpp"

namespace	ft
{

	template < class Compare, bool constness = false >
	class	m_iterator
	{
		public:

			typedef	std::bidirectional_iterator_tag			iterator_category;
			typedef	typename is_const<RBnode, constness>::type	value_type;
			typedef	std::ptrdiff_t								difference_type;
			typedef	typename is_const<RBnode, constness>::type*	pointer;
			typedef	typename is_const<RBnode, constness>::type&	reference;
			typedef	std::size_t									size_type;
			typedef	Compare										key_compare;

		private:

			value_type*		_node_ptr;
			key_compare		_comp;

		public:

			/* default constructor */
			m_iterator ( void ) :
				_node_ptr( NULL ), _comp( key_compare() )  { }

			/* parameterized constructor */
			m_iterator ( value_type* ptr ) :
				_node_ptr( ptr ), _comp( key_compare() ) { }

			/* copy constructor */
			m_iterator ( const m_iterator& src ) { *this = src; }

			/* copy constructor from non-const to const */
	//		template < class U >
	//		m_iterator ( const m_iterator<U, false>& src ) :
	//			_node_ptr( &*src ), _comp( ) { }

			/* destructor */
			~m_iterator ( void ) { }

			/* it_copy = it */
			m_iterator&	operator= ( const m_iterator& rhs )
			{
				if ( this == &rhs )
					return ( *this );
				_node_ptr = rhs._node_ptr;
				_comp = rhs._comp;
				return ( *this );
			}

			/* const it_copy = it */
	//		template < class U >
	//		m_iterator&	operator= ( const m_iterator<U, false>& rhs )
	//		{ _node_ptr = &*rhs; return ( *this ); }

			/* *it */
			reference	operator* ( void ) const
			{ return ( _node_ptr->get_content() ); }

			/* it->struct_arg */
	//		pointer		operator-> ( void ) const
	//		{ return ( &( operator*() ) ); }

			void		get_next_parent( void )
			{
				value_type*		next_node;

				next_node = _node_ptr->get_parent();
				if ( next_node == NIL )
					; // END
				else if ( _node_ptr->child_dir() == LEFT )
					_node_ptr = next_node;
				else
				{
					_node_ptr = next_node;
					get_next_parent();
				}
			}

			/* ++it */
			m_iterator&	operator++ ( void )
			{
//				if ( _node_ptr == NIL )
//					;
				value_type*		next_node;

				next_node = _node_ptr->get_child( RIGHT );
				if ( next_node != NIL )
				{
					while ( next_node != NIL )
					{
						_node_ptr = next_node;
						next_node = _node_ptr->get_child( LEFT );
					}
				}
				else
				{
					get_next_parent();
				}

				return ( *this );
			}
//
//			/* --it */
//			m_iterator&	operator-- ( void ) { _node_ptr--; return ( *this ); }
//
//			/* it++ */
//			m_iterator	operator++ ( int )
//			{ m_iterator before_inc( *this ); _node_ptr++; return ( before_inc ); }
//
//			/* it-- */
//			m_iterator	operator-- ( int )
//			{ m_iterator before_dec( *this ); _node_ptr--; return ( before_dec ); }
//
//			/* it == it2 */
//			bool	operator== ( const m_iterator& rhs ) const
//			{ return ( _node_ptr == rhs._node_ptr ); }
//
//			/* it == const it2 */
//			template < class U >
//			bool	operator== ( const m_iterator<U, true>& rhs ) const
//			{ return ( _node_ptr == &*rhs ); }
//
//			/* const it == it2 */
//			template < class U >
//			bool	operator== ( const m_iterator<U, false>& rhs ) const
//			{ return ( _node_ptr == &*rhs ); }
//
//			/* it != it2 */
//			bool	operator!= ( const m_iterator& rhs ) const
//			{ return ( _node_ptr != rhs._node_ptr ); }
//
//			/* it != const it2 */
//			template < class U >
//			bool	operator!= ( const m_iterator<U, true>& rhs ) const
//			{ return ( _node_ptr != &*rhs ); }
//
//			/* const it != it2 */
//			template < class U >
//			bool	operator!= ( const m_iterator<U, false>& rhs ) const
//			{ return ( _node_ptr != &*rhs ); }

	}; // class m_iterator

} // namespace ft

#endif // __MAP_ITERATOR_TEMPLATE_HPP__
