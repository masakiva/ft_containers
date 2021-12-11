/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBnode.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:52:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/11 14:23:19 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RBNODE_CLASS_HPP__
# define __RBNODE_CLASS_HPP__

#include <cstddef> // NULL

namespace	ft
{

#define BLACK	0
#define RED		1

#define	NIL		NULL // pointer to sentinel RBnode

#define	LEFT	0
#define	RIGHT	1

	class	RBnode
	{
		private:

			void*		_content;
			RBnode*		_parent;
			RBnode*		_child[2];
			bool		_color;

			RBnode ( void );

			RBnode*		_get_next_parent ( bool dir , int i) const;

		public:

			RBnode ( void* content );

			void*		get_content ( void ) const;
			bool		get_color ( void ) const;
			void		set_color ( bool color );
			bool		child_dir ( void ) const;
			void		set_child ( bool dir, RBnode* child );
			RBnode*		get_child ( bool dir ) const;
			void		set_parent ( RBnode* parent );
			RBnode*		get_parent ( void ) const;
			RBnode*		get_grandparent ( void ) const;
			RBnode*		get_sibling ( void ) const;
			RBnode*		get_uncle ( void ) const;
			RBnode*		get_closenephew ( void ) const;
			RBnode*		get_distantnephew ( void ) const;

			RBnode*		get_next ( bool dir ) const;
			void		swap_position ( RBnode* other, RBnode** root_link );

	}; // class RBnode

} // namespace ft

#endif // __RBNODE_CLASS_HPP__
