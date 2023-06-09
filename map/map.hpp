/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:17:16 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/11 14:22:19 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
# define __MAP_HPP__

#include <memory> // allocator
#include <cstddef> // NULL
#include <stdexcept>
#include "map_iterator.template.hpp"
#include "reverse_iterator.template.hpp"
#include "pair.template.hpp"
#include "RBtree.class.hpp"
#include "equal.template.hpp"
#include "lexicographical_compare.template.hpp"

namespace	ft
{

	template <	class Key,
			 	class T,
				class Compare = std::less<Key>,
				class Alloc = std::allocator< pair<const Key, T> > >
	class	map
	{
		/*
		** display order of typedefs and functions taken from
		** https://cplusplus.com/reference/map/map/
		*/
		public:

			typedef	Key											key_type;
			typedef	T											mapped_type;
			typedef	pair<const key_type, mapped_type>			value_type;
			typedef	Compare										key_compare;
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef	m_iterator<value_type>						iterator;
			typedef	m_iterator<value_type, true>			const_iterator;
			typedef	ft::reverse_iterator<iterator>			reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>
				const_reverse_iterator;
			typedef	ptrdiff_t							difference_type;
			typedef	size_t								size_type;

			class	value_compare :
				public std::binary_function<value_type,value_type,bool>
			{
				public:
					typedef	bool		result_type;
					typedef	value_type	first_argument_type;
					typedef	value_type	second_argument_type;
				private:
					key_compare		_comp;
				public:
					value_compare ( key_compare comp ) : _comp( comp ) { }
					bool	operator() ( const value_type& x,
							const value_type& y ) const
					{ return _comp( x.first, y.first ); }
			};

		private:

			size_type		_size;
			RBtree			_tree;
			key_compare		_comp;
			allocator_type	_alloc;

			typedef typename allocator_type::template rebind<RBnode>::other
				_allocator_type_rbnode;
			_allocator_type_rbnode	_alloc_node;

			/******* HELPER FUNCTIONS *****************************************/
			pair<iterator,bool>		_search_and_insert ( RBnode* new_node,
					value_type* new_pair );
			iterator				_insert_with_iterator ( iterator pos,
					RBnode* new_node, value_type* new_pair );
			size_type				_search_and_erase ( const key_type& key );
			void	_free_one_node ( RBnode* node );
			void	_clear_deeper ( RBnode* node );

		public:

			/******* CANONICAL FORM *******************************************/
			explicit map ( const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type() );
			template < class InputIt >
				map ( InputIt first, InputIt last,
						const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type() );
			map ( const map& src );
			~map ( void );
			map&		operator= ( const map &rhs );

			/******* ITERATORS ************************************************/
			iterator				begin ( void );
			const_iterator			begin ( void ) const;
			iterator				end ( void );
			const_iterator			end ( void ) const;
			reverse_iterator		rbegin ( void );
			const_reverse_iterator	rbegin ( void ) const;
			reverse_iterator		rend ( void );
			const_reverse_iterator	rend ( void ) const;

			/******* CAPACITY *************************************************/
			bool		empty ( void ) const;
			size_type	size ( void ) const;
			size_type	max_size ( void ) const;

			/******* ELEMENT ACCESS *******************************************/
			mapped_type&		operator[] ( const key_type& key );
			mapped_type&		at ( const key_type& key );
			const mapped_type&	at ( const key_type& key ) const;

			/******* MODIFIERS ************************************************/
			pair<iterator,bool>
						insert ( const value_type& val );
			iterator	insert ( iterator pos, const value_type& val );
			template < class InputIt >
    			void	insert ( InputIt first, InputIt last);
			void		erase ( iterator pos );
			size_type	erase ( const key_type& key );
			void		erase ( iterator first, iterator last );
			void		swap ( map& other );
			void		clear ( void );

			/******* OBSERVERS ************************************************/
			key_compare		key_comp( void ) const;
			value_compare	value_comp( void ) const;

			/******* OPERATIONS ***********************************************/
			iterator		find ( const key_type& key );
			const_iterator	find ( const key_type& key ) const;
			size_type		count ( const key_type& key ) const;
			iterator		lower_bound ( const key_type& key );
			const_iterator	lower_bound ( const key_type& key ) const;
			iterator		upper_bound ( const key_type& key );
			const_iterator	upper_bound ( const key_type& key ) const;
			pair<iterator,iterator>				equal_range
				( const key_type& key );
			pair<const_iterator,const_iterator>	equal_range
				( const key_type& key ) const;

			/******* ALLOCATOR ************************************************/
			allocator_type	get_allocator ( void ) const;

	}; // class map

	/******* NON-MEMBER FUNCTIONS *********************************************/

	template < class Key, class T, class Compare, class Alloc >
		bool	operator== ( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs );

	template < class Key, class T, class Compare, class Alloc >
		bool	operator!= ( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs );

	template < class Key, class T, class Compare, class Alloc >
		bool	operator<  ( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs );

	template < class Key, class T, class Compare, class Alloc >
		bool	operator<= ( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs );

	template < class Key, class T, class Compare, class Alloc >
		bool	operator>  ( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs );

	template < class Key, class T, class Compare, class Alloc >
		bool	operator>= ( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs );

	template < class Key, class T, class Compare, class Alloc >
		void	swap ( map<Key,T,Compare,Alloc>& lhs,
				map<Key,T,Compare,Alloc>& rhs );

} // namespace ft

#include "map.templatedef.hpp"

#endif // __MAP_HPP__
