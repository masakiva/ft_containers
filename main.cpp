#include "vector.templatedef.hpp"
#include <cstdlib> // EXIT_SUCCESS
#include <iostream>
#include <vector>

class test
{
	public:

		int		r;

		test ( void )
		{
			static int i = 0;
			r = i;
			i++;
			std::cout << r << ": default constructor" << std::endl;
		}
		test ( const test &src )
		{
			r = src.r + 10;
			std::cout << r << ": copy constructor"<< std::endl;
		}
		~test ( void )
		{
			std::cout << r << ": destructor" << std::endl;
		}

};

int		main ( void )
{
//	ft::vector<int>	vec;
//	ft::vector<int>	vec2( vec );
//	ft::vector<int> vec3( 4, 2 );
//	ft::vector<int>	vec4( vec3 );
	std::vector<test> testvec( 1 );
	std::cout << "----------" << std::endl;
	std::cout << testvec.empty() << std::endl;
	std::cout << "----------" << std::endl;
	testvec.resize( 0 );
	std::cout << "----------" << std::endl;
	std::cout << testvec.empty() << std::endl;
	std::cout << "----------" << std::endl;

//	try
//	{
//		std::cout << vec3.at( 4 ) << std::endl;
//	}
//	catch ( std::exception &e )
//	{
//		std::cout << e.what() << std::endl;
//	}

	return ( EXIT_SUCCESS );
}
