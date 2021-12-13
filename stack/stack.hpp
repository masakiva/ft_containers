/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:51:32 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/13 17:51:35 by mvidal-a         ###   ########.fr       */
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

		protected:

			container_type		c;

		public:

			/* default constructor */
			explicit stack ( const container_type& cont = container_type() ) :
				c( cont ) { }

			/* copy constructor */
			stack ( const stack& src ) { *this = src; }

			/* destructor */
			~stack ( void ) { }

			/* = */
			stack&		operator= ( const stack &rhs )
			{
				if ( this == &rhs )
					return ( *this );
				c = rhs.c;
				return ( *this );
			}

			/* empty */
			bool				empty( void ) const
			{ return ( c.empty() ); }

			/* size */
			size_type			size( void ) const
			{ return ( c.size() ); }

			/* top */
			value_type&			top( void )
			{ return ( c.back() ); }

			/* top (const) */
			const value_type&	top( void ) const
			{ return ( c.back() ); }

			/* push */
			void				push ( const value_type& val )
			{ c.push_back( val ); }

			/* pop */
			void				pop( void )
			{ c.pop_back(); }


			/* == */
			template < class U, class Cont >
				friend bool		operator== ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs.c == rhs.c ); }

			/* != */
			template < class U, class Cont >
				friend bool		operator!= ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs.c != rhs.c ); }

			/* < */
			template < class U, class Cont >
				friend bool		operator<  ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs.c < rhs.c ); }

			/* <= */
			template < class U, class Cont >
				friend bool		operator<= ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs.c <= rhs.c ); }

			/* > */
			template < class U, class Cont >
				friend bool		operator>  ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs.c > rhs.c ); }

			/* >= */
			template < class U, class Cont >
				friend bool		operator>= ( const stack<U,Cont>& lhs,
						const stack<U,Cont>& rhs )
				{ return ( lhs.c >= rhs.c ); }
	};

} // namespace ft

#endif // __STACK_HPP__
