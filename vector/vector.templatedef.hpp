/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.templatedef.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:45:40 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/10 16:17:10 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_TEMPLATEDEF_HPP__
# define __VECTOR_TEMPLATEDEF_HPP__

namespace	ft
{

	/******* CANONICAL FORM ***************************************************/

	/* default constructor */
	template < class T, class Alloc >
		vector<T,Alloc>::vector ( const allocator_type& alloc ) :
			_capacity( 0 ),
			_size( 0 ),
			_alloc( alloc )
		{
			_vec = _alloc.allocate( _capacity );
		}

	/* fill constructor */
	template < class T, class Alloc >
		vector<T,Alloc>::vector ( size_type count, const value_type& val,
				const allocator_type& alloc ) :
			_capacity( count ),
			_size( count ),
			_alloc( alloc )
		{
			_vec = _alloc.allocate( _capacity );
			for ( size_type i = 0; i < _size; i++ )
				_alloc.construct( _vec + i, val );
		}

	/* range constructor */
	template < class T, class Alloc >
		template < class InputIt >
			vector<T,Alloc>::vector ( typename enable_if<
						!is_integral<InputIt>::value, InputIt
					>::type first, InputIt last,
					const allocator_type& alloc ) :
				_capacity( 0 ),
				_alloc( alloc )
			{
				for ( InputIt it = first; it != last; it++ )
					_capacity++;
				_vec = _alloc.allocate( _capacity );

				_size = _capacity;
				for ( size_type i = 0; i < _size; i++ )
					_alloc.construct( _vec + i, *first++ );
			}

	/* copy constructor */
	template < class T, class Alloc >
		vector<T,Alloc>::vector ( const vector& src ) :
			_capacity( 0 ),
			_size( 0 ),
			_alloc( src._alloc )
		{
			_vec = _alloc.allocate( _capacity );
			*this = src;
		}

	/* destructor */
	template < class T, class Alloc >
		vector<T,Alloc>::~vector ( void )
		{
			this->clear();
			_alloc.deallocate( _vec, _size );
		}

	/* = */
	template < class T, class Alloc >
		vector<T,Alloc>&
				vector<T,Alloc>::operator= ( const vector& rhs )
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


	/******* ITERATORS ********************************************************/

	/* begin */
	template < class T, class Alloc >
		typename vector<T,Alloc>::iterator
				vector<T,Alloc>::begin ( void )
		{
			iterator	it( _vec );

			return ( it );
		}

	/* begin (const) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::const_iterator
				vector<T,Alloc>::begin ( void ) const
		{
			const_iterator	it( _vec );

			return ( it );
		}

	/* end */
	template < class T, class Alloc >
		typename vector<T,Alloc>::iterator
				vector<T,Alloc>::end ( void )
		{
			iterator	ite( _vec + _size );

			return ( ite );
		}

	/* end (const) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::const_iterator
				vector<T,Alloc>::end ( void ) const
		{
			const_iterator	ite( _vec + _size );

			return ( ite );
		}

	/* rbegin */
	template < class T, class Alloc >
		typename vector<T,Alloc>::reverse_iterator
				vector<T,Alloc>::rbegin ( void )
		{
			iterator			it = this->end();
			reverse_iterator	rev_it( it );

			return ( rev_it );
		}

	/* rbegin (const) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::const_reverse_iterator
				vector<T,Alloc>::rbegin ( void ) const
		{
			const_iterator			it = this->end();
			const_reverse_iterator	rev_it( it );

			return ( rev_it );
		}

	/* rend */
	template < class T, class Alloc >
		typename vector<T,Alloc>::reverse_iterator
				vector<T,Alloc>::rend ( void )
		{
			iterator			it = this->begin();
			reverse_iterator	rev_it( it );

			return ( rev_it );
		}

	/* rend (const) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::const_reverse_iterator
				vector<T,Alloc>::rend ( void ) const
		{
			const_iterator			it = this->begin();
			const_reverse_iterator	rev_it( it );

			return ( rev_it );
		}


	/******* CAPACITY *********************************************************/

	/* size */
	template < class T, class Alloc >
		typename vector<T,Alloc>::size_type
				vector<T,Alloc>::size ( void ) const
		{
			return ( _size );
		}

	/* max_size */
	template < class T, class Alloc >
		typename vector<T,Alloc>::size_type
				vector<T,Alloc>::max_size ( void ) const
		{
			return ( _alloc.max_size() );
		}

	/* resize */
	template < class T, class Alloc >
		void	vector<T,Alloc>::resize ( size_type count, value_type val )
		{
			this->reserve( count );
			if ( count > _size )
			{
				for ( size_type i = _size; i < count; i++ )
					_alloc.construct( _vec + i, val );
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
		typename vector<T,Alloc>::size_type
				vector<T,Alloc>::capacity ( void ) const
		{
			return ( _capacity );
		}

	/* empty */
	template < class T, class Alloc >
		bool	vector<T,Alloc>::empty ( void ) const
		{
			return ( _size == 0 );
		}

	/* reserve */
	template < class T, class Alloc >
		void	vector<T,Alloc>::reserve ( size_type new_cap )
		{
			if ( new_cap > _capacity )
			{
				if ( new_cap > this->max_size() )
					throw std::length_error( "new capacity exceeds max_size" );

				value_type*	new_vec;

				new_vec = _alloc.allocate( new_cap ); // allocate new capacity
				for ( size_type i = 0; i < _size; i++ )
					_alloc.construct( new_vec + i, _vec[i] ); // do the copy

				for ( size_type i = 0; i < _size; i++ )
					_alloc.destroy( _vec + i ); // destroy old array
				_alloc.deallocate( _vec, _capacity );
				_vec = new_vec;
				_capacity = new_cap;
			}
		}


	/******* ELEMENT ACCESS ***************************************************/

	/* [] */
	template < class T, class Alloc >
		typename vector<T,Alloc>::reference
				vector<T,Alloc>::operator[] ( size_type pos )
		{
			return ( _vec[pos] );
		}

	/* [] (const) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::const_reference
				vector<T,Alloc>::operator[] ( size_type pos ) const
		{
			return ( _vec[pos] );
		}

	/* at */
	template < class T, class Alloc >
		typename vector<T,Alloc>::reference
				vector<T,Alloc>::at ( size_type pos )
		{
			if ( pos >= _size )
				throw std::out_of_range( "at() argument out of vector range" );

			return ( _vec[pos] );
		}

	/* at (const) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::const_reference
				vector<T,Alloc>::at ( size_type pos ) const
		{
			if ( pos >= _size )
				throw std::out_of_range( "at() argument out of vector range" );

			return ( _vec[pos] );
		}

	/* front */
	template < class T, class Alloc >
		typename vector<T,Alloc>::reference
				vector<T,Alloc>::front ( void )
		{
			return ( _vec[0] );
		}

	/* front (const) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::const_reference
				vector<T,Alloc>::front ( void ) const
		{
			return ( _vec[0] );
		}

	/* back */
	template < class T, class Alloc >
		typename vector<T,Alloc>::reference
				vector<T,Alloc>::back ( void )
		{
			return ( _vec[_size - 1] );
		}

	/* back (const) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::const_reference
				vector<T,Alloc>::back ( void ) const
		{
			return ( _vec[_size - 1] );
		}


	/******* MODIFIERS ********************************************************/

	/* assign (from a range of iterators) */
	template < class T, class Alloc >
		template < class InputIt >
			void	vector<T,Alloc>::assign ( typename enable_if<
						!is_integral<InputIt>::value, InputIt
					>::type first, InputIt last )
			{
				size_type	new_size = 0;
				for ( InputIt it = first; it != last; it++ )
					new_size++; // compute new size

				if ( new_size > _capacity )
				{ // reallocate and replace all content
					for ( size_type i = 0; i < _size; i++ )
						_alloc.destroy( _vec + i );
					_alloc.deallocate( _vec, _capacity );

					_vec = _alloc.allocate( new_size );
					for ( size_type i = 0; i < new_size; i++ )
						_alloc.construct( _vec + i, *first++ );
					_capacity = new_size;
				}
				else if ( new_size >= _size )
				{
					for ( size_type i = 0; i < _size; i++ )
						_vec[i] = *first++; // overwrite previous content
					for ( size_type i = _size; i < new_size; i++ )
						_alloc.construct( _vec + i, *first++ ); // add the rest
				}
				else
				{
					for ( size_type i = 0; i < new_size; i++ )
						_vec[i] = *first++; // overwrite previous content
					for ( size_type i = new_size; i < _size; i++ )
						_alloc.destroy( _vec + i ); // remove the remainder
				}
				_size = new_size;
			}

	/* assign (fill a single value) */
	template < class T, class Alloc >
		void	vector<T,Alloc>::assign ( size_type count,
				const value_type& val )
		{
			if ( count > _capacity )
			{ // reallocate and replace all content
				for ( size_type i = 0; i < _size; i++ )
					_alloc.destroy( _vec + i );
				_alloc.deallocate( _vec, _capacity );

				_vec = _alloc.allocate( count );
				for ( size_type i = 0; i < count; i++ )
					_alloc.construct( _vec + i, val );
				_capacity = count;
			}
			else if ( count >= _size )
			{
				for ( size_type i = 0; i < _size; i++ )
					_vec[i] = val; // overwrite previous content
				for ( size_type i = _size; i < count; i++ )
					_alloc.construct( _vec + i, val ); // add the rest
			}
			else
			{
				for ( size_type i = 0; i < count; i++ )
					_vec[i] = val; // overwrite previous content
				for ( size_type i = count; i < _size; i++ )
					_alloc.destroy( _vec + i ); // remove the remainder
			}
			_size = count;
		}

	/* push_back */
	template < class T, class Alloc >
		void	vector<T,Alloc>::push_back ( const value_type& val )
		{
			this->reserve( _size + 1 );
			_alloc.construct( _vec + _size, val );
			_size++;
		}

	/* pop_back */
	template < class T, class Alloc >
		void	vector<T,Alloc>::pop_back ( void )
		{
			_alloc.destroy( _vec + _size - 1 );
			_size--;
		}

	/* insert (single element) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::iterator
				vector<T,Alloc>::insert ( iterator pos, const value_type& val )
		{
			difference_type		n = pos - this->begin();
			this->reserve( _size + 1 );
			pos = this->begin() + n; // set position in newly allocated array

			_size++;
			if ( pos == this->end() - 1 )
			{ // equivalent to push_back( val )
				_alloc.construct( _vec + _size - 1, val );
			}
			else
			{
				// add one element at the end of the array
				_alloc.construct( _vec + _size - 1, _vec[_size - 2] );
				for ( iterator it = this->end() - 3; it >= pos ; it-- )
				{ // forward shift of every element after pos
					*(it + 1) = *it;
				}
				// fill element at pos with val
				*pos = val;
			}

			return ( pos );
		}

	/* insert (fill a single value) */
	template < class T, class Alloc >
		void	vector<T,Alloc>::insert ( iterator pos, size_type count,
				const value_type& val )
		{
			difference_type		n = pos - this->begin();
			this->reserve( _size + count );
			pos = this->begin() + n; // set position in newly allocated array

			value_type*	ptr = _vec + _size;
			for ( size_type i = 0; i < count; i++ )
			{ // add count elements at the end of the array
				_alloc.construct( ptr, *(ptr - count) );
				ptr++;
			}
			_size += count;
			for ( iterator it = this->end() - count - 2; it >= pos ; it-- )
			{ // forward shift of every element after pos
				*(it + count) = *it;
			}

			for ( size_type i = 0; i < count; i++ )
			{ // fill count elements from pos, with val
				*pos = val;
				pos++;
			}
		}

	/* insert (from a range of iterators) */
	template < class T, class Alloc >
		template < class InputIt >
			void	vector<T,Alloc>::insert ( iterator pos, typename enable_if<
						!is_integral<InputIt>::value, InputIt
					>::type first, InputIt last )
			{
				size_type	count = 0;
				for ( InputIt it = first; it != last; it++ )
					count++; // compute new size

				difference_type		n = pos - this->begin();
				this->reserve( _size + count );
				// set position in newly allocated array
				pos = this->begin() + n;

				value_type*	ptr = _vec + _size;
				for ( size_type i = 0; i < count; i++ )
				{ // add count elements at the end of the array
					_alloc.construct( ptr, *(ptr - count) );
					ptr++;
				}
				_size += count;
				for ( iterator it = this->end() - count - 2; it >= pos ; it-- )
				{ // forward shift of every element after pos
					*(it + count) = *it;
				}

				for ( size_type i = 0; i < count; i++ )
				{ // do the copy, starting from pos
					*pos = *first++;
					pos++;
				}
			}

	/* erase (single element) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::iterator
				vector<T,Alloc>::erase ( iterator pos )
		{
			iterator	it;
			iterator	it_last = this->end() - 1;
			for ( it = pos; it < it_last; it++ )
			{ // shift backwards every element after pos
				*it = *(it + 1);
			}
			_alloc.destroy( &*it ); // remove element at pos
			_size--;

			return ( pos );
		}

	/* erase (range) */
	template < class T, class Alloc >
		typename vector<T,Alloc>::iterator
				vector<T,Alloc>::erase ( iterator first, iterator last )
		{
			difference_type	range = last - first;

			iterator	it = first;
			iterator	ite = this->end();
			while ( last < ite )
			{ // shift backwards every element after pos
				*it = *last;
				it++;
				last++;
			}

			for ( ; it < ite; it++ )
				_alloc.destroy( &*it ); // remove elements at end of array
			_size -= range;

			return ( first );
		}

	/* swap */
	template < class T, class Alloc >
		void	vector<T,Alloc>::swap ( vector<T,Alloc>& other )
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
		void	vector<T,Alloc>::clear ( void )
		{
			for ( size_type i = 0; i < _size; i++ )
				_alloc.destroy( _vec + i );
			_size = 0;
		}


	/******* ALLOCATOR ********************************************************/

	/* get_allocator */
	template < class T, class Alloc >
		typename vector<T,Alloc>::allocator_type
				vector<T,Alloc>::get_allocator ( void ) const
		{
			return ( _alloc );
		}


	/******* NON-MEMBER FUNCTIONS *********************************************/

	/* == */
	template < class T, class Alloc >
		bool	operator== ( const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs )
		{
			if ( lhs.size() != rhs.size() )
				return ( false );
			return ( ft::equal( lhs.begin(), lhs.end(), rhs.begin() ) );
		}

	/* != */
	template < class T, class Alloc >
		bool	operator!= ( const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs )
		{
			return ( !operator==( lhs, rhs ) );
		}

	/* < */
	template < class T, class Alloc >
		bool	operator< ( const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs )
		{
			return ( ft::lexicographical_compare( lhs.begin(), lhs.end(),
						rhs.begin(), rhs.end() ) );
		}

	/* <= */
	template < class T, class Alloc >
		bool	operator<= ( const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs )
		{
			return ( !operator<( rhs, lhs ) );
		}

	/* > */
	template < class T, class Alloc >
		bool	operator> ( const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs )
		{
			return ( operator<( rhs, lhs ) );
		}

	/* >= */
	template < class T, class Alloc >
		bool	operator>= ( const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs )
		{
			return ( !operator<( lhs, rhs ) );
		}

	/* swap */
	template < class T, class Alloc >
		void	swap ( vector<T,Alloc>& lhs, vector<T,Alloc>& rhs )
		{
			lhs.swap( rhs );
		}

} // namespace ft

#endif // __VECTOR_TEMPLATEDEF_HPP__
