/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:39:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/11 19:36:04 by mvidal-a         ###   ########.fr       */
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
			explicit vector ( size_type n, const value_type& val = value_type(),
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
			void		resize( size_type n, value_type val = value_type() );
			size_type	capacity ( void ) const;
			bool		empty( void ) const;
			void		reserve( size_type n );

			/******* ELEMENT ACCESS *******************************************/
			reference		operator[] ( size_type n );
			const_reference	operator[] ( size_type n ) const;
			reference		at ( size_type n );
			const_reference	at ( size_type n ) const;
			reference 		front( void );
			const_reference	front( void ) const;
			reference 		back( void );
			const_reference	back( void ) const;

			/******* MODIFIERS ************************************************/
			void	assign ( size_type n, const value_type& val );
			void	push_back ( const value_type& val );
			void	pop_back ( void );
			void	swap ( vector& x );
			void	clear ( void );

	};
}

//#include "vector.templatedef.hpp"

#endif // __VECTOR_HPP__
