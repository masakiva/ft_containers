/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:31:44 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/20 12:32:38 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __IS_INTEGRAL_HPP__
# define __IS_INTEGRAL_HPP__

namespace	ft
{

	template < class T, T v >
	struct	integral_constant
	{
		static const T value = v;
	};

	typedef	integral_constant<bool, true>	true_type;
	typedef	integral_constant<bool, false>	false_type;

	template < class T >
	struct	is_integral : ft::false_type { };

	template < >
	struct	is_integral<bool> : ft::true_type { };
	template < >
	struct	is_integral<char> : ft::true_type { };
	template < >
	struct	is_integral<unsigned char> : ft::true_type { };
	template < >
	struct	is_integral<wchar_t> : ft::true_type { };
	template < >
	struct	is_integral<short> : ft::true_type { };
	template < >
	struct	is_integral<unsigned short> : ft::true_type { };
	template < >
	struct	is_integral<int> : ft::true_type { };
	template < >
	struct	is_integral<unsigned int> : ft::true_type { };
	template < >
	struct	is_integral<long> : ft::true_type { };
	template < >
	struct	is_integral<unsigned long> : ft::true_type { };

} // namespace ft

#endif // __IS_INTEGRAL_HPP__
