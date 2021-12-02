/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:41:07 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/02 15:09:44 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBtree.class.hpp"

namespace	ft
{

	void	RBtree::_print_node ( RBnode* node, bool dir, int i ) const
	{
		if ( node == NIL )
			std::cout << ">>> " << ( dir ? "\e[34mright\e[0m" : "\e[32mleft\e[0m" )
				<< " of " << i << ": \e[30;43mNIL\e[0m" << std::endl;
		else
		{
			int	new_i = i + (dir ? 10 : 100 );
			std::cout << ">>> " << new_i << ": "
				<< ( dir ? "\e[34mright\e[0m" : "\e[32mleft\e[0m" ) << " of " << i << ": ";
			std::cout << ( node->get_color() == RED ?
					"\e[41mRED\e[0m" : "\e[30;47mBLACK\e[0m" ) << std::endl;
			this->_print_node( node->get_child( LEFT ), LEFT, new_i );
			this->_print_node( node->get_child( RIGHT ), RIGHT, new_i );
		}
	}

	void	RBtree::print_tree ( void ) const
	{
		std::cout << ">>> ROOT: ";
		if ( _root == NIL )
			std::cout << ": \e[30;43mNIL\e[0m" << std::endl;
		else
		{
			std::cout << ( _root->get_color() == RED ?
					"\e[41mRED\e[0m" : "\e[30;47mBLACK\e[0m" ) << std::endl;
			this->_print_node( _root->get_child( LEFT ), LEFT, 0 );
			this->_print_node( _root->get_child( RIGHT ), RIGHT, 0 );
		}
	}

	RBtree::RBtree ( void ) : _root( NIL ) { }

	RBnode*		RBtree::get_root ( void ) const
	{
		return ( _root );
	}

	RBnode*		RBtree::get_first_node ( void ) const
	{
		if ( _root == NIL )
			return ( NULL );

		RBnode*		first;
		RBnode*		left_child;

		first = _root;
		left_child = first->get_child( LEFT );
		while ( left_child != NIL )
		{ // assign to left child if not NIL
			first = left_child;
			left_child = first->get_child( LEFT );
		}

		return ( first );
	}

	RBnode*		RBtree::get_last_node ( void ) const
	{
		if ( _root == NIL )
			return ( NULL );

		RBnode*		last;
		RBnode*		right_child;

		last = _root;
		right_child = last->get_child( RIGHT );
		while ( right_child != NIL )
		{ // assign to right child if not NIL
			last = right_child;
			right_child = last->get_child( RIGHT );
		}

		return ( last );
	}

	void	RBtree::_rotate_subtree( RBnode* parent, bool dir)
	{
		RBnode*		grandparent;
		RBnode*		sibling;
		RBnode*		closenephew;

		grandparent = parent->get_parent();
		sibling = parent->get_child( 1 - dir );
		if ( sibling == NIL ) // pointer to true RBnode required
			return ;
		closenephew = sibling->get_child( dir );

		parent->set_child( 1 - dir, closenephew );
		if ( closenephew != NIL )
			closenephew->set_parent( parent );
		sibling->set_child( dir, parent );
		parent->set_parent( sibling );
		sibling->set_parent( grandparent );
		if ( grandparent != NULL )
		{
			if ( parent == grandparent->get_child( RIGHT ) )
				// cannot write
				// if ( parent->child_dir() == RIGHT )
				// because parent's parent is not grandparent anymore
				grandparent->set_child( RIGHT, sibling );
			else
				grandparent->set_child( LEFT, sibling );
		}
		else
		{
			_root = sibling;
		}
	}

	void	RBtree::_insert_rebalancing_loop ( RBnode* node, RBnode* parent )
	{
		RBnode*		grandparent;
		RBnode*		uncle;
		bool		parent_dir;

		while ( parent != NULL )
		{
			if (parent->get_color() == BLACK)
				break ; // insertion complete

			// else: parent is red

			grandparent = parent->get_parent();
			if ( grandparent == NULL )
			{ // parent is the root and red
				parent->set_color( BLACK );
				break ; // insertion complete
			}

			// else: parent red and grandparent exists

			parent_dir = parent->child_dir();
			uncle = parent->get_sibling();

			if ( uncle == NIL || uncle->get_color() == BLACK )
			{ // parent red and uncle black (NIL is black)
				if ( node == parent->get_child( 1 - parent_dir ) )
				{ // node is inner grandchild of grandparent
					this->_rotate_subtree( parent, parent_dir );
					parent = grandparent->get_child( parent_dir );
				}
				// node is outer grandchild of grandparent
				this->_rotate_subtree( grandparent, 1 - parent_dir );
				parent->set_color( BLACK );
				grandparent->set_color( RED );
				break ; // insertion complete
			}

			// else: parent and uncle red
			parent->set_color( BLACK );
			uncle->set_color( BLACK );
			grandparent->set_color( RED );
			node = grandparent; // new current node
			// iterate 1 black level (= 2 tree levels) higher
			parent = node->get_parent();
		}
	}

	void	RBtree::insert ( RBnode* node, RBnode* parent, bool dir )
	{
		node->set_color( RED ); // every node is RED at first
		node->set_child( LEFT, NIL );
		node->set_child( RIGHT, NIL );
		node->set_parent( parent );
		if ( parent == NULL )
		{
			_root = node; // node is the new root
			return ; // insertion complete
		}
		parent->set_child( dir, node ); // insert node

		// maintain RBtree properties by rotating subtree or changing colors
		this->_insert_rebalancing_loop( node, parent );
	}

} // namespace ft
