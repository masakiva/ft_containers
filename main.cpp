#include "vector.templatedef.hpp"
#include "reverse_iterator.hpp"
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
std::ostream&	operator<<( std::ostream &o, test const &rhs )
{
	o << rhs.id;
	return ( o );
}


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

	std::cout << "--------------------" << std::endl << std::endl;
}

struct	test_struct { int n; };

void	vector_iterator( void )
{
	std::cout << "ITERATOR" << std::endl;

	NAMESPACE::vector<int>	vec( 5 );
	int		i = 0;
	for ( NAMESPACE::vector<int>::reverse_iterator rit = vec.rbegin();
			rit != vec.rend(); ++rit )
		*rit = ++i;
	std::cout << "vec:";
	for ( NAMESPACE::vector<int>::iterator it = vec.begin();
			it != vec.end(); ++it )
		std::cout << ' ' << *it;
	std::cout << std::endl;

	i = 1;
	NAMESPACE::vector<test_struct>	vec2( 9 );
	for ( NAMESPACE::vector<test_struct>::iterator it = vec2.begin() + 1;
			it <= vec2.end(); it++ )
		(it - 1)->n = i++;
	std::cout << "vec2 len: " << vec2.end() - vec2.begin() << std::endl;
	std::cout << "vec2 (odd values):";
	for ( NAMESPACE::vector<test_struct>::iterator it = vec2.begin();
			it < vec2.end(); it += 2 )
		std::cout << ' ' << it->n;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}

template < class T, class Alloc >
	void	print_vector( NAMESPACE::vector<T,Alloc>& vec )
	{
		std::cout << "values:";
		for ( typename NAMESPACE::vector<T,Alloc>::size_type i = 0;
				i < vec.size(); i++ )
		{
			std::cout << ' ' << vec[i];
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

	std::cout << "--------------------" << std::endl << std::endl;
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

	std::cout << "--------------------" << std::endl << std::endl;
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

	vec.pop_back();
	std::cout << "-> pop_back()" << std::endl;
	print_vector( vec );

	vec.push_back( 8 );
	std::cout << "-> push_back( 2 )" << std::endl;
	print_vector( vec );

	vec.push_back( 7 );
	std::cout << "-> push_back( 7 )" << std::endl;
	print_vector( vec );

	vec.push_back( 1 );
	std::cout << "-> push_back( 1 )" << std::endl;
	print_vector( vec );

	std::cout << "-> insert( 1, 3 )" << std::endl;
	std::cout << "value inserted: " << *vec.insert( vec.begin() + 1, 3 )
		<< std::endl;
	print_vector( vec );

	vec.insert( vec.begin() + 5, 2, 9 );
	std::cout << "-> insert( 1, 2, 3 )" << std::endl;
	print_vector( vec );

	std::cout << "-> erase( 2 )" << std::endl;
	std::cout << "value following erased one: " << *vec.erase( vec.begin() + 2 )
		<< std::endl;
	print_vector( vec );

	std::cout << "-> erase( 1, 3 )" << std::endl;
	std::cout << "value following erased ones: "
		<< *vec.erase( vec.begin() + 1, vec.begin() + 3 ) << std::endl;
	print_vector( vec );

	vec.assign( 4, 2 );
	std::cout << "-> assign( 4, 2 )" << std::endl;
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

	std::cout << "--------------------" << std::endl << std::endl;
}

void	vector_allocator( void )
{
	NAMESPACE::vector<int> vec;
	vec.get_allocator();
}

void	reverse_iterator_vector( void )
{
	std::cout << "REVERSE ITERATOR" << std::endl;

	std::vector<int>	vec;

	for ( std::vector<int>::size_type i = 0; i < 10; i++ )
		vec.push_back( i );

	typedef	std::vector<int>::iterator	iter_type;
	iter_type		from( vec.begin() );
	iter_type		until( vec.end() );

	NAMESPACE::reverse_iterator<iter_type>	rev_until( from );
	NAMESPACE::reverse_iterator<iter_type>	rev_from( until );

	std::cout << "vec rev:";
	while ( rev_from < rev_until )
		std::cout << ' ' << *rev_from++;
	std::cout << std::endl;

	rev_from -= 10;
	std::cout << "vec (using underlying iterator):";
	for ( iter_type it = rev_until.base(); it != rev_from.base(); it++ )
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "vec span = " << rev_from - rev_until << std::endl;

	std::cout << "vec rev:";
	for ( std::vector<int>::size_type i = 0; i < 10; i++ )
		std::cout << ' ' << rev_from[i];
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}

int		main ( void )
{
//	vector_canonicalform();
//	vector_iterator();
//	vector_capacity();
//	vector_elementaccess();
	vector_modifiers();
//	vector_allocator();
//	reverse_iterator_vector();

	return ( EXIT_SUCCESS );
}
