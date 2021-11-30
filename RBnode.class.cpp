/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBnode.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:30:10 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/30 19:33:17 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBnode.class.hpp"

namespace	ft
{

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

	RBnode*	RBnode::get_child ( bool dir ) const
	{
		return ( _child[dir] );
	}

	void	RBnode::set_parent ( RBnode* parent )
	{
		_parent = parent;
	}

	RBnode*	RBnode::get_parent ( void ) const
	{
		return ( _parent );
	}

	RBnode*	RBnode::get_grandparent ( void ) const
	{
		return ( _parent == NULL ? NULL : _parent->_parent );
	}

	RBnode*	RBnode::get_sibling ( void ) const
	{
		return ( _parent == NULL ?
				NULL : _parent->_child[1 - this->child_dir()] );
	}

	RBnode*	RBnode::get_uncle ( void ) const
	{
		return ( _parent == NULL ? NULL : _parent->get_sibling() );
	}

	RBnode*	RBnode::get_closenephew ( void ) const
	{
		RBnode*	sibling;
		bool	dir;
		
		if ( _parent == NULL )
			return ( NULL );
		dir = this->child_dir();
		sibling = _parent->_child[1 - dir];
		if ( sibling == NIL )
			return ( NULL );

		return ( sibling->_child[dir] );
	}

	RBnode*	RBnode::get_distantnephew ( void ) const
	{
		RBnode*	sibling;
		bool	dir;
		
		if ( _parent == NULL )
			return ( NULL );
		dir = this->child_dir();
		sibling = _parent->_child[1 - dir];
		if ( sibling == NIL )
			return ( NULL );

		return ( sibling->_child[1 - dir] );
	}

} // namespace ft
