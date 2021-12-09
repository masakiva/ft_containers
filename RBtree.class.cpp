/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:41:07 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/09 17:48:39 by mvidal-a         ###   ########.fr       */
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

	RBnode*		RBtree::get_extremity ( bool dir ) const
	{ // get first or last node of the tree
		if ( _root == NIL )
			return ( NULL );

		RBnode*		extremity;
		RBnode*		child;

		extremity = _root;
		child = extremity->get_child( dir );
		while ( child != NIL )
		{ // assign to dir (LEFT or RIGHT) child if not NIL
			extremity = child;
			child = extremity->get_child( dir );
		}

		return ( extremity );
	}

	// the following code in this file is largely inspired by
	// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Operations

	void	RBtree::_rotate_subtree ( RBnode* parent, bool dir )
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

		do
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
			{ // parent red and uncle black (a NIL node is considered black)
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

		} while ( parent != NULL );
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

	void	RBtree::_rebalance_red_parent ( RBnode* parent, RBnode *sibling )
	{ // parent red, sibling and nephews black
		sibling->set_color( RED );
		parent->set_color( BLACK );
	}

	void	RBtree::_rebalance_red_distantnephew ( RBnode* parent, bool dir,
			RBnode *sibling, RBnode* distantnephew )
	{ // distantnephew red, sibling black
		_rotate_subtree( parent, dir );
		sibling->set_color( parent->get_color() );
		parent->set_color( BLACK );
		distantnephew->set_color( BLACK );
	}

	void	RBtree::_rebalance_red_closenephew ( RBnode* parent, bool dir,
			RBnode *sibling, RBnode* closenephew, RBnode* distantnephew )
	{ // closenephew red, sibling and distantnephew black
		_rotate_subtree( sibling, 1 - dir );
		sibling->set_color( RED );
		closenephew->set_color( BLACK );
		distantnephew = sibling;
		sibling = closenephew;

		// now distantnephew is red and sibling black
		this->_rebalance_red_distantnephew( parent, dir, sibling,
				distantnephew );
	}

	void	RBtree::_rebalance_red_sibling ( RBnode* parent, bool dir,
			RBnode *sibling, RBnode* closenephew, RBnode* distantnephew )
	{ // sibling red, parent and nephews black
		_rotate_subtree( parent, dir );
		parent->set_color( RED );
		sibling->set_color( BLACK );
		sibling = closenephew; // != NIL

		// now parent is red and sibling black

		distantnephew = sibling->get_child( 1 - dir );
		if ( distantnephew != NIL && distantnephew->get_color() == RED )
		{
			this->_rebalance_red_distantnephew( parent, dir, sibling,
					distantnephew );
			return; // deletion complete
		}

		closenephew = sibling->get_child( dir );
		if ( closenephew != NIL && closenephew->get_color() == RED )
		{
			this->_rebalance_red_closenephew( parent, dir, sibling, closenephew,
					distantnephew );
			return; // deletion complete
		}

		// else: nephews considered black
		this->_rebalance_red_parent( parent, sibling );
	}


	void	RBtree::_remove_black_leaf ( RBnode* node, RBnode* parent )
	{
		bool		dir;
		RBnode*		sibling;
		RBnode*		closenephew;
		RBnode*		distantnephew;

		dir = node->child_dir();
		parent->set_child( dir, NIL ); // remove node from the tree

		// the requirement 4 of a red-black tree is violated ( "Every path from
		// a given node to any of its descendant NIL nodes goes through the same
		// number of black nodes." )
		// this is fixed by the following rebalancing loop
		do
		{
			sibling = parent->get_child( 1 - dir );
			distantnephew = sibling->get_child( 1 - dir );
			closenephew = sibling->get_child( dir );

			if ( sibling->get_color() == RED )
			{ // sibling red, thus parent, closenephew and distantnephew black
				this->_rebalance_red_sibling( parent, dir, sibling, closenephew,
						distantnephew );
				return ; // deletion complete
			}

			// else: sibling is black
			if ( distantnephew != NIL && distantnephew->get_color() == RED )
			{ // distantnephew red
				this->_rebalance_red_distantnephew( parent, dir, sibling,
						distantnephew );
				return; // deletion complete
			}

			// else: distantnephew is black
			if ( closenephew != NIL && closenephew->get_color() == RED )
			{ // closenephew red
				this->_rebalance_red_closenephew( parent, dir, sibling,
						closenephew, distantnephew );
				return; // deletion complete
			}

			// else: both nephews are NIL (first iteration) or black (later)
			if ( parent->get_color() == RED )
			{ // parent red
				this->_rebalance_red_parent( parent, sibling );
				return; // deletion complete
			}

			// else: parent, sibling and nephews are black
			sibling->set_color( RED );
			node = parent; // new current node
			// iterate 1 black level (= 1 tree level) higher
			parent = node->get_parent();
			if ( parent != NULL )
				dir = node->child_dir();

		} while ( parent != NULL );
	}

	void	RBtree::remove ( RBnode* node )
	{
		RBnode*		parent;
		RBnode*		child;
		RBnode*		next;

		if ( node->get_child( LEFT ) != NIL
				&& node->get_child( RIGHT ) != NIL)
		{ // node has two children
			// swap the parent, children pointers and the color with next node
			next = node->get_next( RIGHT );
			node->swap_position( next, &_root );
		}

		// from now node has zero or one child

		parent = node->get_parent();
		if ( node->get_color() == RED )
		{ // node is red and thus has either zero or two children, and the
		  // previous swap eliminates the second case
			if ( parent == NULL ) // node is root
				_root = NIL;
			else
				parent->set_child( node->child_dir(), NIL );
			return ; // deletion complete
		}

		// else: node is black
		child = node->get_child( LEFT );
		if ( child == NIL )
			child = node->get_child( RIGHT );
		if ( child != NIL )
		{ // node is black and has exactly one child
			child->set_color( BLACK );
			child->set_parent( parent );
			if ( parent == NULL ) // node is root
				_root = child;
			else
				parent->set_child( node->child_dir(), child );
			return ; // deletion complete
		}

		// else: node is black and does not have any children
		if ( parent == NULL )
		{ // node is the root
			_root = NIL;
			return ; // deletion complete
		}
		this->_remove_black_leaf( node, parent ); // complex case
	}

} // namespace ft
