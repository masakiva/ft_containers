/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.templatedef.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:43:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/01 16:22:31 by mvidal-a         ###   ########.fr       */
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

			++it;

			return ( it );
		}


	/******* MODIFIERS ********************************************************/

	template < class Key, class T, class Compare, class Alloc >
		void map<Key,T,Compare,Alloc>::_insert_in_tree ( RBnode* new_node,
						value_type* new_pair ) // comment this func
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
			this->print_tree();
			std::cout << std::endl;
		}


	/******* ALLOCATOR ********************************************************/

	/* get_allocator */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::allocator_type
				map<Key,T,Compare,Alloc>::get_allocator ( void ) const
		{
			return ( _alloc );
		}



	template < class Key, class T, class Compare, class Alloc >
		void	map<Key,T,Compare,Alloc>::_print_node ( RBnode* node, bool dir, int i ) const
		{
			value_type*	pair;

			if ( node == NIL )
			{
				std::cout << ">>> " << ( dir ? "\e[34mright\e[0m" : "\e[32mleft\e[0m" )
					<< " of " << i << ": \e[30;43mNIL\e[0m" << std::endl;
			}
			else
			{
				int	new_i = i + (dir ? 10 : 100 );
				std::cout << ">>> " << new_i << ": "
					<< ( dir ? "\e[34mright\e[0m" : "\e[32mleft\e[0m" ) << " of " << i << ": ";
				pair = static_cast<value_type*>( node->get_content() );
				std::cout << ( node->get_color() == RED ?
						"\e[41mRED\e[0m" : "\e[30;47mBLACK\e[0m" );
				std::cout << std::endl << pair->first << std::endl;// << pair->second << std::endl;
				this->_print_node( node->get_child( LEFT ), LEFT, new_i );
				this->_print_node( node->get_child( RIGHT ), RIGHT, new_i );
			}
		}

	template < class Key, class T, class Compare, class Alloc >
		void	map<Key,T,Compare,Alloc>::print_tree ( void ) const
		{
			RBnode*		root;
			value_type*	pair;

			std::cout << ">>> ROOT: ";
			root = _tree.get_root();
			if ( root == NIL )
				std::cout << ": \e[30;43mNIL\e[0m" << std::endl;
			else
			{
				pair = static_cast<value_type*>( root->get_content() );
				std::cout << ( root->get_color() == RED ?
						"\e[41mRED\e[0m" : "\e[30;47mBLACK\e[0m" );
				std::cout << std::endl << pair->first << std::endl;// << pair->second << std::endl;
				this->_print_node( root->get_child( LEFT ), LEFT, 0 );
				this->_print_node( root->get_child( RIGHT ), RIGHT, 0 );
			}
		}


} // namespace ft

#endif // __MAP_TEMPLATEDEF_HPP__
