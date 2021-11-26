/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.templatedef.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:43:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/26 19:11:00 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_TEMPLATEDEF_HPP__
# define __MAP_TEMPLATEDEF_HPP__

namespace	ft
{

	/******* CANONICAL FORM ***************************************************/

	/* default constructor */
	template <	class Key, class T, class Compare, class Alloc >
		map<Key,T,Compare,Alloc>::map ( const key_compare& comp,
				const allocator_type& alloc ) :
			_alloc( alloc ),
			_size( 0 ),
			_comp( comp )

		{
		}


	/******* MODIFIERS ********************************************************/

	/* insert (single element) */
	template <	class Key, class T, class Compare, class Alloc >
		void
			map<Key,T,Compare,Alloc>::insert ( const value_type& val )
		{
			RBnode*		node;
			value_type*	pair;
			RBnode*		root;

			pair = _alloc.allocate( 1 );
			_alloc.construct( pair, val );
			node = _alloc_node.allocate( 1 );
			_alloc_node.construct( node, pair );

			root = _tree.get_root();
			if ( root == NIL )
				_tree.insert( node, NULL, LEFT );
			else if ( root
		}


	/******* ALLOCATOR ********************************************************/

	/* get_allocator */
	template <	class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::allocator_type
				map<Key,T,Compare,Alloc>::get_allocator ( void ) const
		{
			return ( _alloc );
		}


} // namespace ft

#endif // __MAP_TEMPLATEDEF_HPP__
