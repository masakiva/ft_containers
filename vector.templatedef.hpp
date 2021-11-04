/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.templatedef.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:45:40 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/04 17:31:37 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_TEMPLATEDEF_HPP__
# define __VECTOR_TEMPLATEDEF_HPP__

#include "vector.hpp"

namespace	ft
{

	/************************ CONSTRUCTORS AND DESTRUCTOR *************************/

	template < typename T >
		vector<T>::vector( void ) :
			_begin(NULL),
			_end(NULL)
	{ }

	template < typename T >
	explicit vector (const allocator_type& alloc = allocator_type())
	{
		alloc.allocate();
	}

	template < typename T >
		vector<T>::vector( const vector<T>& src ) :
			_begin(NULL),
			_end(NULL)
	{ *this = src; }

	template < typename T >
		vector<T>::~vector( void ) { }


	/**************************** OPERATORS OVERLOADS *****************************/

	template < typename T >
		vector<T>&		vector<T>::operator=( const vector<T>& rhs )
		{
			if ( this == &rhs )
				return ( *this );

			this->_begin = rhs._begin;
			this->_end = rhs._end;

			return ( *this );
		}

	template < typename T >
		typename vector<T>::iterator	vector<T>::begin( void )
		{
			vector<T>::iterator	it( this->_begin );

			return ( it );
		}

	template < typename T >
		typename vector<T>::iterator	vector<T>::end( void )
		{
			vector<T>::iterator	ite( this->_end );

			return ( ite );
		}


	/******************************************************************************/
	/********************************** ITERATOR **********************************/
	/******************************************************************************/

	/************************ CONSTRUCTORS AND DESTRUCTOR *************************/

	template < typename T >
		vector<T>::iterator::iterator( void ) :
			_ptr(NULL)
	{ }

	template < typename T >
		vector<T>::iterator::iterator( T* ptr ) :
			_ptr(ptr)
	{ }

	template < typename T >
		vector<T>::iterator::iterator( const vector<T>::iterator& src )
		{ *this = src; }

	template < typename T >
		vector<T>::iterator::~iterator( void ) { }

	/**************************** OPERATORS OVERLOADS *****************************/

	template < typename T >
		typename vector<T>::iterator&	vector<T>::iterator::operator=(
				const vector<T>::iterator& rhs )
		{
			if ( this == &rhs )
				return ( *this );

			this->_ptr = rhs._ptr;

			return ( *this );
		}

	template < typename T >
		T&		vector<T>::iterator::operator*( void ) const
		{
			return ( *this->_ptr );
		}

	template < typename T >
		bool		vector<T>::iterator::operator>(
				const vector<T>::iterator &rhs ) const
		{
			return ( this->_ptr > rhs._ptr );
		}

	template < typename T >
		bool		vector<T>::iterator::operator<(
				const vector<T>::iterator &rhs ) const
		{
			return ( this->_ptr < rhs._ptr );
		}

	template < typename T >
		bool		vector<T>::iterator::operator>=(
				const vector<T>::iterator &rhs ) const
		{
			return ( this->_ptr >= rhs._ptr );
		}

	template < typename T >
		bool		vector<T>::iterator::operator<=(
				const vector<T>::iterator &rhs ) const
		{
			return ( this->_ptr <= rhs._ptr );
		}

	template < typename T >
		bool		vector<T>::iterator::operator==(
				const vector<T>::iterator &rhs ) const
		{
			return ( this->_ptr == rhs._ptr );
		}

	template < typename T >
		bool		vector<T>::iterator::operator!=(
				const vector<T>::iterator &rhs ) const
		{
			return ( this->_ptr != rhs._ptr );
		}

	template < typename T >
		typename vector<T>::iterator&	vector<T>::iterator::operator++( void )
		{
			this->_ptr++;

			return ( *this );
		}

	template < typename T >
		typename vector<T>::iterator&	vector<T>::iterator::operator--( void )
		{
			this->_ptr--;

			return ( *this );
		}

	template < typename T >
		typename vector<T>::iterator	vector<T>::iterator::operator++( int )
		{
			iterator	before_inc( *this );

			this->_ptr++;

			return ( before_inc );
		}

	template < typename T >
		typename vector<T>::iterator	vector<T>::iterator::operator--( int )
		{
			iterator	before_dec( *this );

			this->_ptr--;

			return ( before_dec );
		}

}

#endif // __VECTOR_TEMPLATEDEF_HPP__
