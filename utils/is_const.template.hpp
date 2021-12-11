/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_const.template.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 00:48:08 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/28 00:49:52 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __IS_CONST_TEMPLATE_HPP__
# define __IS_CONST_TEMPLATE_HPP__

namespace	ft
{

	template < class T, bool constness >
	struct is_const
	{
		typedef	T			type;
	};

	template < class T >
	struct is_const<T, true>
	{
		typedef	const T		type;
	};

} // namespace ft

#endif // __IS_CONST_TEMPLATE_HPP__
