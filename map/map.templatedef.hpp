/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.templatedef.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:43:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/29 18:36:44 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_TEMPLATEDEF_HPP__
# define __MAP_TEMPLATEDEF_HPP__

namespace	ft
{

	/******* CANONICAL FORM ***************************************************/

	/* default constructor */
	template < class Key, class T, class Compare, class Alloc >
		map<Key,T,Compare,Alloc>::map ( const key_compare& comp,
				const allocator_type& alloc ) :
			_size( 0 ),
			_comp( comp ),
			_alloc( alloc )
		{
		}


	/******* ITERATORS ********************************************************/

	/* begin */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::iterator
				map<Key,T,Compare,Alloc>::begin ( void )
		{
			iterator	it( _tree.get_first_node() );

			return ( it );
		}

	/* end */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::iterator
				map<Key,T,Compare,Alloc>::end ( void )
		{
			iterator	it( _tree.get_last_node() );

			return ( it );
		}


	/******* MODIFIERS ********************************************************/

	template < class Key, class T, class Compare, class Alloc >
		void map<Key,T,Compare,Alloc>::_insert_in_tree ( RBnode* new_node,
						value_type* new_pair )
		{
			RBnode*		parent;
			RBnode*		cur_node;
			value_type*	cur_pair;

			parent = _tree.get_root();
			while ( parent != NULL )
			{
				cur_pair = static_cast<value_type*>( parent->get_content() );
				if ( cur_pair->first == new_pair->first )
					return ;
				if ( _comp( new_pair->first, cur_pair->first ) )
				{
					cur_node = parent->get_child( LEFT );
					if ( cur_node == NIL )
					{
						_tree.insert( new_node, parent, LEFT );
						return ;
					}
					else
						parent = cur_node;
				}
				else
				{
					cur_node = parent->get_child( RIGHT );
					if ( cur_node == NIL )
					{
						_tree.insert( new_node, parent, RIGHT );
						return ;
					}
					else
						parent = cur_node;
				}
			}
			_tree.insert( new_node, NULL, LEFT ); // insert 
		}

	/* insert (single element) */
	template < class Key, class T, class Compare, class Alloc >
		void map<Key,T,Compare,Alloc>::insert ( const value_type& val )
		{
			RBnode*		new_node;
			value_type*	new_pair;

			new_pair = _alloc.allocate( 1 ); // allocate for the pair
			_alloc.construct( new_pair, val );
			new_node = _alloc_node.allocate( 1 ); // allocate for the node
			_alloc_node.construct( new_node, new_pair );

			this->_insert_in_tree( new_node, new_pair );
		}


	/******* ALLOCATOR ********************************************************/

	/* get_allocator */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::allocator_type
				map<Key,T,Compare,Alloc>::get_allocator ( void ) const
		{
			return ( _alloc );
		}


} // namespace ft

#endif // __MAP_TEMPLATEDEF_HPP__
