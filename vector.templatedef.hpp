/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.templatedef.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:45:40 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/05 14:53:11 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_TEMPLATEDEF_HPP__
# define __VECTOR_TEMPLATEDEF_HPP__

#include "vector.hpp"

namespace	ft
{

	/************************ CONSTRUCTORS AND DESTRUCTOR *************************/

	template < class T, class Alloc >
		vector<T, Alloc>::vector ( const allocator_type& alloc ) :
			_alloc(alloc),
			_begin(NULL),
			_end(NULL)
		{
			this->_vec = this->_alloc.allocate( 0 );
		}

	template < class T, class Alloc >
		vector<T, Alloc>::vector ( size_type n, const value_type& val, const
				allocator_type& alloc ) :
			_alloc(alloc),
			_begin(NULL),
			_end(NULL)
		{
			this->_vec = this->_alloc.allocate( n );
			for ( size_type i = 0; i < n; i++ )
				this->_alloc.construct( this->_vec + i, val );
		}

	template < class T, class Alloc >
		vector<T, Alloc>::vector( const vector<T, Alloc>& src )
		{
			*this = src;
		}

	template < class T, class Alloc >
		vector<T, Alloc>::~vector( void ) { }


	/**************************** OPERATORS OVERLOADS *****************************/

	template < class T, class Alloc >
		vector<T, Alloc>&		vector<T, Alloc>::operator=( const vector<T, Alloc>& rhs )
		{
			if ( this == &rhs )
				return ( *this );

			this->_alloc = rhs._alloc;
			this->_size = rhs._size;
			this->_capacity = rhs._capacity;
			this->_begin = rhs._begin;
			this->_end = rhs._end;

			return ( *this );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator	vector<T, Alloc>::begin( void )
		{
			vector<T, Alloc>::iterator	it( this->_begin );

			return ( it );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator	vector<T, Alloc>::end( void )
		{
			vector<T, Alloc>::iterator	ite( this->_end );

			return ( ite );
		}


	/******************************************************************************/
	/********************************** ITERATOR **********************************/
	/******************************************************************************/

	/************************ CONSTRUCTORS AND DESTRUCTOR *************************/

	template < class T, class Alloc >
		vector<T, Alloc>::iterator::iterator( void ) :
			_ptr(NULL)
	{ }

	template < class T, class Alloc >
		vector<T, Alloc>::iterator::iterator( T* ptr ) :
			_ptr(ptr)
	{ }

	template < class T, class Alloc >
		vector<T, Alloc>::iterator::iterator( const vector<T, Alloc>::iterator& src )
		{ *this = src; }

	template < class T, class Alloc >
		vector<T, Alloc>::iterator::~iterator( void ) { }

	/**************************** OPERATORS OVERLOADS *****************************/

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator&	vector<T, Alloc>::iterator::operator=(
				const vector<T, Alloc>::iterator& rhs )
		{
			if ( this == &rhs )
				return ( *this );

			this->_ptr = rhs._ptr;

			return ( *this );
		}

	template < class T, class Alloc >
		T&		vector<T, Alloc>::iterator::operator*( void ) const
		{
			return ( *this->_ptr );
		}

	template < class T, class Alloc >
		bool		vector<T, Alloc>::iterator::operator>(
				const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr > rhs._ptr );
		}

	template < class T, class Alloc >
		bool		vector<T, Alloc>::iterator::operator<(
				const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr < rhs._ptr );
		}

	template < class T, class Alloc >
		bool		vector<T, Alloc>::iterator::operator>=(
				const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr >= rhs._ptr );
		}

	template < class T, class Alloc >
		bool		vector<T, Alloc>::iterator::operator<=(
				const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr <= rhs._ptr );
		}

	template < class T, class Alloc >
		bool		vector<T, Alloc>::iterator::operator==(
				const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr == rhs._ptr );
		}

	template < class T, class Alloc >
		bool		vector<T, Alloc>::iterator::operator!=(
				const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr != rhs._ptr );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator&	vector<T, Alloc>::iterator::operator++( void )
		{
			this->_ptr++;

			return ( *this );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator&	vector<T, Alloc>::iterator::operator--( void )
		{
			this->_ptr--;

			return ( *this );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator	vector<T, Alloc>::iterator::operator++( int )
		{
			iterator	before_inc( *this );

			this->_ptr++;

			return ( before_inc );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator	vector<T, Alloc>::iterator::operator--( int )
		{
			iterator	before_dec( *this );

			this->_ptr--;

			return ( before_dec );
		}

}

#endif // __VECTOR_TEMPLATEDEF_HPP__
