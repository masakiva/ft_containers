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

void	map_modifiers( void )
{
	std::cout << "MODIFIERS" << std::endl;

	NAMESPACE::map<char,int>	map;

	char	c = 'a';
	int		i = 100;
	map.insert ( NAMESPACE::make_pair( c, i ) );

	std::cout << "----------" << std::endl << std::endl;
}
