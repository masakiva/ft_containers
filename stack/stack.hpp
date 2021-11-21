/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:51:32 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/21 13:37:52 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_HPP__
# define __STACK_HPP__

#include "vector.hpp"

namespace	ft
{
	template < class T, class Container = vector<T> >
	class	stack
	{
		public:

			typedef	T								value_type;
			typedef	Container						container_type;
			typedef	typename Container::size_type	size_type;

		private:

			container_type		_cont;

		public:

			/* default constructor */
			explicit stack ( const container_type& cont = container_type() ) :
				_cont( cont ) { }

			/* copy constructor */
			stack ( const stack& src ) { *this = src; }

			/* destructor */
			~stack ( void ) { }

			/* = */
			stack&		operator= ( const stack &rhs )
			{
				if ( this == &rhs )
					return ( *this );
				_cont = rhs._cont;
				return ( *this );
			}

			/* empty */
			bool				empty( void ) const
			{ return ( _cont.empty() ); }

			/* size */
			size_type			size( void ) const
			{ return ( _cont.size() ); }

			/* top */
			value_type&			top( void )
			{ return ( _cont.back() ); }

			/* top (const) */
			const value_type&	top( void ) const
			{ return ( _cont.back() ); }

			/* push */
			void				push ( const value_type& val )
			{ _cont.push_back( val ); }

			/* pop */
			void				pop( void )
			{ _cont.pop_back(); }


			/* == */
			template < class U, class Cont >
				friend bool		operator== ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs._cont == rhs._cont ); }

			/* != */
			template < class U, class Cont >
				friend bool		operator!= ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs._cont != rhs._cont ); }

			/* < */
			template < class U, class Cont >
				friend bool		operator<  ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs._cont < rhs._cont ); }

			/* <= */
			template < class U, class Cont >
				friend bool		operator<= ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs._cont <= rhs._cont ); }

			/* > */
			template < class U, class Cont >
				friend bool		operator>  ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs._cont > rhs._cont ); }

			/* >= */
			template < class U, class Cont >
				friend bool		operator>= ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs._cont >= rhs._cont ); }
	};

} // namespace ft

#endif // __STACK_HPP__
