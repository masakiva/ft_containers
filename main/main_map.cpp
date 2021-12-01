#include "main.hpp"

void	pair( void )
{
	std::cout << "PAIR" << std::endl;

	NAMESPACE::pair<test,int>	p ( 1, 2 );
	NAMESPACE::pair<test,int>	p2 ( p );

	std::cout << p.first << ", " << p.second << std::endl;

	NAMESPACE::pair<test,int>	p3 = NAMESPACE::make_pair<test,int>( 1, 2 );

	std::cout << p3.first << ", " << p3.second << std::endl;

	NAMESPACE::pair<int,test>	p4 ( 1, 2 );
	NAMESPACE::pair<int,test>	p5 ( p4 );

	std::cout << p5.first << ", " << p5.second << std::endl;

	NAMESPACE::pair<char,test>	p6;
	p6 = NAMESPACE::make_pair<char,test>( 'c', 2 );

	std::cout << p6.first << ", " << p6.second << std::endl;

	std::cout << "----------" << std::endl << std::endl;
}

template < class T >
struct	more
{
	bool	operator() ( const T& a, const T& b ) const { return ( a > b ); }
};

template < class T >
struct	same
{
	bool	operator() ( const T& a, const T& b ) const { return ( a == b ); }
};

void	map_modifiers( void )
{
	std::cout << "MODIFIERS" << std::endl;

	NAMESPACE::map<int,char>	map;

	map.insert ( NAMESPACE::make_pair( 1, 'a' ) );
	map.insert ( NAMESPACE::make_pair( 2, 'b' ) );
	map.insert ( NAMESPACE::make_pair( 3, 'c' ) );
	map.insert ( NAMESPACE::make_pair( 4, 'd' ) );
	map.insert ( NAMESPACE::make_pair( 5, 'e' ) );

	for ( NAMESPACE::map<int,char>::iterator it = map.begin();
			it != map.end(); ++it )
	{
		std::cout << it->first << " " << it->second << std::endl;
	}

	std::cout << "----------" << std::endl << std::endl;
}
//	NAMESPACE::map<char,int, more<char> >	map;
