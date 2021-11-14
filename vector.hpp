/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:39:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/14 17:41:29 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <memory> // allocator
#include <cstddef> // NULL
#include <stdexcept>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"

namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
	class	vector
	{
		public:

			typedef	T											value_type;
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef	v_iterator<std::random_access_iterator_tag, T>
				iterator;
			typedef	v_iterator<std::random_access_iterator_tag, const T>
				const_iterator;
			typedef	reverse_iterator<iterator>			reverse_iterator;
			//typedef	reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef	ptrdiff_t							difference_type;
			typedef	size_t								size_type;

		private:

			allocator_type		_alloc;
			char				__pad[7];
			size_type			_capacity;
			size_type			_size;
			value_type*			_vec;

		public:

			/******* CANONICAL FORM *******************************************/
			explicit vector ( const allocator_type& alloc = allocator_type() );
			explicit vector ( size_type count,
					const value_type& value = value_type(),
					const allocator_type& alloc = allocator_type() );
			vector ( const vector& src );
			~vector ( void );
			vector&		operator= ( const vector &rhs );

			/******* ITERATORS ************************************************/
			iterator				begin ( void );
			const_iterator			begin ( void ) const;
			iterator				end ( void );
			const_iterator			end ( void ) const;
			reverse_iterator		rbegin( void );
			//const_reverse_iterator	rbegin( void ) const;
			reverse_iterator		rend( void );
			//const_reverse_iterator	rend( void ) const;

			/******* CAPACITY *************************************************/
			size_type	size ( void ) const;
			size_type	max_size( void ) const;
			void		resize( size_type count,
					value_type value = value_type() );
			size_type	capacity ( void ) const;
			bool		empty( void ) const;
			void		reserve( size_type new_cap );

			/******* ELEMENT ACCESS *******************************************/
			reference		operator[] ( size_type pos );
			const_reference	operator[] ( size_type pos ) const;
			reference		at ( size_type pos );
			const_reference	at ( size_type pos ) const;
			reference 		front( void );
			const_reference	front( void ) const;
			reference 		back( void );
			const_reference	back( void ) const;

			/******* MODIFIERS ************************************************/
			void		assign ( size_type count, const value_type& value );
			void		push_back ( const value_type& value );
			void		pop_back ( void );
			iterator	erase ( iterator pos );
			//iterator	erase ( iterator first, iterator last );
			void		swap ( vector& other );
			void		clear ( void );

			/******* ALLOCATOR ************************************************/
			allocator_type	get_allocator( void ) const;

	};
}

//#include "vector.templatedef.hpp"

#endif // __VECTOR_HPP__
