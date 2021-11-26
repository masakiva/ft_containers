/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:41:07 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/26 19:00:53 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBtree.class.hpp"

namespace	ft
{

	RBtree::RBtree ( void ) : _root( NIL ) { }

	RBnode*	RBtree::get_root( void )
	{
		return ( _root );
	}

	void	RBtree::_rotate_subtree ( RBnode* parent /* root of subtree (may be the root of tree) */, int dir )
	{
		RBnode*	grandparent;
		RBnode*	sibling;
		RBnode*	closenephew;

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
			grandparent->set_child( parent->child_dir(), sibling );
		else
			_root = sibling;
	}

	void	RBtree::_insert_rebalancing_loop ( RBnode* node, RBnode* parent,
			bool dir )
	{
		RBnode*	grandparent;  // -> parent node of parent
		RBnode*	uncle;  // -> uncle of node

		while ( parent != NULL )
		{
			if (parent->get_color() == BLACK)
				break ; // insertion complete
			// From now on parent is red.
			grandparent = parent->get_parent();
			if ( grandparent == NULL )
			{ // parent is the root and red:
				parent->set_color( BLACK );
				break ; // insertion complete
			}
			// else: parent red and grandparent!=NULL.
			dir = parent->child_dir(); // the side of parent grandparent on which node parent is located
			uncle = grandparent->get_child( 1 - dir );
			if ( uncle == NIL || uncle->get_color() == BLACK ) // considered black
			{ // parent red && uncle black:
				if ( node == parent->get_child( 1 - dir ) )
				{ // Case_I5 (parent red && uncle black && node inner grandchild of grandparent):
					this->_rotate_subtree( parent, dir ); // parent is never the root
					node = parent; // new current node
					parent = grandparent->get_child( dir ); // new parent of node
					// fall through to Case_I6
				}
				// Case_I6 (parent red && uncle black && node outer grandchild of grandparent):
				this->_rotate_subtree( grandparent, 1 - dir ); // grandparent may be the root
				parent->set_color( BLACK );
				grandparent->set_color( RED );
				break ; // insertion complete
			}
			// Case_I2 (parent+uncle red):
			parent->set_color( BLACK );
			uncle->set_color( BLACK );
			grandparent->set_color( RED );
			node = grandparent; // new current node
			// iterate 1 black level
			//   (= 2 tree levels) higher
			parent = node->get_parent();
		}
	}

	void	RBtree::insert ( RBnode* node, RBnode* parent /* -> parent node of node ( may be NULL ) */, bool dir )
	{
		node->set_color( RED );
		node->set_child( LEFT, NIL );
		node->set_child( RIGHT, NIL );
		node->set_parent( parent );
		if ( parent == NULL )
		{   // There is no parent
			_root = node;     // node is the new root of the tree tree.
			return ; // insertion complete
		}
		parent->set_child( dir, node ); // insert node as dir-child of parent

		this->_insert_rebalancing_loop( node, parent, dir );
	}

} // namespace ft
