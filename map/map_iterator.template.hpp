/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.template.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:13:36 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/01 17:08:32 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_ITERATOR_TEMPLATE_HPP__
# define __MAP_ITERATOR_TEMPLATE_HPP__

#include "is_const.template.hpp"
#include "RBnode.class.hpp"

namespace	ft
{

	template < class T, bool constness = false >
	class	m_iterator
	{
		public:

			typedef	std::bidirectional_iterator_tag			iterator_category;
			typedef	typename is_const<T, constness>::type		value_type;
			typedef	std::ptrdiff_t								difference_type;
			typedef	typename is_const<T, constness>::type*		pointer;
			typedef	typename is_const<T, constness>::type&		reference;
			typedef	std::size_t									size_type;

		private:

			RBnode*		_node_ptr;
			RBnode*		_last_node;

		public:

			/* default constructor */
			m_iterator ( void );

			/* parameterized constructor */
			m_iterator ( RBnode* ptr );

			/* copy constructor */
			m_iterator ( const m_iterator& src );

			/* copy constructor from non-const to const */
	//		template < class U >
	//		m_iterator ( const m_iterator<U, false>& src ) :
	//			_node_ptr( &*src ) { }

			/* destructor */
			~m_iterator ( void ) { }

			/* it_copy = it */
			m_iterator&	operator= ( const m_iterator& rhs );

			/* const it_copy = it */
	//		template < class U >
	//		m_iterator&	operator= ( const m_iterator<U, false>& rhs )
	//		{ _node_ptr = &*rhs; return ( *this ); }

			/* *it */
			reference	operator* ( void ) const
			{
				return ( *static_cast<T*>(_node_ptr->get_content()) );
			}

			/* it->struct_arg */
			pointer		operator-> ( void ) const
			{ return ( &( operator*() ) ); }

			void		get_next_parent ( void )
			{
				RBnode*		next_node;

				next_node = _node_ptr->get_parent();
				if ( next_node == NULL )
					_node_ptr = NULL; // node is root: no next node
				else if ( _node_ptr->child_dir() == LEFT )
				{ // node is left child of parent
					_node_ptr = next_node; // assign to parent
				}
				else
				{ // node is right child of parent
					_node_ptr = next_node; // assign to parent
					get_next_parent(); // same operations with the parent
				}
			}

			/* ++it */
			m_iterator&	operator++ ( void )
			{
				RBnode*		next_node;

				next_node = _node_ptr->get_child( RIGHT );
				if ( next_node != NIL )
				{ // right child exists
					while ( next_node != NIL )
					{ // assign to right child, then left child, left child...
						_node_ptr = next_node;
						next_node = _node_ptr->get_child( LEFT );
					}
				}
				else
				{ // right child doesn't exist
					_last_node = _node_ptr;
					get_next_parent();
				}

				return ( *this );
			}

			void		get_prev_parent ( void )
			{
				RBnode*		prev_node;

				prev_node = _node_ptr->get_parent();
				if ( prev_node == NULL )
					_node_ptr = NULL ; // node is root: no previous node
				else if ( _node_ptr->child_dir() == RIGHT )
				{ // node is right child of parent
					_node_ptr = prev_node; // assign to parent
				}
				else
				{ // node is left child of parent
					_node_ptr = prev_node; // assign to parent
					get_prev_parent(); // same operations with the parent
				}
			}

			/* --it */
			m_iterator&	operator-- ( void )
			{
				if ( _node_ptr == NULL )
				{
					_node_ptr = _last_node;
					return ( *this );
				}

				RBnode*		prev_node;

				prev_node = _node_ptr->get_child( LEFT );
				if ( prev_node != NIL )
				{ // left child exists
					while ( prev_node != NIL )
					{ // assign to left child, then right child, right child...
						_node_ptr = prev_node;
						prev_node = _node_ptr->get_child( RIGHT );
					}
				}
				else
				{ // left child doesn't exist
					get_prev_parent();
				}

				return ( *this );
			}

			/* it++ */
			m_iterator	operator++ ( int )
			{
				m_iterator	before_inc( *this );

				_node_ptr++;

				return ( before_inc );
			}

			/* it-- */
			m_iterator	operator-- ( int )
			{
				m_iterator	before_dec( *this );

				_node_ptr--;

				return ( before_dec );
			}

			/* it == it2 */
			bool	operator== ( const m_iterator& rhs ) const
			{ return ( _node_ptr == rhs._node_ptr ); }

			/* it == const it2 */
			template < class U >
			bool	operator== ( const m_iterator<U, true>& rhs ) const
			{ return ( _node_ptr == rhs._node_ptr ); }

			/* const it == it2 */
			template < class U >
			bool	operator== ( const m_iterator<U, false>& rhs ) const
			{ return ( _node_ptr == rhs._node_ptr ); }

			/* it != it2 */
			bool	operator!= ( const m_iterator& rhs ) const
			{ return ( _node_ptr != rhs._node_ptr ); }

			/* it != const it2 */
			template < class U >
			bool	operator!= ( const m_iterator<U, true>& rhs ) const
			{ return ( _node_ptr != &*rhs ); }

			/* const it != it2 */
			template < class U >
			bool	operator!= ( const m_iterator<U, false>& rhs ) const
			{ return ( _node_ptr != &*rhs ); }

	}; // class m_iterator

} // namespace ft

#include "map_iterator.templatedef.hpp"

#endif // __MAP_ITERATOR_TEMPLATE_HPP__
