/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.template.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:40:56 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/28 00:51:26 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ENABLE_IF_TEMPLATE_HPP__
# define __ENABLE_IF_TEMPLATE_HPP__

namespace	ft
{

	template < bool Cond, class T = void >
	struct enable_if
	{
	};

	template < class T >
	struct enable_if<true, T>
	{ // overload of previous struct, for 'true' as value of Cond
		typedef T type; // make this type available if Cond is true
	};

} // namespace ft

#endif // __ENABLE_IF_TEMPLATE_HPP__
