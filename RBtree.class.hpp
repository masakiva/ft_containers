/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:52:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/28 00:51:41 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RBTREE_CLASS_HPP__
# define __RBTREE_CLASS_HPP__

#include "RBnode.class.hpp"

namespace	ft
{

	class	RBtree
	{
		private:

			RBnode*		_root; // == NIL if tree is empty

			void	_rotate_subtree ( RBnode* parent, int dir );
			void	_insert_rebalancing_loop ( RBnode* node, RBnode* parent,
					bool dir );

		public:

			RBtree ( void );

			RBnode*	get_root( void );
			void	insert ( RBnode* node, RBnode* parent, bool dir );

	}; // class RBtree

} // namespace ft

#endif // __RBTREE_CLASS_HPP__
