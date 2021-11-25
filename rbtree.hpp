/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:52:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/25 17:55:55 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RBTREE_HPP__
# define __RBTREE_HPP__

namespace	ft
{
	enum	e_color
	{
		BLACK,
		RED
	};

	struct	RBnode
	{
		RBnode*			parent;   // == NULL if root of the tree
		RBnode*			child[2]; // == NIL if child is empty
		// Index is:
		//   LEFT  := 0, if (key < parent->key)
		//   RIGHT := 1, if (key > parent->key)
		enum e_color	color;
		void*			content;
	};

	struct	RBtree
	{
		RBnode*		root; // == NIL if tree is empty
	};

#define	NIL		NULL // null pointer  or  pointer to sentinel RBnode
#define	LEFT	0
#define	RIGHT	1
#define	left	child[LEFT]
#define	right	child[RIGHT]

	// Get the child direction (∈ { LEFT, RIGHT })
	//   of the non-root non-NIL  RBnode* node:
	bool	child_dir ( RBnode* node )
	{
		return ( node == node->parent->right ? RIGHT : LEFT );
	}

	RBnode*	get_parent ( RBnode* node )
	{
		// The parent of the root RBnode is set to NULL.
		return ( node == NULL ? NULL : node->parent );
	}

	RBnode*	get_grandparent( RBnode* node )
	{
		// Will return NULL if node is root or child of root
		return ( get_parent( get_parent( node ) ) );
	}

	RBnode*	get_sibling ( RBnode* node )
	{
		RBnode*	parent;
		
		parent = get_parent( node );
		if ( parent == NULL )
			return ( NULL );

		return ( parent->child[1 - child_dir( node )] );
	}

	RBnode*	get_uncle ( RBnode* node )
	{
		RBnode*	parent;
		
		parent = get_parent( node );
		if ( parent == NULL )
			return ( NULL );

		return ( get_sibling( parent ) );
	}

	RBnode*	get_closenephew ( RBnode* node )
	{
		RBnode*	parent;
		RBnode*	sibling;
		bool	dir;
		
		parent = get_parent( node );
		if ( parent == NULL )
			return ( NULL );
		dir = child_dir( node );
		sibling = parent->child[1 - dir];
		if ( sibling == NIL )
			return ( NULL );

		return ( sibling->child[dir] );
	}

	RBnode*	get_distantnephew ( RBnode* node )
	{
		RBnode*	parent;
		RBnode*	sibling;
		bool	dir;
		
		parent = get_parent( node );
		if ( parent == NULL )
			return ( NULL );
		dir = child_dir( node );
		sibling = parent->child[1 - dir];
		if ( sibling == NIL )
			return ( NULL );

		return ( sibling->child[1 - dir] );
	}

	RBnode*	rotate_subtree ( RBtree* tree, RBnode* parent /* root of subtree (may be the root of tree) */, int dir )
	{
		RBnode*	grandparent;
		RBnode*	sibling;
		RBnode*	closenephew;
		
		grandparent = get_parent( parent );
		sibling = parent->child[1 - dir];
		if ( sibling == NIL ) // pointer to true RBnode required
			return ( NULL );
		closenephew = sibling->child[dir];

		parent->child[1 - dir] = closenephew;
		if ( closenephew != NIL )
			closenephew->parent = parent;
		sibling->child[dir] = parent;
		parent->parent = sibling;
		sibling->parent = grandparent;
		if ( grandparent != NULL )
			grandparent->child[child_dir( parent )] = sibling;
		else
			tree->root = sibling;

		return ( sibling ); // new root of subtree
	}

	void	insert_rebalancing_loop ( RBtree* tree, RBnode* node,
			RBnode* parent, bool dir )
	{
		RBnode*	grandparent;  // -> parent node of parent
		RBnode*	uncle;  // -> uncle of node

		while ( parent != NULL )
		{
			if (parent->color == BLACK)
				return ; // insertion complete
			// From now on parent is red.
			grandparent = get_parent( parent );
			if ( grandparent == NULL )
			{ // parent is the root and red:
				parent->color = BLACK;
				return ; // insertion complete
			}
			// else: parent red and grandparent!=NULL.
			dir = child_dir( parent ); // the side of parent grandparent on which node parent is located
			uncle = grandparent->child[1 - dir]; // uncle
			if ( uncle == NIL || uncle->color == BLACK ) // considered black
			{ // parent red && uncle black:
				if ( node == parent->child[1 - dir] )
				{ // Case_I5 (parent red && uncle black && node inner grandchild of grandparent):
					rotate_subtree( tree, parent, dir ); // parent is never the root
					node = parent; // new current node
					parent = grandparent->child[dir]; // new parent of node
					// fall through to Case_I6
				}
				// Case_I6 (parent red && uncle black && node outer grandchild of grandparent):
				rotate_subtree( tree, grandparent, 1 - dir ); // grandparent may be the root
				parent->color = BLACK;
				grandparent->color = RED;
				return ; // insertion complete
			}
			// Case_I2 (parent+uncle red):
			parent->color = BLACK;
			uncle->color = BLACK;
			grandparent->color = RED;
			node = grandparent; // new current node
			// iterate 1 black level
			//   (= 2 tree levels) higher
			parent = node->parent;
		}
	}

	void	rbtree_insert ( RBtree* tree, RBnode* node, RBnode* parent /* -> parent node of node ( may be NULL ) */,
			bool dir )
	{
		node->color = RED;
		node->left  = NIL;
		node->right = NIL;
		node->parent = parent;
		if ( parent == NULL )
		{   // There is no parent
			tree->root = node;     // node is the new root of the tree tree.
			return ; // insertion complete
		}
		parent->child[dir] = node; // insert node as dir-child of parent

		insert_rebalancing_loop( tree, node, parent, dir );
	}

} // namespace ft

#endif // __RBTREE_HPP__
