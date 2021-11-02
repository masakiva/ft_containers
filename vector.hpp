/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:39:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/02 19:58:27 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <memory> // allocator

namespace	ft
{
	template < typename T >
	class	vector
	{
		private:

			T*		_begin;
			T*		_end;

		public:

			vector( void );
			vector( const vector& src );
			~vector( void );

			vector&		operator=( const vector &rhs );

			class	iterator
			{
				private:

					T*		_ptr;

				public:

					iterator( void );
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
			}

			iterator	begin( void );
			iterator	end( void );
	};
}

#include "vector.templatedef.hpp"

#endif // __VECTOR_HPP__
