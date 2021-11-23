/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:52:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/23 17:20:41 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RBTREE_HPP__
# define __RBTREE_HPP__

namespace	ft
{
	enum	color_t
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
		enum color_t	color;
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
	bool	child_dir( RBnode* node )
	{
		return ( node == node->parent->right ? RIGHT : LEFT );
	}

	RBnode*	get_parent( RBnode* node )
	{
		// The parent of the root RBnode is set to NULL.
		return ( node == NULL ? NULL : node->parent );
	}

	RBnode*	get_grandparent( RBnode* node )
	{
		// Will return NULL if node is root or child of root
		return ( get_parent( get_parent( node ) ) );
	}

	RBnode*	get_sibling( RBnode* node )
	{
		RBnode*	parent;
		
		parent = get_parent( node );
		if ( parent == NULL )
			return ( NULL );

		return ( parent->child[1 - child_dir( node )] );
	}

	RBnode*	get_uncle( RBnode* node )
	{
		RBnode*	parent;
		
		parent = get_parent( node );
		if ( parent == NULL )
			return ( NULL );

		return ( get_sibling( parent ) );
	}

	RBnode*	get_closenephew( RBnode* node )
	{
		RBnode* parent;
		RBnode* sibling;
		int		dir;
		
		parent = get_parent( node );
		if ( parent == NULL )
			return ( NULL );
		dir = child_dir( node );
		sibling = parent->child[1 - dir];
		if ( sibling == NIL )
			return ( NULL );

		return ( sibling->child[dir] );
	}

	RBnode*	get_distantnephew( RBnode* node )
	{
		RBnode* parent;
		RBnode* sibling;
		int		dir;
		
		parent = get_parent( node );
		if ( parent == NULL )
			return ( NULL );
		dir = child_dir( node );
		sibling = parent->child[1 - dir];
		if ( sibling == NIL )
			return ( NULL );

		return ( sibling->child[1 - dir] );
	}

	RBnode*	rotate_subtree( RBtree* tree, RBnode* parent /* root of subtree (may be the root of tree) */, int dir )
	{
		RBnode*	grandparent;
		RBnode* sibling;
		RBnode* closenephew;
		
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

#define rotate(node,dir) rotate_subtree(tree,node,dir)
#define rotate_left(node)    rotate_subtree(tree,node,LEFT)
#define rotate_right(node)   rotate_subtree(tree,node,RIGHT)

} // namespace ft

#endif // __RBTREE_HPP__
