/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBnode.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:30:10 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/10 19:16:30 by mvidal-a         ###   ########.fr       */
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

	void	RBnode::swap_position ( RBnode* other, RBnode** root_link )
	{
		RBnode*		new_self_parent;
		RBnode*		new_self_left;
		RBnode*		new_self_right;
		RBnode**	new_self_link; // child ptr of other's parent
								   // that will point to "this"

		RBnode*		new_other_parent;
		RBnode*		new_other_left;
		RBnode*		new_other_right;
		RBnode**	new_other_link; // child ptr of this' parent
									// that will point to "other"

		bool		temp_color;

		// general case
		new_self_parent = other->_parent;
		new_self_left = other->_child[LEFT];
		new_self_right = other->_child[RIGHT];
		if ( other->_parent != NULL )
		{
			if ( other->child_dir() == LEFT )
				new_self_link = &other->_parent->_child[LEFT];
			else
				new_self_link = &other->_parent->_child[RIGHT];
		}
		else // other is root
			new_self_link = root_link;

		new_other_parent = _parent;
		new_other_left = _child[LEFT];
		new_other_right = _child[RIGHT];
		if ( _parent != NULL )
		{
			if ( this->child_dir() == LEFT )
				new_other_link = &_parent->_child[LEFT];
			else
				new_other_link = &_parent->_child[RIGHT];
		}
		else // this is root
			new_other_link = root_link;

		// special case: if one is the other's parent
		if ( other->_parent == this )
		{
			new_self_parent = other;
			new_self_link = NULL;
			if (_child[LEFT] == other)
				new_other_left = this;
			else
				new_other_right = this;
		}
		else if ( _parent == other )
		{
			new_other_parent = this;
			new_other_link = NULL;
			if (other->_child[LEFT] == this)
				new_self_left = other;
			else
				new_self_right = other;
		}

		// set all pointers
		_parent = new_self_parent;
		_child[LEFT] = new_self_left;
		if ( _child[LEFT] != NIL )
			_child[LEFT]->_parent = this;
		_child[RIGHT] = new_self_right;
		if ( _child[RIGHT] != NIL )
			_child[RIGHT]->_parent = this;
		if ( new_self_link != NULL )
			*new_self_link = this;

		other->_parent = new_other_parent;
		other->_child[LEFT] = new_other_left;
		if ( other->_child[LEFT] != NIL )
			other->_child[LEFT]->_parent = other;
		other->_child[RIGHT] = new_other_right;
		if ( other->_child[RIGHT] != NIL )
			other->_child[RIGHT]->_parent = other;
		if ( new_other_link != NULL )
			*new_other_link = other;

		temp_color = other->_color;
		other->_color = _color;
		_color = temp_color;
	}

} // namespace ft
