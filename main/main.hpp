#ifndef __MAIN_HPP__
# define __MAIN_HPP__

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include <vector>
#include <stack>
#include <map>
#include <cstdlib> // EXIT_SUCCESS
#include <iostream>

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
		test ( const test& src )
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
		test&	operator= ( const test& rhs )
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
		friend std::ostream&	operator<<( std::ostream& o, const test& rhs )
		{
			o << rhs.id;
			return ( o );
		}
};

struct	test_struct
{
	int n;
};

void	vector_canonicalform( void );
void	vector_iterator( void );
template < class T, class Alloc >
	void	print_vector( NAMESPACE::vector<T,Alloc>& vec );
void	vector_capacity( void );
void	vector_elementaccess( void );
void	vector_modifiers( void );
void	vector_allocator( void );
void	vector_non_member_functions( void );
void	reverse_iterator_vector( void );

void	stack_tests( void );

#endif // __MAIN_HPP__
