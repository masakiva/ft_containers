/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.templatedef.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:45:40 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/10 22:47:47 by mvidal-a         ###   ########.fr       */
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
			_size(0),
			_capacity(0)
		{ }

	/* fill constructor */
	template < class T, class Alloc >
		vector<T, Alloc>::vector ( size_type n, const value_type& val, const
				allocator_type& alloc ) :
			_alloc(alloc),
			_size(n),
			_capacity(n)
		{
			_vec = _alloc.allocate( _capacity );
			for ( size_type i = 0; i < _size; i++ )
				_alloc.construct( _vec + i, val );
		}

	/* copy constructor */
	template < class T, class Alloc >
		vector<T, Alloc>::vector ( const vector<T, Alloc>& src ) :
			_alloc(src._alloc),
			_size(0),
			_capacity(0)
		{
			*this = src;
		}

	/* destructor */
	template < class T, class Alloc >
		vector<T, Alloc>::~vector ( void )
		{
			for ( size_type i = 0; i < _size; i++ )
				_alloc.destroy( _vec + i );
			if ( _size != 0 )
				_alloc.deallocate( _vec, _size );
		}

	/* = */
	template < class T, class Alloc >
		vector<T, Alloc>&
				vector<T, Alloc>::operator= ( const vector<T, Alloc>& rhs )
		{
			if ( this == &rhs )
				return ( *this );

			for ( size_type i = 0; i < _size; i++ )
				_alloc.destroy( _vec + i );
			if ( _capacity != 0 )
				_alloc.deallocate( _vec, _capacity );

			_size = rhs._size;
			_capacity = rhs._capacity;

			_vec = _alloc.allocate( _capacity );
			for ( size_type i = 0; i < _size; i++ )
				_alloc.construct( _vec + i, rhs._vec[i] );

			return ( *this );
		}


	/******* CAPACITY *********************************************************/

	/* size */
	template < class T, class Alloc >
		typename vector<T, Alloc>::size_type
				vector<T, Alloc>::size ( void ) const
		{
			return ( _size );
		}

	/* max_size */
	template < class T, class Alloc >
		typename vector<T, Alloc>::size_type
				vector<T, Alloc>::max_size ( void ) const
		{
			return ( _alloc.max_size() );
		}

	/* resize */
	template < class T, class Alloc >
		void	vector<T, Alloc>::resize ( size_type n, value_type val )
		{
			this->reserve( n );
			if ( n > _size )
			{
				for ( size_type i = _size; i < n; i++ )
					_alloc.construct( _vec + i, val );
			}
			else if ( n < _size )
			{
				for ( size_type i = n; i < _size; i++ )
					_alloc.destroy( _vec + i );
			}
			_size = n;
		}

	/* capacity */
	template < class T, class Alloc >
		typename vector<T, Alloc>::size_type
				vector<T, Alloc>::capacity ( void ) const
		{
			return ( _capacity );
		}

	/* empty */
	template < class T, class Alloc >
		bool	vector<T, Alloc>::empty ( void ) const
		{
			return ( _size == 0 );
		}

	/* reserve */
	template < class T, class Alloc >
		void	vector<T, Alloc>::reserve ( size_type n )
		{
			if ( n > _capacity )
			{
				value_type*	new_vec;

				_capacity = n;
				new_vec = _alloc.allocate( _capacity );
				for ( size_type i = 0; i < _size; i++ )
					_alloc.construct( new_vec + i, _vec[i] );

				for ( size_type i = 0; i < _size; i++ )
				_alloc.destroy( _vec + i );
				if ( _capacity != 0 )
					_alloc.deallocate( _vec, _capacity );
				_vec = new_vec;
			}
		}

	/******* ELEMENT ACCESS ***************************************************/

	/* [] */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::operator[] ( size_type n )
		{
			return ( _vec[n] );
		}

	/* [] (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::operator[] ( size_type n ) const
		{
			return ( _vec[n] );
		}

	/* at */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::at ( size_type n )
		{
			if ( n >= _size )
				throw std::out_of_range( "at() argument out of vector range" );
			return ( _vec[n] );
		}

	/* at (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::at ( size_type n ) const
		{
			if ( n >= _size )
				throw std::out_of_range( "at() argument out of vector range" );
			return ( _vec[n] );
		}

	/* front */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::front ( void )
		{
			return ( _vec[0] );
		}

	/* front (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::front ( void ) const
		{
			return ( _vec[0] );
		}

	/* back */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::back ( void )
		{
			return ( _vec[_size] );
		}

	/* back (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::back ( void ) const
		{
			return ( _vec[_size] );
		}


	/******* MODIFIERS ********************************************************/

//	template < class T, class Alloc >
//	void	vector<T, Alloc>::assign ( size_type n, const value_type& val )
//	{
//		if ( n > _capacity )
//	}


	/******* ITERATORS ********************************************************/

	/* begin */
	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator
				vector<T, Alloc>::begin ( void )
		{
			vector<T, Alloc>::iterator	it( _vec );

			return ( it );
		}

//	/* begin (const) */
//	template < class T, class Alloc >
//		typename vector<T, Alloc>::const_iterator
//				vector<T, Alloc>::begin ( void ) const
//		{
//			vector<T, Alloc>::iterator	it( _vec );
//
//			return ( it );
//		}

	/* end */
	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator
				vector<T, Alloc>::end ( void )
		{
			vector<T, Alloc>::iterator	ite( _vec + _size );

			return ( ite );
		}

//	/* end (const) */
//	template < class T, class Alloc >
//		typename vector<T, Alloc>::const_iterator
//				vector<T, Alloc>::end ( void ) const
//		{
//			vector<T, Alloc>::iterator	ite( _vec + _size );
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

			_ptr = rhs._ptr;

			return ( *this );
		}

	template < class T, class Alloc >
		T&		vector<T, Alloc>::iterator::operator* ( void ) const
		{
			return ( *_ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator>
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( _ptr > rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator<
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( _ptr < rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator>=
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( _ptr >= rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator<=
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( _ptr <= rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator==
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( _ptr == rhs._ptr );
		}

	template < class T, class Alloc >
		bool	vector<T, Alloc>::iterator::operator!=
				( const vector<T, Alloc>::iterator &rhs ) const
		{
			return ( _ptr != rhs._ptr );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator&
				vector<T, Alloc>::iterator::operator++ ( void )
		{
			_ptr++;

			return ( *this );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator&
				vector<T, Alloc>::iterator::operator-- ( void )
		{
			_ptr--;

			return ( *this );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator
				vector<T, Alloc>::iterator::operator++ ( int )
		{
			iterator	before_inc( *this );

			_ptr++;

			return ( before_inc );
		}

	template < class T, class Alloc >
		typename vector<T, Alloc>::iterator
				vector<T, Alloc>::iterator::operator-- ( int )
		{
			iterator	before_dec( *this );

			_ptr--;

			return ( before_dec );
		}

}

#endif // __VECTOR_TEMPLATEDEF_HPP__
