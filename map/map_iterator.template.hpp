/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.template.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:13:36 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/12/07 15:18:22 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_ITERATOR_TEMPLATE_HPP__
# define __MAP_ITERATOR_TEMPLATE_HPP__

#include "is_const.template.hpp"
#include "RBnode.class.hpp"

namespace	ft
{

	template < class T, bool constness = false >
	class	m_iterator
	{
		public:

			typedef	std::bidirectional_iterator_tag			iterator_category;
			typedef	typename is_const<T, constness>::type		value_type;
			typedef	std::ptrdiff_t								difference_type;
			typedef	typename is_const<T, constness>::type*		pointer;
			typedef	typename is_const<T, constness>::type&		reference;
			typedef	std::size_t									size_type;

		private:

			RBnode*		_node_ptr;
			RBnode*		_last_node_ptr;
			void*		_map_ptr;

		public:

			m_iterator ( void );
			m_iterator ( RBnode* ptr, void* map_ptr );
			m_iterator ( const m_iterator& src );
			template < class U >
				m_iterator ( const m_iterator<U, false>& src );
			~m_iterator ( void );

			m_iterator&	operator= ( const m_iterator& rhs );
			template < class U >
				m_iterator&	operator= ( const m_iterator<U, false>& rhs );

			RBnode*		get_node_ptr ( void ) const;
			void		set_node_ptr ( RBnode* ptr, void* map_ptr );
			RBnode*		get_last_node_ptr ( void ) const;
			void*		get_map_ptr ( void ) const;

			reference	operator* ( void ) const;
			pointer		operator-> ( void ) const;

			m_iterator&	operator++ ( void );
			m_iterator&	operator-- ( void );
			m_iterator	operator++ ( int );
			m_iterator	operator-- ( int );

			bool	operator== ( const m_iterator& rhs ) const;
			bool	operator== ( const m_iterator<T, true>& rhs );
			bool	operator== ( const m_iterator<T, false>& rhs );

			bool	operator!= ( const m_iterator& rhs ) const;
			bool	operator!= ( const m_iterator<T, true>& rhs );
			bool	operator!= ( const m_iterator<T, false>& rhs );

	}; // class m_iterator

} // namespace ft

#include "map_iterator.templatedef.hpp"

#endif // __MAP_ITERATOR_TEMPLATE_HPP__
