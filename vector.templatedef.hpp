/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.templatedef.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:45:40 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/09 19:52:31 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_TEMPLATEDEF_HPP__
# define __VECTOR_TEMPLATEDEF_HPP__

#include "vector.hpp"

namespace	ft
{

	/******* CANONICAL FORM ***************************************************/

	/* default constructor */
	template < class T, class Alloc >
		vector<T, Alloc>::vector ( const allocator_type& alloc ) :
			_alloc(alloc),
			_size(0)
		{ }

	/* fill constructor */
	template < class T, class Alloc >
		vector<T, Alloc>::vector ( size_type n, const value_type& val, const
				allocator_type& alloc ) :
			_alloc(alloc),
			_size(n)
		{
			this->_vec = this->_alloc.allocate( n );
			for ( size_type i = 0; i < n; i++ )
				this->_alloc.construct( this->_vec + i, val );
		}

	/* copy constructor */
	template < class T, class Alloc >
		vector<T, Alloc>::vector ( const vector<T, Alloc>& src ) :
			_alloc(src._alloc),
			_size(0)
		{
			*this = src;
		}

	/* destructor */
	template < class T, class Alloc >
		vector<T, Alloc>::~vector ( void )
		{
			for ( size_type i = 0; i < this->_size; i++ )
				this->_alloc.destroy( this->_vec + i );
			if ( this->_size != 0 )
				this->_alloc.deallocate( this->_vec, this->_size );
		}

	/* = */
	template < class T, class Alloc >
		vector<T, Alloc>&
				vector<T, Alloc>::operator= ( const vector<T, Alloc>& rhs )
		{
			if ( this == &rhs )
				return ( *this );

			for ( size_type i = 0; i < this->_size; i++ )
				this->_alloc.destroy( this->_vec + i );
			if ( this->_size != 0 )
				this->_alloc.deallocate( this->_vec, this->_size );

			this->_size = rhs._size;
			this->_capacity = rhs._capacity;

			this->_vec = this->_alloc.allocate( this->_size );
			for ( size_type i = 0; i < this->_size; i++ )
				this->_alloc.construct( this->_vec + i, rhs._vec[i] );

			return ( *this );
		}


	/******* CAPACITY *********************************************************/

	/* size */
	template < class T, class Alloc >
		typename vector<T, Alloc>::size_type
				vector<T, Alloc>::size( void ) const
		{
			return ( this->_size );
		}

	/* capacity */
	template < class T, class Alloc >
		typename vector<T, Alloc>::size_type
				vector<T, Alloc>::capacity( void ) const
		{
			return ( this->_capacity );
		}

	/******* ELEMENT ACCESS ***************************************************/

	/* [] */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::operator[] ( size_type n )
		{
			return ( this->_vec[n] );
		}

	/* [] (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::operator[] ( size_type n ) const
		{
			return ( this->_vec[n] );
		}

	/* at */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::at ( size_type n )
		{
			if ( n >= this->_size )
				throw std::out_of_range( "at() argument out of vector range" );
			return ( this->_vec[n] );
		}

	/* at (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::at ( size_type n ) const
		{
			if ( n >= this->_size )
				throw std::out_of_range( "at() argument out of vector range" );
			return ( this->_vec[n] );
		}

	/* front */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::front ( void )
		{
			return ( this->_vec[0] );
		}

	/* front (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::front ( void ) const
		{
			return ( this->_vec[0] );
		}

	/* back */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::back ( void )
		{
			return ( this->_vec[this->_size] );
		}

	/* back (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::back ( void ) const
		{
			return ( this->_vec[this->_size] );
		}


	/******* MODIFIERS ********************************************************/

//	template < class T, class Alloc >
//	void	vector<T, Alloc>::assign ( size_type n, const value_type& val )
//	{
//		if ( n > this->_capacity )
//	}


	/******* ITERATORS ********************************************************/

	/* begin */
	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator
				vector<T, Alloc>::begin ( void )
		{
			vector<T, Alloc>::iterator	it( this->_vec );

			return ( it );
		}

//	/* begin (const) */
//	template < class T, class Alloc >
//		typename vector<T, Alloc>::const_iterator
//				vector<T, Alloc>::begin ( void ) const
//		{
//			vector<T, Alloc>::iterator	it( this->_vec );
//
//			return ( it );
//		}

	/* end */
	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator
				vector<T, Alloc>::end ( void )
		{
			vector<T, Alloc>::iterator	ite( this->_vec + this->_size );

			return ( ite );
		}

//	/* end (const) */
//	template < class T, class Alloc >
//		typename vector<T, Alloc>::const_iterator
//				vector<T, Alloc>::end ( void ) const
//		{
//			vector<T, Alloc>::iterator	ite( this->_vec + this->_size );
//
//			return ( ite );
//		}


	/**************************************************************************/
	/******************************** ITERATOR ********************************/
	/**************************************************************************/

	/********************** CONSTRUCTORS AND DESTRUCTOR ***********************/

	template < class T, class Alloc >
		vector<T, Alloc>::iterator::iterator ( void ) :
			_ptr(NULL)
	{ }

	template < class T, class Alloc >
		vector<T, Alloc>::iterator::iterator ( T* ptr ) :
			_ptr(ptr)
	{ }

	template < class T, class Alloc >
		vector<T, Alloc>::iterator::iterator
				( const vector<T, Alloc>::iterator& src )
		{ *this = src; }

	template < class T, class Alloc >
		vector<T, Alloc>::iterator::~iterator ( void ) { }

	/************************** OPERATORS OVERLOADS ***************************/

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator&
				vector<T, Alloc>::iterator::operator=
				( const vector<T, Alloc>::iterator& rhs )
		{
			if ( this == &rhs )
				return ( *this );

			this->_ptr = rhs._ptr;

			return ( *this );
		}

	template < class T, class Alloc >
		T&		vector<T, Alloc>::iterator::operator* ( void ) const
		{
			return ( *this->_ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator>
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr > rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator<
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr < rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator>=
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr >= rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator<=
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr <= rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator==
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr == rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator!=
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( this->_ptr != rhs._ptr );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator&
				vector<T, Alloc>::iterator::operator++ ( void )
		{
			this->_ptr++;

			return ( *this );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator&
				vector<T, Alloc>::iterator::operator-- ( void )
		{
			this->_ptr--;

			return ( *this );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator
				vector<T, Alloc>::iterator::operator++ ( int )
		{
			iterator	before_inc( *this );

			this->_ptr++;

			return ( before_inc );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator
				vector<T, Alloc>::iterator::operator-- ( int )
		{
			iterator	before_dec( *this );

			this->_ptr--;

			return ( before_dec );
		}

}

#endif // __VECTOR_TEMPLATEDEF_HPP__
