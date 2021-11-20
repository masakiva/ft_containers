/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:51:32 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/20 15:00:41 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_HPP__
# define __STACK_HPP__

#include "vector.hpp"

namespace	ft
{
	template < class T >
	class	stack : public vector
	{
		public:

			typedef	T			value_type;
			typedef	vector<T>	container_type;
			typedef	size_t		size_type;

	};

} // namespace ft

#endif __STACK_HPP__
