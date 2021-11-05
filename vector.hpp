/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:39:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/05 14:52:54 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <memory> // allocator
#include <cstddef> // NULL

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

			value_type*			_vec;
			allocator_type		_alloc;
			size_type			_size;
			size_type			_capacity;
			T*					_begin; //
			T*					_end; //

		public:

			explicit vector ( const allocator_type& alloc = allocator_type() );
			explicit vector ( size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type() );
			vector( const vector& src );
			~vector( void );

			vector&		operator=( const vector &rhs );

			class	iterator
			{
				private:

					T*		_ptr;

				public:

					iterator( void );
					iterator( T* ptr );
					iterator( const iterator& src );
					~iterator( void );

					iterator&		operator=( const iterator &rhs );

					T&			operator*( void ) const;

					bool		operator>( const iterator &rhs ) const;
					bool		operator<( const iterator &rhs ) const;
					bool		operator>=( const iterator &rhs ) const;
					bool		operator<=( const iterator &rhs ) const;
					bool		operator==( const iterator &rhs ) const;
					bool		operator!=( const iterator &rhs ) const;

					iterator&	operator++( void );
					iterator&	operator--( void );
					iterator	operator++( int );
					iterator	operator--( int );
			};

			iterator	begin( void );
			iterator	end( void );
	};
}

#include "vector.templatedef.hpp"

#endif // __VECTOR_HPP__
