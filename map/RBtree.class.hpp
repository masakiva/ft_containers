/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:52:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/11 14:22:35 by mvidal-a         ###   ########.fr       */
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

			RBnode*		_root;

			void	_rotate_subtree ( RBnode* parent, bool dir );
			void	_insert_rebalancing_loop ( RBnode* node, RBnode* parent );
			void	_remove_black_leaf ( RBnode* node, RBnode* parent );
			void	_rebalance_red_parent ( RBnode* parent, RBnode *sibling );
			void	_rebalance_red_distantnephew ( RBnode* parent, bool dir,
					RBnode *sibling, RBnode* distantnephew );
			void	_rebalance_red_closenephew ( RBnode* parent, bool dir,
					RBnode *sibling, RBnode* closenephew,
					RBnode* distantnephew );
			void	_rebalance_red_sibling ( RBnode* parent, bool dir,
					RBnode *sibling, RBnode* closenephew,
					RBnode* distantnephew );

		public:

			RBtree ( void );

			RBnode*		get_root ( void ) const;
			void		set_root_to_nil ( void );
			RBnode*		get_extremity ( bool dir ) const;
			void		insert ( RBnode* node, RBnode* parent, bool dir );
			void		remove ( RBnode* node );

	}; // class RBtree

} // namespace ft

#endif // __RBTREE_CLASS_HPP__
