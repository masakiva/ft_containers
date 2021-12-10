/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.templatedef.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:43:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/10 16:04:58 by mvidal-a         ###   ########.fr       */
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
		{ }

	/* range constructor */
	template < class Key, class T, class Compare, class Alloc >
		template < class InputIt >
			map<Key,T,Compare,Alloc>::map ( InputIt first, InputIt last,
					const key_compare& comp, const allocator_type& alloc ) :
			_size( 0 ),
			_comp( comp ),
			_alloc( alloc )
			{
				for ( ; first != last; first++ )
				{
					this->insert( *first );
				}
			}

	/* copy constructor */
	template < class Key, class T, class Compare, class Alloc >
		map<Key,T,Compare,Alloc>::map ( const map& src ) :
			_size( 0 ),
			_alloc( src._alloc )
		{
			*this = src;
		}

	/* destructor */
	template < class Key, class T, class Compare, class Alloc >
		map<Key,T,Compare,Alloc>::~map ( void )
		{
			this->clear();
		}

	/* = */
	template < class Key, class T, class Compare, class Alloc >
		map<Key,T,Compare,Alloc>&
				map<Key,T,Compare,Alloc>::operator= ( const map& rhs )
		{
			if ( this == &rhs )
				return ( *this );

			if ( _size > 0 )
				this->clear();

			_comp = rhs._comp;
			for ( const_iterator it = rhs.begin(); it != rhs.end(); it++ )
				this->insert( *it );
			_size = rhs._size;

			return ( *this );
		}


	/******* ITERATORS ********************************************************/

	/* begin */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::iterator
				map<Key,T,Compare,Alloc>::begin ( void )
		{
			iterator	it( _tree.get_extremity( LEFT ), this );

			return ( it );
		}

	/* begin (const) */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::const_iterator
				map<Key,T,Compare,Alloc>::begin ( void ) const
		{
			const_iterator	it( _tree.get_extremity( LEFT ), (void*) this );

			return ( it );
		}

	/* end */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::iterator
				map<Key,T,Compare,Alloc>::end ( void )
		{
			iterator	it( _tree.get_extremity( RIGHT ), this );

			std::cout << "END" << std::endl;
			if ( it.get_node_ptr() != NULL )
				++it;

			return ( it );
		}

	/* end (const) */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::const_iterator
				map<Key,T,Compare,Alloc>::end ( void ) const
		{
			const_iterator	it( _tree.get_extremity( RIGHT ), (void*) this );

			if ( it.get_node_ptr() != NULL )
				++it;

			return ( it );
		}

	/* rbegin */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::reverse_iterator
				map<Key,T,Compare,Alloc>::rbegin ( void )
		{
			iterator			it = this->end();
			reverse_iterator	rev_it( it );

			return ( rev_it );
		}

	/* rbegin (const) */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::const_reverse_iterator
				map<Key,T,Compare,Alloc>::rbegin ( void ) const
		{
			const_iterator			it = this->end();
			const_reverse_iterator	rev_it( it );

			return ( rev_it );
		}

	/* rend */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::reverse_iterator
				map<Key,T,Compare,Alloc>::rend ( void )
		{
			iterator			it = this->begin();
			reverse_iterator	rev_it( it );

			return ( rev_it );
		}

	/* rend (const) */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::const_reverse_iterator
				map<Key,T,Compare,Alloc>::rend ( void ) const
		{
			const_iterator			it = this->begin();
			const_reverse_iterator	rev_it( it );

			return ( rev_it );
		}


	/******* CAPACITY *********************************************************/

	/* empty */
	template < class Key, class T, class Compare, class Alloc >
		bool	map<Key,T,Compare,Alloc>::empty ( void ) const
		{
			return ( _size == 0 );
		}

	/* size */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::size_type
				map<Key,T,Compare,Alloc>::size ( void ) const
		{
			return ( _size );
		}

	/* max_size */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::size_type
				map<Key,T,Compare,Alloc>::max_size ( void ) const
		{
			return ( _alloc.max_size() );
		}


	/******* ELEMENT ACCESS ***************************************************/

	/* [] */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::mapped_type&
				map<Key,T,Compare,Alloc>::operator[] ( const key_type& key )
		{
			RBnode*			cur_node;
			value_type*		cur_pair;
			RBnode*			child;

			cur_node = _tree.get_root();
			while ( cur_node != NIL )
			{ // search for the key in the tree
				cur_pair = static_cast<value_type*>( cur_node->get_content() );
				if ( _comp( key, cur_pair->first ) )
					child = cur_node->get_child( LEFT );
				else if ( _comp( cur_pair->first, key ) )
					child = cur_node->get_child( RIGHT );
				else
				{ // key found
					return ( cur_pair->second ); // return existent mapped value
				}
				cur_node = child; // iterate one level deeper (if child != NIL)
			}

			// key not found:
			// insert pair with this key and a mapped value default constructed
			pair<iterator,bool>		new_pair =
				this->insert( make_pair( key, mapped_type() ) );

			return ( new_pair.first->second ); // return ref to new mapped value
		}

	/* at */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::mapped_type&
				map<Key,T,Compare,Alloc>::at ( const key_type& key )
		{
			RBnode*			cur_node;
			value_type*		cur_pair;
			RBnode*			child;

			cur_node = _tree.get_root();
			while ( cur_node != NIL )
			{ // search for the key in the tree
				cur_pair = static_cast<value_type*>( cur_node->get_content() );
				if ( _comp( key, cur_pair->first ) )
					child = cur_node->get_child( LEFT );
				else if ( _comp( cur_pair->first, key ) )
					child = cur_node->get_child( RIGHT );
				else
				{ // key found
					return ( cur_pair->second ); // return existent mapped value
				}
				cur_node = child; // iterate one level deeper (if child != NIL)
			}

			// key not found
			throw std::out_of_range(
					"at() argument does not match an existing key in the map" );
		}

	/* at (const) */
	template < class Key, class T, class Compare, class Alloc >
		const typename map<Key,T,Compare,Alloc>::mapped_type&
				map<Key,T,Compare,Alloc>::at ( const key_type& key ) const
		{
			RBnode*			cur_node;
			value_type*		cur_pair;
			RBnode*			child;

			cur_node = _tree.get_root();
			while ( cur_node != NIL )
			{ // search for the key in the tree
				cur_pair = static_cast<value_type*>( cur_node->get_content() );
				if ( _comp( key, cur_pair->first ) )
					child = cur_node->get_child( LEFT );
				else if ( _comp( cur_pair->first, key ) )
					child = cur_node->get_child( RIGHT );
				else
				{ // key found
					return ( cur_pair->second ); // return existent mapped value
				}
				cur_node = child; // iterate one level deeper (if child != NIL)
			}

			// key not found
			throw std::out_of_range(
					"at() argument does not match an existing key in the map" );
		}


	/******* MODIFIERS ********************************************************/

	/* insert (single element) */
	template < class Key, class T, class Compare, class Alloc >
		pair<typename map<Key,T,Compare,Alloc>::iterator,bool>
				map<Key,T,Compare,Alloc>::insert ( const value_type& val )
		{
			RBnode*		new_node;
			value_type*	new_pair;

			new_pair = _alloc.allocate( 1 ); // allocate for the pair
			_alloc.construct( new_pair, val ); // construct pair
			new_node = _alloc_node.allocate( 1 ); // allocate for the node
			_alloc_node.construct( new_node, new_pair ); // construct node

			return ( this->_search_and_insert( new_node, new_pair ) );
		}

	/* insert (single element, with hint for position) */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::iterator
				map<Key,T,Compare,Alloc>::insert ( iterator pos,
				const value_type& val )
		{
			RBnode*		new_node;
			value_type*	new_pair;

			new_pair = _alloc.allocate( 1 ); // allocate for the pair
			_alloc.construct( new_pair, val ); // construct pair
			new_node = _alloc_node.allocate( 1 ); // allocate for the node
			_alloc_node.construct( new_node, new_pair ); // construct node

			return ( this->_insert_with_iterator( pos, new_node, new_pair ) );
		}

	/* insert (from a range of iterators) */
	template < class Key, class T, class Compare, class Alloc >
		template < class InputIt >
			void	map<Key,T,Compare,Alloc>::insert ( InputIt first,
					InputIt last )
			{
				for ( ; first != last; first++ )
				{
					this->insert( *first );
				}
			}

	/* erase (single element, from iterator) */
	template < class Key, class T, class Compare, class Alloc >
		void	map<Key,T,Compare,Alloc>::erase ( iterator pos )
		{
			RBnode*		node;

			node = pos.get_node_ptr();

			_tree.remove( node );
			_size--;

			this->_free_one_node( node );
		}

	/* erase (single element, from key) */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::size_type
				map<Key,T,Compare,Alloc>::erase ( const key_type& key )
		{
			return ( this->_search_and_erase( key ) );
		}

	/* erase (from a range of iterators) */
	template < class Key, class T, class Compare, class Alloc >
		void	map<Key,T,Compare,Alloc>::erase ( iterator first,
				iterator last )
		{
			iterator	it;

			while ( first != last )
			{
				it = first;
				++first;
				this->erase( it );
			}
		}

	/* swap */
	template < class Key, class T, class Compare, class Alloc >
		void	map<Key,T,Compare,Alloc>::swap ( map& other )
		{
			size_type		temp_size;
			RBtree			temp_tree;
			key_compare		temp_comp;

			temp_size = other._size;
			other._size = _size;
			_size = temp_size;

			temp_tree = other._tree;
			other._tree = _tree;
			_tree = temp_tree;

			temp_comp = other._comp;
			other._comp = _comp;
			_comp = temp_comp;
		}

	/* clear */
	template < class Key, class T, class Compare, class Alloc >
		void	map<Key,T,Compare,Alloc>::clear ( void )
		{
			RBnode*		node;

			node = _tree.get_root();
			if ( node != NIL )
				this->_clear_deeper( node );
			_tree.set_root_to_nil();
			_size = 0;
		}


	/******* OBSERVERS ********************************************************/

	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::key_compare
				map<Key,T,Compare,Alloc>::key_comp ( void ) const
		{
			return ( _comp );
		}

	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::value_compare
				map<Key,T,Compare,Alloc>::value_comp ( void ) const
		{
			value_compare	value_comp( _comp );

			return ( value_comp );
		}


	/******* OPERATIONS *******************************************************/

	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::iterator
				map<Key,T,Compare,Alloc>::find ( const key_type& key )
		{
			RBnode*			cur_node;
			value_type*		cur_pair;

			cur_node = _tree.get_root();
			while ( cur_node != NIL )
			{
				cur_pair = static_cast<value_type*>( cur_node->get_content() );
				if ( _comp( key, cur_pair->first ) )
					cur_node = cur_node->get_child( LEFT );
				else if ( _comp( cur_pair->first, key ) )
					cur_node = cur_node->get_child( RIGHT );
				else
				{ // found the key
					iterator	it( cur_node, this );
					return ( it );
				}
			}

			return ( this->end() ); // key not found
		}

	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::const_iterator
				map<Key,T,Compare,Alloc>::find ( const key_type& key ) const
		{
			RBnode*			cur_node;
			value_type*		cur_pair;

			cur_node = _tree.get_root();
			while ( cur_node != NIL )
			{
				cur_pair = static_cast<value_type*>( cur_node->get_content() );
				if ( _comp( key, cur_pair->first ) )
					cur_node = cur_node->get_child( LEFT );
				else if ( _comp( cur_pair->first, key ) )
					cur_node = cur_node->get_child( RIGHT );
				else
				{ // found the key
					iterator	it( cur_node, this );
					return ( it );
				}
			}

			return ( this->end() ); // key not found
		}

	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::size_type
				map<Key,T,Compare,Alloc>::count ( const key_type& key ) const
		{
			RBnode*			cur_node;
			value_type*		cur_pair;

			cur_node = _tree.get_root();
			while ( cur_node != NIL )
			{
				cur_pair = static_cast<value_type*>( cur_node->get_content() );
				if ( _comp( key, cur_pair->first ) )
					cur_node = cur_node->get_child( LEFT );
				else if ( _comp( cur_pair->first, key ) )
					cur_node = cur_node->get_child( RIGHT );
				else
				{ // found the key
					return ( 1 );
				}
			}

			return ( 0 ); // key not found
		}

	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::iterator
				map<Key,T,Compare,Alloc>::lower_bound ( const key_type& key )
		{
			iterator		it = this->begin();

			for ( ; it != this->end(); ++it )
			{
				if ( !_comp( it->first, key ) )
					return ( it );
			}

			return ( this->end() );
		}

	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::const_iterator
				map<Key,T,Compare,Alloc>::lower_bound ( const key_type& key )
				const
		{
			iterator		it = this->begin();

			for ( ; it != this->end(); ++it )
			{
				if ( !_comp( it->first, key ) )
					return ( it );
			}

			return ( this->end() );
		}

	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::iterator
				map<Key,T,Compare,Alloc>::upper_bound ( const key_type& key )
		{
			iterator		it = this->begin();

			for ( ; it != this->end(); ++it )
			{
				if ( _comp( key, it->first ) )
					return ( it );
			}

			return ( this->end() );
		}

	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::const_iterator
				map<Key,T,Compare,Alloc>::upper_bound ( const key_type& key )
				const
		{
			iterator		it = this->begin();

			for ( ; it != this->end(); ++it )
			{
				if ( !_comp( it->first, key ) )
					return ( it );
			}

			return ( this->end() );
		}

	template < class Key, class T, class Compare, class Alloc >
		pair<typename map<Key,T,Compare,Alloc>::iterator,
		typename map<Key,T,Compare,Alloc>::iterator>
				map<Key,T,Compare,Alloc>::equal_range ( const key_type& key )
		{
			return ( make_pair( lower_bound( key ), upper_bound( key ) ) );
		}

	template < class Key, class T, class Compare, class Alloc >
		pair<typename map<Key,T,Compare,Alloc>::const_iterator,
		typename map<Key,T,Compare,Alloc>::const_iterator>
				map<Key,T,Compare,Alloc>::equal_range ( const key_type& key )
				const
		{
			return ( make_pair( lower_bound( key ), upper_bound( key ) ) );
		}


	/******* ALLOCATOR ********************************************************/

	/* get_allocator */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::allocator_type
				map<Key,T,Compare,Alloc>::get_allocator ( void ) const
		{
			return ( _alloc );
		}


	/******* NON-MEMBER FUNCTIONS *********************************************/

	/* swap */
	template < class Key, class T, class Compare, class Alloc >
		void	swap ( map<Key,T,Compare,Alloc>& lhs,
				map<Key,T,Compare,Alloc>& rhs )
		{
			lhs.swap( rhs );
		}


	/******* HELPER FUNCTIONS *************************************************/

	/* _search_and_insert */
	template < class Key, class T, class Compare, class Alloc >
		pair<typename map<Key,T,Compare,Alloc>::iterator,bool>
				map<Key,T,Compare,Alloc>::_search_and_insert ( RBnode* new_node,
				value_type* new_pair )
		{
			RBnode*			cur_node;
			value_type*		cur_pair;
			RBnode*			child;
			iterator		it( new_node, this ); // element to return

			cur_node = _tree.get_root();
			if ( cur_node == NIL )
				_tree.insert( new_node, NULL, 0 ); // insert as tree root
			while ( cur_node != NIL )
			{
				cur_pair = static_cast<value_type*>( cur_node->get_content() );
				if ( _comp( new_pair->first, cur_pair->first ) )
				{ // with _comp defined from std::less<Key>, new_key < cur_key
					child = cur_node->get_child( LEFT );
					if ( child == NIL )
					{
						// insert as left child of cur_node
						_tree.insert( new_node, cur_node, LEFT );
						break ; // insertion complete
					}
				}
				else if ( _comp( cur_pair->first, new_pair->first ) )
				{ // ... new_key > cur_key
					child = cur_node->get_child( RIGHT );
					if ( child == NIL )
					{
						// insert as right child of cur_node
						_tree.insert( new_node, cur_node, RIGHT );
						break ; // insertion complete
					}
				}
				else
				{ // the same key is already in the tree
					it.set_node_ptr( cur_node, this ); // return existent node
					this->_free_one_node( new_node );
					return ( make_pair( it, false ) ); // false: no insertion
				}
				cur_node = child; // child exists: iterate one level deeper
			}
			_size++;

			return ( make_pair( it, true ) ); // true: node inserted
		}

	/* _insert_with_iterator */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::iterator
				map<Key,T,Compare,Alloc>::_insert_with_iterator ( iterator pos,
				RBnode* new_node, value_type* new_pair )
		{
			RBnode* 	cur_node;
			RBnode* 	next_node;

			cur_node = pos.get_node_ptr();
			if ( pos.get_map_ptr() == this // pos points to the same map
					&& cur_node != NULL // pos != map.end()
					&& _comp( pos->first, new_pair->first ) )
			{ // new pair/node comes after pos
				++pos;
				next_node = pos.get_node_ptr();
				if ( next_node == NULL )
				{ // given pos is the last node: insert at the end of the tree
					_tree.insert( new_node, cur_node, RIGHT );
					// return iterator to new node
					pos.set_node_ptr( new_node, this );
					_size++;
					return ( pos );
				}
				if ( _comp( new_pair->first, pos->first ) )
				{ // new pair/node comes before incremented pos
					// insert as right or left child whether it already exists
					if ( cur_node->get_child( RIGHT ) == NIL )
						_tree.insert( new_node, cur_node, RIGHT );
					else
						_tree.insert( new_node, next_node, LEFT );
					// return iterator to new node
					pos.set_node_ptr( new_node, this );
					_size++;
					return ( pos );
				}
			}

			// pos does not immediately precede the newly inserted node
			// so it's a false hint: fall back to general insert function
			return ( this->_search_and_insert( new_node, new_pair ).first );
		}

	/* _search_and_erase */
	template < class Key, class T, class Compare, class Alloc >
		typename map<Key,T,Compare,Alloc>::size_type
				map<Key,T,Compare,Alloc>::_search_and_erase
				( const key_type& key )
		{
			RBnode*			cur_node;
			value_type*		cur_pair;

			cur_node = _tree.get_root();
			while ( cur_node != NIL )
			{
				cur_pair = static_cast<value_type*>( cur_node->get_content() );
				if ( _comp( key, cur_pair->first ) )
					cur_node = cur_node->get_child( LEFT );
				else if ( _comp( cur_pair->first, key ) )
					cur_node = cur_node->get_child( RIGHT );
				else
				{ // found the key
					_tree.remove( cur_node );
					_size--;
					this->_free_one_node( cur_node );
					return ( 1 ); // one node removed
				}
			}

			return ( 0 ); // key not found: no node removed
		}

	/* _free_one_node */
	template < class Key, class T, class Compare, class Alloc >
		void	map<Key,T,Compare,Alloc>::_free_one_node ( RBnode* node )
		{
			value_type*		pair;
			
			pair = static_cast<value_type*>( node->get_content() );
			_alloc.destroy( pair );
			_alloc.deallocate( pair, 1 );
			_alloc_node.destroy( node );
			_alloc_node.deallocate( node, 1 );
		}

	/* _clear_deeper */
	template < class Key, class T, class Compare, class Alloc >
		void	map<Key,T,Compare,Alloc>::_clear_deeper ( RBnode* node )
		{
			RBnode*		child;

			child = node->get_child( LEFT );
			if ( child != NIL ) // if left child exists, free it first
				this->_clear_deeper( child );

			child = node->get_child( RIGHT );
			if ( child != NIL ) // if right child exists, free it first
				this->_clear_deeper( child );

			this->_free_one_node( node );
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
