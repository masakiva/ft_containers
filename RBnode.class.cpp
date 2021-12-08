/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBnode.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:30:10 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/08 21:57:19 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBnode.class.hpp"

namespace	ft
{

	// the code in this file is largely inspired by
	// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Operations

	RBnode::RBnode ( void* content ) :
		_content( content ),
		_parent( NULL ),
		_color( RED )
	{
		_child[LEFT] = NULL;
		_child[RIGHT] = NULL;
	}

	void*	RBnode::get_content ( void ) const
	{
		return ( _content );
	}

	void	RBnode::set_color ( bool color )
	{
		_color = color;
	}

	bool	RBnode::get_color ( void ) const
	{
		return ( _color );
	}

	bool	RBnode::child_dir ( void ) const
	{
		return ( this == _parent->_child[LEFT] ? LEFT : RIGHT );
	}

	void	RBnode::set_child ( bool dir, RBnode* child )
	{
		_child[dir] = child;
	}

	RBnode*		RBnode::get_child ( bool dir ) const
	{
		return ( _child[dir] );
	}

	void	RBnode::set_parent ( RBnode* parent )
	{
		_parent = parent;
	}

	RBnode*		RBnode::get_parent ( void ) const
	{
		return ( _parent );
	}

	RBnode*		RBnode::get_grandparent ( void ) const
	{
		return ( _parent == NULL ? NULL : _parent->_parent );
	}

	RBnode*		RBnode::get_sibling ( void ) const
	{
		return ( _parent == NULL ?
				NULL : _parent->_child[1 - this->child_dir()] );
	}

	RBnode*		RBnode::get_uncle ( void ) const
	{
		return ( _parent == NULL ? NULL : _parent->get_sibling() );
	}

	RBnode*		RBnode::get_closenephew ( void ) const
	{
		RBnode*		sibling;
		bool		dir;
		
		if ( _parent == NULL )
			return ( NULL );
		dir = this->child_dir();
		sibling = _parent->_child[1 - dir];
		if ( sibling == NIL )
			return ( NULL );

		return ( sibling->_child[dir] );
	}

	RBnode*		RBnode::get_distantnephew ( void ) const
	{
		RBnode*		sibling;
		bool		dir;
		
		if ( _parent == NULL )
			return ( NULL );
		dir = this->child_dir();
		sibling = _parent->_child[1 - dir];
		if ( sibling == NIL )
			return ( NULL );

		return ( sibling->_child[1 - dir] );
	}

	RBnode*		RBnode::get_next ( bool dir ) const
	{ // comments are for dir == RIGHT (for iterator's operator++ )
		RBnode*		next_node;

		if ( _child[dir] != NIL )
		{ // right child exists
			next_node = _child[dir]; // assign to right child
			while ( next_node->_child[1 - dir] != NULL )
			{ // assign to left child, left child... as long as there is one
				next_node = next_node->_child[1 - dir];
			}
		}
		else
		{ // right child doesn't exist
			next_node = this->_get_next_parent( dir, 0 );
		}
		return ( next_node );
	}

	RBnode*		RBnode::_get_next_parent ( bool dir, int i) const
	{ // comments are for dir == RIGHT (for iterator's operator++ )
		RBnode*		next_node;

	//	if ( i == 100 )
	//	{
	//		std::cout << "i == 100" << std::endl;
	//		return ( NULL );
	//	}
		if ( _parent == NULL )
			next_node = NULL; // current node is root: no next node
		else if ( this->child_dir() == 1 - dir )
		{ // current node is left child of parent
			next_node = _parent; // assign to parent
		}
		else
		{ // current node is right child of parent
			next_node = _parent->_get_next_parent( dir, ++i ); // same with parent
		}
		return ( next_node );
	}

	void	RBnode::swap_content ( RBnode* rhs )
	{
		void*	temp_content;

		temp_content = rhs->_content;
		rhs->_content = _content;
		_content = temp_content;
	}

	void	RBnode::swap_position ( RBnode* rhs )
	{
		RBnode*		temp_node_ptr;
		bool		temp_color;

//		if ( _parent != NULL )
//		{
//			temp_node_ptr = rhs->_parent->_child[ rhs->child_dir() ];
//			rhs->_parent->_child[ rhs->child_dir() ] = _parent->_child[ this->child_dir() ];
//			_parent->_child[ this->child_dir() ] = temp_node_ptr;
//		}
		if ( rhs->_parent == this )
		{
			rhs->_parent = _parent;
			_parent = rhs;
		}
		else if ( _parent == rhs )
		{
			_parent = rhs->_parent;
			rhs->_parent = this;
		}
		else
		{
			temp_node_ptr = rhs->_parent;
			rhs->_parent = _parent;
			_parent = temp_node_ptr;
		}

		temp_node_ptr = rhs->_child[LEFT];
		rhs->_child[LEFT] = _child[LEFT];
		_child[LEFT] = temp_node_ptr;

		temp_node_ptr = rhs->_child[RIGHT];
		rhs->_child[RIGHT] = _child[RIGHT];
		_child[RIGHT] = temp_node_ptr;
		std::cout << rhs->_child[RIGHT] << std::endl << rhs << std::endl;

		temp_color = rhs->_color;
		rhs->_color = _color;
		_color = temp_color;
	}

} // namespace ft
