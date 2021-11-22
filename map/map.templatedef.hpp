/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.templatedef.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:43:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/22 15:30:54 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_TEMPLATEDEF_HPP__
# define __MAP_TEMPLATEDEF_HPP__

namespace	ft
{

	/******* CANONICAL FORM ***************************************************/

	/* default constructor */
	template <	class Key, class T, class Compare, class Alloc >
		map<Key,T,Compare,Alloc>::map ( const key_compare& comp,
				const allocator_type& alloc ) :
			_alloc( alloc ),
			_size( 0 )
		{
			_map = _alloc.allocate( _size );
		}

} // namespace ft

#endif // __MAP_TEMPLATEDEF_HPP__
