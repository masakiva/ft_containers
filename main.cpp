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
	std::cout << "----------" << std::endl;

	std::cout << "for loop with brackets operator ([]):";
	for ( NAMESPACE::vector<int>::size_type i = 0; i < vec.size(); i++ )
	{
		std::cout << " " << vec[i];
	}
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl;
}

template < class T, class Alloc >
	void	print_vector( NAMESPACE::vector<T, Alloc>& vec )
	{
		std::cout << "values:";
		for ( typename NAMESPACE::vector<T, Alloc>::size_type i = 0;
				i < vec.size(); i++ )
		{
			std::cout << " " << vec[i];
		}
		std::cout << std::endl;
		std::cout << "capacity = " << vec.capacity() << std::endl;
		std::cout << "size = " << vec.size() << std::endl;
		std::cout << "----------" << std::endl;
	}

void	vector_capacity( void )
{
	std::cout << "CAPACITY" << std::endl;
	NAMESPACE::vector<int>	vec( 3, 2 );
	std::cout << "-> vec( 3 )" << std::endl;
	print_vector( vec );
	vec.resize( 4 );
	std::cout << "-> resize( 4 )" << std::endl;
	print_vector( vec );
	vec.reserve( 5 );
	std::cout << "-> reserve( 5 )" << std::endl;
	print_vector( vec );
	vec.resize( 5, 3 );
	std::cout << "-> resize( 5, 3 )" << std::endl;
	print_vector( vec );
	vec.reserve( 2 );
	std::cout << "-> reserve( 2 )" << std::endl;
	print_vector( vec );
	vec.resize( 1, 1 );
	std::cout << "-> resize( 1, 1 )" << std::endl;
	print_vector( vec );
	std::cout << "max_size = " << vec.max_size() << std::endl;
	std::cout << "empty = " << vec.empty() << std::endl;
	NAMESPACE::vector<test>	vec2;
	std::cout << "-> vec2 ()" << std::endl;
	std::cout << "vec2.empty = " << vec2.empty() << std::endl;
	std::cout << "--------------------" << std::endl;
}

void	vector_modifiers( void )
{
	std::cout << "MODIFIERS" << std::endl;

	NAMESPACE::vector<int> vec( 2, 4 );
	std::cout << "-> vec( 2, 4 )" << std::endl;
	print_vector( vec );

	vec.assign( 1, 3 );
	std::cout << "-> assign( 1, 3 )" << std::endl;
	print_vector( vec );

	vec.assign( 4, 6 );
	std::cout << "-> assign( 4, 6 )" << std::endl;
	print_vector( vec );

	vec.assign( 3, 5 );
	std::cout << "-> assign( 3, 5 )" << std::endl;
	print_vector( vec );

	vec.push_back( 2 );
	std::cout << "-> push_back( 2 )" << std::endl;
	print_vector( vec );

	vec.push_back( 7 );
	std::cout << "-> push_back( 7 )" << std::endl;
	print_vector( vec );

	vec.pop_back();
	std::cout << "-> pop_back()" << std::endl;
	print_vector( vec );

	NAMESPACE::vector<int> vec2( 2, 9 );
	std::cout << "-> vec2( 2, 9 )" << std::endl;
	print_vector( vec2 );

	vec.swap( vec2 );
	std::cout << "-> vec.swap( vec2 )" << std::endl;
	std::cout << "vec: " << std::endl;
	print_vector( vec );
	std::cout << "vec2: " << std::endl;
	print_vector( vec2 );

	vec.clear();
	std::cout << "-> vec.clear()" << std::endl;
	print_vector( vec );

	std::cout << "--------------------" << std::endl;
}

void	vector_allocator( void )
{
	NAMESPACE::vector<int> vec;
	vec.get_allocator();
}

void	vector_iterator( void )
{
	NAMESPACE::vector<int>				vec( 3, 41 );
	NAMESPACE::vector<int>::iterator	it;

	for ( it = vec.begin(); it != vec.end(); it++ )
		std::cout << *it << std::endl;
}

int		main ( void )
{
//	vector_canonicalform();
//	vector_elementaccess();
//	vector_capacity();
//	vector_modifiers();
//	vector_allocator();
	vector_iterator();

	return ( EXIT_SUCCESS );
}
