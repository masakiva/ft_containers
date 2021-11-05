/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:08:36 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/05 14:18:53 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.templatedef.hpp"
#include <cstdlib> // EXIT_SUCCESS
#include <iostream>

class test
{
	public:
		test() { std::cout << "fd" << std::endl; }
		~test() { std::cout << "df" << std::endl; }
};
int		main( void )
{
	ft::vector<int>	vec;
	ft::vector<test> f(3);

	return ( EXIT_SUCCESS );
}
