#include "vector.templatedef.hpp"
#include <cstdlib> // EXIT_SUCCESS
#include <iostream>
#include <vector>

class test
{
	public:

		int		id;

		test ( void )
		{
			static int i = 1000;
			id = i;
			i++;
			std::cout << "[" << id << "] default constructor" << std::endl;
		}
		test ( int arg )
		{
			(void)arg;
			static int i = 0;
			id = i;
			i++;
			std::cout << "[" << id << "] parameterized constructor"
				<< std::endl;
		}
		test ( const test &src )
		{
			id = src.id + 10;
			std::cout << "[" << id << "] copy constructor from " << src.id
				<< std::endl;
			*this = src;
		}
		~test ( void )
		{
			std::cout << "[" << id << "] destructor" << std::endl;
		}
		test&	operator= ( const test &rhs )
		{
			std::cout << "[" << id << "-->" << rhs.id + 100
				<< "] operator= (test &) from " << rhs.id << std::endl;
			id = rhs.id + 100;
			return ( *this );
		}
		test&	operator= ( int arg )
		{
			std::cout << "[" << id << "-->" << arg + 100
				<< "] operator= (int) from " << arg << " (int arg) "
				<< std::endl;
			id = arg + 100;
			return ( *this );
		}
};

void	vector_canonicalform( void )
{
	std::cout << "CANONICAL FORM" << std::endl;
	{
		NAMESPACE::vector<test>	vec;
		std::cout << "----------" << std::endl;
		NAMESPACE::vector<test>	vec2( vec );
		std::cout << "----------" << std::endl;
	}
	std::cout << "----------" << std::endl;
	{
		NAMESPACE::vector<test>	vec3( 2 );
		std::cout << "----------" << std::endl;
		NAMESPACE::vector<test>	vec4( vec3 );
		std::cout << "----------" << std::endl;
		NAMESPACE::vector<test> vec5;
		vec5 = vec4;
		std::cout << "----------" << std::endl;
	}
	std::cout << "--------------------" << std::endl;
}

void	vector_elementaccess( void )
{
	std::cout << "ELEMENT ACCESS" << std::endl;
	NAMESPACE::vector<int>	vec( 3, 1 );
	vec[1] = 2;
	vec[2] = 3;
	std::cout << "front = " << vec.front() << std::endl;
	std::cout << "at 1 = " << vec.at( 1 ) << std::endl;
	std::cout << "back = " << vec.back() << std::endl;
	try
	{
		std::cout << vec.at( 4 ) << std::endl;
	}
	catch ( std::exception &e )
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "--------------------" << std::endl;

}

void	vector_capacity( void )
{
	std::cout << "CAPACITY" << std::endl;
	NAMESPACE::vector<int>	vec( 3 );
	std::cout << "capacity 1 = " << vec.capacity() << std::endl;
	std::cout << "size 1 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.resize( 4 );
	std::cout << "capacity 2 = " << vec.capacity() << std::endl;
	std::cout << "size 2 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.reserve( 5 );
	std::cout << "capacity 3 = " << vec.capacity() << std::endl;
	std::cout << "size 3 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.resize( 5, 0 );
	std::cout << "capacity 4 = " << vec.capacity() << std::endl;
	std::cout << "size 4 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.reserve( 2 );
	std::cout << "capacity 5 = " << vec.capacity() << std::endl;
	std::cout << "size 5 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.resize( 1 );
	std::cout << "capacity 6 = " << vec.capacity() << std::endl;
	std::cout << "size 6 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "max_size = " << vec.max_size() << std::endl;
	std::cout << "empty 1 = " << vec.empty() << std::endl;
	NAMESPACE::vector<test>	vec2;
	std::cout << "empty 2 = " << vec2.empty() << std::endl;
}

void	vector_modifiers()
{
	std::cout << "MODIFIERS" << std::endl;
	NAMESPACE::vector<int> vec( 2, 4 );
	std::cout << "vec[0] 1 = " << vec[0] << std::endl;
	std::cout << "capacity 1 = " << vec.capacity() << std::endl;
	std::cout << "size 1 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.assign( 1, 3 );
	std::cout << "vec[0] 2 = " << vec[0] << std::endl;
	std::cout << "capacity 2 = " << vec.capacity() << std::endl;
	std::cout << "size 2 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.assign( 4, 6 );
	std::cout << "vec[0] 3 = " << vec[0] << std::endl;
	std::cout << "vec[3] = " << vec[3] << std::endl;
	std::cout << "capacity 3 = " << vec.capacity() << std::endl;
	std::cout << "size 3 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.assign( 3, 5 );
	std::cout << "vec[0] 4 = " << vec[0] << std::endl;
	std::cout << "vec[2] = " << vec[2] << std::endl;
	std::cout << "capacity 4 = " << vec.capacity() << std::endl;
	std::cout << "size 4 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.push_back( 2 );
	std::cout << "vec[0] 5 = " << vec[0] << std::endl;
	std::cout << "vec[3] = " << vec[3] << std::endl;
	std::cout << "capacity 5 = " << vec.capacity() << std::endl;
	std::cout << "size 5 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.push_back( 7 );
	std::cout << "vec[0] 6 = " << vec[0] << std::endl;
	std::cout << "vec[4] = " << vec[4] << std::endl;
	std::cout << "capacity 6 = " << vec.capacity() << std::endl;
	std::cout << "size 6 = " << vec.size() << std::endl;
	std::cout << "----------" << std::endl;
	vec.pop_back();
	std::cout << "vec[0] 7 = " << vec[0] << std::endl;
	std::cout << "vec[3] = " << vec[3] << std::endl;
	std::cout << "capacity 7 = " << vec.capacity() << std::endl;
	std::cout << "size 7 = " << vec.size() << std::endl;
	vec.clear();
	std::cout << "capacity 8 = " << vec.capacity() << std::endl;
	std::cout << "size 8 = " << vec.size() << std::endl;
}

int		main ( void )
{
//	vector_canonicalform();
//	vector_elementaccess();
//	vector_capacity();
	vector_modifiers();

	return ( EXIT_SUCCESS );
}
