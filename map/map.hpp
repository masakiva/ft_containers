/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:17:16 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/26 16:31:43 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
# define __MAP_HPP__

#include <memory> // allocator
#include <cstddef> // NULL
#include <stdexcept>
#include <iostream>
#include "pair.hpp"
#include "RBtree.class.hpp"

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
			//typedef												value_compare;
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			//typedef	m_iterator<T>						iterator;
			//typedef	m_iterator<T, true>					const_iterator;
			//typedef	reverse_iterator<iterator>			reverse_iterator;
			//typedef	ft::reverse_iterator<const_iterator>
				//const_reverse_iterator;
			typedef	ptrdiff_t							difference_type;
			typedef	size_t								size_type;

		private:

			allocator_type	_alloc;
			//char			__pad[7];
			size_type		_size;
			key_compare		_comp;
			RBtree			_tree;

			typedef typename allocator_type::template rebind<RBnode>::other
				_allocator_type_rbnode;
			_allocator_type_rbnode	_alloc_node;

		public:

			/******* CANONICAL FORM *******************************************/
			explicit map ( const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type() );
			template < class InputIt >
				map ( InputIt first, InputIt last,
						const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type() );
			map ( const map& src );
			map&		operator= ( const map &rhs );
//
//			/******* ITERATORS ************************************************/
//			iterator				begin ( void );
//			const_iterator			begin ( void ) const;
//			iterator				end ( void );
//			const_iterator			end ( void ) const;
//			reverse_iterator		rbegin ( void );
//			const_reverse_iterator	rbegin ( void ) const;
//			reverse_iterator		rend ( void );
//			const_reverse_iterator	rend ( void ) const;
//
//			/******* CAPACITY *************************************************/
//			size_type	size ( void ) const;
//			size_type	max_size ( void ) const;
//			void		resize ( size_type count,
//					value_type val = value_type() );
//			size_type	capacity ( void ) const;
//			bool		empty ( void ) const;
//			void		reserve ( size_type new_cap );
//
//			/******* ELEMENT ACCESS *******************************************/
//			reference		operator[] ( size_type pos );
//			const_reference	operator[] ( size_type pos ) const;
//			reference		at ( size_type pos );
//			const_reference	at ( size_type pos ) const;
//			reference 		front ( void );
//			const_reference	front ( void ) const;
//			reference 		back ( void );
//			const_reference	back ( void ) const;
//
//			/******* MODIFIERS ************************************************/
			void	insert ( const value_type& val );
//			template < class InputIt >
//				void		assign ( typename enable_if<
//								!is_integral<InputIt>::value, InputIt
//							>::type first, InputIt last );
//			void		assign ( size_type count, const value_type& val );
//			void		push_back ( const value_type& val );
//			void		pop_back ( void );
//			iterator	insert ( iterator pos, const value_type& val );
//			void		insert ( iterator pos, size_type count,
//					const value_type& val );
//			template < class InputIt >
//    			void		insert (iterator pos, typename enable_if<
//								!is_integral<InputIt>::value, InputIt
//							>::type first, InputIt last);
//			iterator	erase ( iterator pos );
//			iterator	erase ( iterator first, iterator last );
//			void		swap ( map& other );
//			void		clear ( void );

			/******* OPERATIONS ***********************************************/
			//iterator		find ( const key_type& key );
			//const_iterator	find ( const key_type& key ) const;

			/******* ALLOCATOR ************************************************/
			allocator_type	get_allocator ( void ) const;

	}; // class map

} // namespace ft

#include "map.templatedef.hpp"

#endif // __MAP_HPP__
