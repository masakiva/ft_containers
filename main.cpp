/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:08:36 by mvidal-a          #+#    #+#             */
/*   Updated: 2021/11/09 19:40:55 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.templatedef.hpp"
#include <cstdlib> // EXIT_SUCCESS
#include <iostream>
#include <vector>

class test
{
	private:

		int		_r;

	public:

		test ( void )
		{
			srand( clock() );
			this->_r = rand();
			std::cout << "default constructor of " << this->_r << std::endl;
		}
		test ( const test &src )
		{
			this->_r = src._r + 1;
			std::cout << "copy constructor of " << this->_r << std::endl;
		}
		~test ( void )
		{
			std::cout << "destructor of " << this->_r << std::endl;
		}

};

int		main ( void )
{
	ft::vector<int>	vec;
	ft::vector<int>	vec2( vec );
	ft::vector<int> vec3( 4, 2 );
	ft::vector<int>	vec4( vec3 );

	try
	{
		std::cout << vec3.at( 4 ) << std::endl;
	}
	catch ( std::exception &e )
	{
		std::cout << e.what() << std::endl;
	}

	return ( EXIT_SUCCESS );
}
