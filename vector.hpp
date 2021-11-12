/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:39:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/12 14:04:21 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <memory> // allocator
#include <cstddef> // NULL
#include <stdexcept>

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
			typedef	ptrdiff_t									difference_type;
			typedef	size_t										size_type;

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
			class	iterator
			{
				private:

					T*		_ptr;

				public:

					iterator ( void );
					iterator ( T* ptr );
					iterator ( const iterator& src );
					~iterator ( void );
					iterator&	operator= ( const iterator &rhs );

					T&		operator* ( void ) const;

					bool	operator> ( const iterator &rhs ) const;
					bool	operator< ( const iterator &rhs ) const;
					bool	operator>= ( const iterator &rhs ) const;
					bool	operator<= ( const iterator &rhs ) const;
					bool	operator== ( const iterator &rhs ) const;
					bool	operator!= ( const iterator &rhs ) const;

					iterator&	operator++ ( void );
					iterator&	operator-- ( void );
					iterator	operator++ ( int );
					iterator	operator-- ( int );
			};
			iterator		begin ( void );
			//const_iterator	begin ( void ) const;
			iterator		end ( void );
			//const_iterator	end ( void ) const;

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
			void	assign ( size_type count, const value_type& value );
			void	push_back ( const value_type& value );
			void	pop_back ( void );
			void	swap ( vector& other );
			void	clear ( void );

			/******* ALLOCATOR ************************************************/
			allocator_type	get_allocator( void ) const;

	};
}

//#include "vector.templatedef.hpp"

#endif // __VECTOR_HPP__
