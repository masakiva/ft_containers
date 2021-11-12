/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.templatedef.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:45:40 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/12 14:06:10 by mvidal-a         ###   ########.fr       */
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
			_capacity(0),
			_size(0)
		{
			_vec = _alloc.allocate( _capacity );
		}

	/* fill constructor */
	template < class T, class Alloc >
		vector<T, Alloc>::vector ( size_type count, const value_type& value,
				const allocator_type& alloc ) :
			_alloc(alloc),
			_capacity(count),
			_size(count)
		{
			_vec = _alloc.allocate( _capacity );
			for ( size_type i = 0; i < _size; i++ )
				_alloc.construct( _vec + i, value );
		}

	/* copy constructor */
	template < class T, class Alloc >
		vector<T, Alloc>::vector ( const vector<T, Alloc>& src ) :
			_alloc(src._alloc),
			_capacity(0),
			_size(0)
		{
			*this = src;
		}

	/* destructor */
	template < class T, class Alloc >
		vector<T, Alloc>::~vector ( void )
		{
			for ( size_type i = 0; i < _size; i++ )
				_alloc.destroy( _vec + i );
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
		void	vector<T, Alloc>::resize ( size_type count, value_type value )
		{
			this->reserve( count );
			if ( count > _size )
			{
				for ( size_type i = _size; i < count; i++ )
					_alloc.construct( _vec + i, value );
			}
			else if ( count < _size )
			{
				for ( size_type i = count; i < _size; i++ )
					_alloc.destroy( _vec + i );
			}
			_size = count;
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
		void	vector<T, Alloc>::reserve ( size_type new_cap )
		{
			if ( new_cap > _capacity )
			{
				value_type*	new_vec;

				new_vec = _alloc.allocate( new_cap );
				for ( size_type i = 0; i < _size; i++ )
					_alloc.construct( new_vec + i, _vec[i] );

				for ( size_type i = 0; i < _size; i++ )
					_alloc.destroy( _vec + i );
				_alloc.deallocate( _vec, _capacity );
				_vec = new_vec;
				_capacity = new_cap;
			}
		}

	/******* ELEMENT ACCESS ***************************************************/

	/* [] */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::operator[] ( size_type pos )
		{
			return ( _vec[pos] );
		}

	/* [] (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::operator[] ( size_type pos ) const
		{
			return ( _vec[pos] );
		}

	/* at */
	template < class T, class Alloc >
		typename vector<T, Alloc>::reference
				vector<T, Alloc>::at ( size_type pos )
		{
			if ( pos >= _size )
				throw std::out_of_range( "at() argument out of vector range" );
			return ( _vec[pos] );
		}

	/* at (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::at ( size_type pos ) const
		{
			if ( pos >= _size )
				throw std::out_of_range( "at() argument out of vector range" );
			return ( _vec[pos] );
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
			return ( _vec[_size - 1] );
		}

	/* back (const) */
	template < class T, class Alloc >
		typename vector<T, Alloc>::const_reference
				vector<T, Alloc>::back ( void ) const
		{
			return ( _vec[_size - 1] );
		}


	/******* MODIFIERS ********************************************************/

	/* assign */
	template < class T, class Alloc >
		void	vector<T, Alloc>::assign ( size_type count,
				const value_type& value )
		{
			if ( count > _capacity )
			{
				for ( size_type i = 0; i < _size; i++ )
					_alloc.destroy( _vec + i );
				_alloc.deallocate( _vec, _capacity );

				_vec = _alloc.allocate( count );
				_capacity = count;
				for ( size_type i = 0; i < count; i++ )
					_alloc.construct( _vec + i, value );
			}
			else if ( count >= _size )
			{
				for ( size_type i = 0; i < _size; i++ )
					_vec[i] = value;
				for ( size_type i = _size; i < count; i++ )
					_alloc.construct( _vec + i, value );
			}
			else
			{
				for ( size_type i = 0; i < count; i++ )
					_vec[i] = value;
				for ( size_type i = count; i < _size; i++ )
					_alloc.destroy( _vec + i );
			}
			_size = count;
		}

	/* push_back */
	template < class T, class Alloc >
		void	vector<T, Alloc>::push_back ( const value_type& value )
		{
			this->reserve( _size + 1 );
			_alloc.construct( _vec + _size, value );
			_size++;
		}

	/* pop_back */
	template < class T, class Alloc >
		void	vector<T, Alloc>::pop_back ( void )
		{
			_alloc.destroy( _vec + _size - 1 );
			_size--;
		}

	/* swap */
	template < class T, class Alloc >
		void	vector<T, Alloc>::swap ( vector<T, Alloc>& other )
		{
			size_type		temp_capacity;
			size_type		temp_size;
			value_type*		temp_vec;

			temp_capacity = other._capacity;
			other._capacity = _capacity;
			_capacity = temp_capacity;

			temp_size = other._size;
			other._size = _size;
			_size = temp_size;

			temp_vec = other._vec;
			other._vec = _vec;
			_vec = temp_vec;
		}

	/* clear */
	template < class T, class Alloc >
		void	vector<T, Alloc>::clear ( void )
		{
			for ( size_type i = 0; i < _size; i++ )
				_alloc.destroy( _vec + i );
			_size = 0;
		}


	/******* ALLOCATOR ********************************************************/

	/* get_allocator */
	template < class T, class Alloc >
		typename vector<T, Alloc>::allocator_type
				vector<T, Alloc>::get_allocator( void ) const
		{
			return ( _alloc );
		}


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