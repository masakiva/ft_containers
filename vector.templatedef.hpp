/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.templatedef.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:45:40 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/02 19:57:58 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MUTANTSTACK_TEMPLATEDEF_HPP__
# define __MUTANTSTACK_TEMPLATEDEF_HPP__

#include "MutantStack.template.hpp"

template < typename T >
MutantStack<T>::MutantStack( void ) :
	_begin(NULL),
	_end(NULL)
{ }

template < typename T >
MutantStack<T>::MutantStack( const MutantStack<T>& src ) :
	_begin(NULL),
	_end(NULL)
{ *this = src; }

template < typename T >
MutantStack<T>::~MutantStack( void ) { }

template < typename T >
MutantStack<T>&		MutantStack<T>::operator=( const MutantStack<T>& rhs )
{
	if ( this == &rhs )
		return ( *this );

	this->_begin = rhs._begin;
	this->_end = rhs._end;

	return ( *this );
}

template < typename T >
void	MutantStack<T>::push( const T& val )
{
	std::stack<T>::push( val );
	if ( this->size() == 1 )
		this->_begin = &this->top();
	this->_end = &this->top() + 1;
}

template < typename T >
void	MutantStack<T>::pop( void )
{
	std::stack<T>::pop();
	if ( this->size() == 0 )
	{
		this->_begin = NULL;
		this->_end = NULL;
	}
	else
	{
		this->_end = &this->top() + 1;
	}
}

template < typename T >
typename MutantStack<T>::iterator	MutantStack<T>::begin( void )
{
	MutantStack<T>::iterator	it( this->_begin );

	return ( it );
}

template < typename T >
typename MutantStack<T>::iterator	MutantStack<T>::end( void )
{
	MutantStack<T>::iterator	ite( this->_end );

	return ( ite );
}


template < typename T >
MutantStack<T>::iterator::iterator( void ) :
	_ptr(NULL)
{ }

template < typename T >
MutantStack<T>::iterator::iterator( T* ptr ) :
	_ptr(ptr)
{ }

template < typename T >
MutantStack<T>::iterator::iterator( const MutantStack<T>::iterator& src )
{ *this = src; }

template < typename T >
MutantStack<T>::iterator::~iterator( void ) { }

template < typename T >
typename MutantStack<T>::iterator&	MutantStack<T>::iterator::operator=(
		const MutantStack<T>::iterator& rhs )
{
	if ( this == &rhs )
		return ( *this );

	this->_ptr = rhs._ptr;

	return ( *this );
}

template < typename T >
T&		MutantStack<T>::iterator::operator*( void ) const
{
	return ( *this->_ptr );
}

template < typename T >
bool		MutantStack<T>::iterator::operator>(
		const MutantStack<T>::iterator &rhs ) const
{
	return ( this->_ptr > rhs._ptr );
}

template < typename T >
bool		MutantStack<T>::iterator::operator<(
		const MutantStack<T>::iterator &rhs ) const
{
	return ( this->_ptr < rhs._ptr );
}

template < typename T >
bool		MutantStack<T>::iterator::operator>=(
		const MutantStack<T>::iterator &rhs ) const
{
	return ( this->_ptr >= rhs._ptr );
}

template < typename T >
bool		MutantStack<T>::iterator::operator<=(
		const MutantStack<T>::iterator &rhs ) const
{
	return ( this->_ptr <= rhs._ptr );
}

template < typename T >
bool		MutantStack<T>::iterator::operator==(
		const MutantStack<T>::iterator &rhs ) const
{
	return ( this->_ptr == rhs._ptr );
}

template < typename T >
bool		MutantStack<T>::iterator::operator!=(
		const MutantStack<T>::iterator &rhs ) const
{
	return ( this->_ptr != rhs._ptr );
}

template < typename T >
typename MutantStack<T>::iterator&	MutantStack<T>::iterator::operator++( void )
{
	this->_ptr++;

	return ( *this );
}

template < typename T >
typename MutantStack<T>::iterator&	MutantStack<T>::iterator::operator--( void )
{
	this->_ptr--;

	return ( *this );
}

template < typename T >
typename MutantStack<T>::iterator	MutantStack<T>::iterator::operator++( int )
{
	iterator	before_inc( *this );

	this->_ptr++;

	return ( before_inc );
}

template < typename T >
typename MutantStack<T>::iterator	MutantStack<T>::iterator::operator--( int )
{
	iterator	before_dec( *this );

	this->_ptr--;

	return ( before_dec );
}

#endif // __MUTANTSTACK_TEMPLATEDEF_HPP__
