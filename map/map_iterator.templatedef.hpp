/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.templatedef.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:40:31 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/06 17:26:22 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_ITERATOR_TEMPLATEDEF_HPP__
# define __MAP_ITERATOR_TEMPLATEDEF_HPP__

namespace	ft
{

	/******* CANONICAL FORM ***************************************************/

	/* default constructor */
	template < class T, bool constness >
		m_iterator<T,constness>::m_iterator ( void ) :
			_node_ptr( NULL ),
			_last_node_ptr( NULL ),
			_map_ptr( NULL )
		{ }

	/* parameterized constructor */
	template < class T, bool constness >
		m_iterator<T,constness>::m_iterator ( RBnode* ptr, void* map_ptr ) :
			_node_ptr( ptr ),
			_last_node_ptr( NULL ),
			_map_ptr( map_ptr )
		{ }

	/* copy constructor */
	template < class T, bool constness >
		m_iterator<T,constness>::m_iterator ( const m_iterator& src )
		{
			*this = src;
		}

	/* copy constructor from non-const to const */
	template < class T, bool constness >
		template < class U >
			m_iterator<T,constness>::m_iterator
					( const m_iterator<U, false>& src )
			{
				*this = src;
			}

	/* destructor */
	template < class T, bool constness >
		m_iterator<T,constness>::~m_iterator ( void )
		{ }

	/* it_copy = it */
	template < class T, bool constness >
		m_iterator<T,constness>&
				m_iterator<T,constness>::operator= ( const m_iterator& rhs )
		{
			if ( this == &rhs )
				return ( *this );
			_node_ptr = rhs._node_ptr;
			_last_node_ptr = rhs._last_node_ptr;
			_map_ptr = rhs._map_ptr;
			return ( *this );
		}

	/* const it_copy = it */
	template < class T, bool constness >
		template < class U >
			m_iterator<T,constness>&	m_iterator<T,constness>::operator=
					( const m_iterator<U, false>& rhs )
			{
				_node_ptr = rhs.get_node_ptr();
				_last_node_ptr = rhs.get_last_node_ptr();
				_map_ptr = rhs.get_map_ptr();
				return ( *this );
			}


	/******* GETTERS AND SETTERS **********************************************/

	/* get_node_ptr */
	template < class T, bool constness >
		RBnode*		m_iterator<T,constness>::get_node_ptr ( void ) const
		{
			return ( _node_ptr );
		}

	/* set_node_ptr */
	template < class T, bool constness >
		void		m_iterator<T,constness>::set_node_ptr ( RBnode* ptr,
				void* map_ptr )
		{
			_node_ptr = ptr;
			_map_ptr = map_ptr;
		}

	/* get_last_node_ptr */
	template < class T, bool constness >
		RBnode*		m_iterator<T,constness>::get_last_node_ptr ( void ) const
		{
			return ( _last_node_ptr );
		}

	/* get_map_ptr */
	template < class T, bool constness >
		void*		m_iterator<T,constness>::get_map_ptr ( void ) const
		{
			return ( _map_ptr );
		}


	/******* ELEMENT ACCESS ***************************************************/

	/* *it */
	template < class T, bool constness >
		typename m_iterator<T,constness>::reference
				m_iterator<T,constness>::operator* ( void ) const
		{
			return ( *static_cast<T*>(_node_ptr->get_content()) );
		}

	/* it->struct_arg */
	template < class T, bool constness >
		typename m_iterator<T,constness>::pointer
				m_iterator<T,constness>::operator-> ( void ) const
		{
			return ( &( operator*() ) );
		}


	/******* INCREMENT AND DECREMENT ******************************************/

	/* ++it */
	template < class T, bool constness >
		m_iterator<T,constness>&
				m_iterator<T,constness>::operator++ ( void )
		{
			_last_node_ptr = _node_ptr;
			this->_iterate( RIGHT );

			return ( *this );
		}

	/* --it */
	template < class T, bool constness >
		m_iterator<T,constness>&
				m_iterator<T,constness>::operator-- ( void )
		{
			if ( _node_ptr == NULL )
				_node_ptr = _last_node_ptr;
			else
				this->_iterate( LEFT );

			return ( *this );
		}

	/* it++ */
	template < class T, bool constness >
		m_iterator<T,constness>
				m_iterator<T,constness>::operator++ ( int )
		{
			m_iterator	before_inc( *this );

			_last_node_ptr = _node_ptr;
			this->_iterate( RIGHT );

			return ( before_inc );
		}

	/* it-- */
	template < class T, bool constness >
		m_iterator<T,constness>
				m_iterator<T,constness>::operator-- ( int )
		{
			m_iterator	before_dec( *this );

			if ( _node_ptr == NULL )
				_node_ptr = _last_node_ptr;
			else
				this->_iterate( LEFT );

			return ( before_dec );
		}


	/******* COMPARISONS ******************************************************/

	/* it == it2 */
	template < class T, bool constness >
		bool	m_iterator<T,constness>::operator==
				( const m_iterator& rhs ) const
		{
			return ( _node_ptr == rhs._node_ptr );
		}

	/* it == const it2 */
	template < class T, bool constness >
		bool	m_iterator<T,constness>::operator==
				( const m_iterator<T, true>& rhs )
		{
			return ( _node_ptr == rhs.get_node_ptr() );
		}

	/* const it == it2 */
	template < class T, bool constness >
		bool	m_iterator<T,constness>::operator==
				( const m_iterator<T, false>& rhs )
		{
			return ( _node_ptr == rhs.get_node_ptr() );
		}

	/* it != it2 */
	template < class T, bool constness >
		bool	m_iterator<T,constness>::operator!=
				( const m_iterator& rhs ) const
		{
			return ( _node_ptr != rhs._node_ptr );
		}

	/* it != const it2 */
	template < class T, bool constness >
		bool	m_iterator<T,constness>::operator!=
				( const m_iterator<T, true>& rhs )
		{
			return ( _node_ptr != rhs.get_node_ptr() );
		}

	/* const it != it2 */
	template < class T, bool constness >
		bool	m_iterator<T,constness>::operator!=
				( const m_iterator<T, false>& rhs )
		{
			return ( _node_ptr != rhs.get_node_ptr() );
		}


	/******* HELPER FUNCTIONS *************************************************/

	template < class T, bool constness >
		void	m_iterator<T,constness>::_get_next_parent ( bool dir )
		{ // comments are for dir == RIGHT (for operator++ )
			RBnode*		next_node;

			next_node = _node_ptr->get_parent();
			if ( next_node == NULL )
				_node_ptr = NULL; // current node is root: no next node
			else if ( _node_ptr->child_dir() == 1 - dir )
			{ // current node is left child of parent
				_node_ptr = next_node; // assign to parent
			}
			else
			{ // current node is right child of parent
				_node_ptr = next_node; // assign to parent
				this->_get_next_parent( dir ); // same operations with parent
			}
		}

	template < class T, bool constness >
		void	m_iterator<T,constness>::_iterate ( bool dir )
		{ // comments are for dir == RIGHT (for operator++ )
			RBnode*		next_node;

			next_node = _node_ptr->get_child( dir );
			if ( next_node != NIL )
			{ // right child exists
				do
				{ // assign to right child, then left child, left child...
					_node_ptr = next_node;
					next_node = _node_ptr->get_child( 1 - dir );
				} while ( next_node != NIL );
			}
			else
			{ // right child doesn't exist
				this->_get_next_parent( dir );
			}
		}

} // namespace ft

#endif // __MAP_ITERATOR_TEMPLATEDEF_HPP__
