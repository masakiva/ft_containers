/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:52:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/30 19:31:07 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RBTREE_CLASS_HPP__
# define __RBTREE_CLASS_HPP__

#include "RBnode.class.hpp"
#include <iostream>

namespace	ft
{

	class	RBtree
	{
		private:

			RBnode*		_root;

			void	_rotate_subtree ( RBnode* parent, bool dir );
			void	_insert_rebalancing_loop ( RBnode* node, RBnode* parent );

			void	_print_node ( RBnode* node, bool dir, int i ) const; /////////////////////////////

		public:

			void	print_tree ( void ) const; //////////////////////////////////////////////

			RBtree ( void );

			RBnode*	get_root ( void ) const;
			RBnode*	get_first_node ( void ) const;
			RBnode*	get_last_node ( void ) const;
			void	insert ( RBnode* node, RBnode* parent, bool dir );

	}; // class RBtree

} // namespace ft

#endif // __RBTREE_CLASS_HPP__
