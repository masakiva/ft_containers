/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:40:56 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/16 18:43:00 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ENABLE_IF_HPP__
# define __ENABLE_IF_HPP__

namespace	ft
{
	template < bool Cond, class T = void >
	struct enable_if
	{
	};

	template < class T >
	struct enable_if<true, T>
	{
		typedef T type;
	};
}

#endif // __ENABLE_IF_HPP__
