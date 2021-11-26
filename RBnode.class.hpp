/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBnode.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:52:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/26 15:03:04 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RBNODE_CLASS_HPP__
# define __RBNODE_CLASS_HPP__

#include <cstddef> // NULL

namespace	ft
{

#define BLACK	0
#define RED		1

#define	NIL		NULL // null pointer  or  pointer to sentinel RBnode

#define	LEFT	0
#define	RIGHT	1

	class	RBnode
	{
		private:

			void*		_content;
			bool		_color;
			RBnode*		_parent;   // == NULL if root of the tree
			RBnode*		_child[2]; // == NIL if child is empty
			// Index is:
			//   LEFT  := 0, if (key < parent->key)
			//   RIGHT := 1, if (key > parent->key)

			RBnode ( void );

		public:

			RBnode ( void* content );

			bool		get_color ( void );
			void		set_color ( bool color );
			bool		child_dir ( void );
			void		set_child ( bool dir, RBnode* child );
			RBnode*		get_child ( bool dir );
			void		set_parent ( RBnode* parent );
			RBnode*		get_parent ( void );
			RBnode*		get_grandparent ( void );
			RBnode*		get_sibling ( void );
			RBnode*		get_uncle ( void );
			RBnode*		get_closenephew ( void );
			RBnode*		get_distantnephew ( void );

	}; // class RBnode

} // namespace ft

#endif // __RBNODE_CLASS_HPP__
