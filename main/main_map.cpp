#include "main.hpp"

void	pair ( void )
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

void	map_canonicalform( void )
{
	std::cout << "CANONICAL FORM" << std::endl;

	{
		std::cout << "-> default and copy constructors" << std::endl;
		NAMESPACE::map<test,int>	map;
		std::cout << "----------" << std::endl;
		NAMESPACE::map<test,int>	map2( map );
		std::cout << "----------" << std::endl;
	}
	std::cout << "----------" << std::endl << std::endl;

	{
		std::cout << "-> fill constructor (with number of elements as argument), "
			"copy constructor, and operator= overload" << std::endl;
		NAMESPACE::map<int,test>	map;
		map.insert ( NAMESPACE::make_pair( 1, 'a' ) );
		map.insert ( NAMESPACE::make_pair( 2, 'b' ) );
		map.insert ( NAMESPACE::make_pair( 3, 'c' ) );
		std::cout << "----------" << std::endl;
		NAMESPACE::map<int,test>	map2( map );
		std::cout << "----------" << std::endl;
		NAMESPACE::map<int,test>	map3;
		map3 = map2;
		std::cout << "----------" << std::endl;
	}

	std::cout << "----------" << std::endl << std::endl;

	{
		std::cout << "-> range constructor (with iterators as arguments)"
			<< std::endl;
		NAMESPACE::map<test,test>	map;
		map.insert ( NAMESPACE::make_pair( 1, 'a' ) );
		map.insert ( NAMESPACE::make_pair( 2, 'b' ) );
		map.insert ( NAMESPACE::make_pair( 3, 'c' ) );
		NAMESPACE::map<test,test>::iterator	it = map.begin();
		NAMESPACE::map<test,test>::iterator	ite = map.end();
		NAMESPACE::map<test,test>	map2( it, ite );
		std::cout << "----------" << std::endl;
	}

	std::cout << "--------------------" << std::endl << std::endl;
}

NAMESPACE::map<int,char>	sample_map ( void )
{
	NAMESPACE::map<int,char>	map;

	map.insert ( NAMESPACE::make_pair( 1, 'a' ) );
	map.insert ( NAMESPACE::make_pair( 2, 'b' ) );
	map.insert ( NAMESPACE::make_pair( 3, 'c' ) );
	map.insert ( NAMESPACE::make_pair( 4, 'd' ) );
	map.insert ( NAMESPACE::make_pair( 5, 'e' ) );

	return ( map );
}

void	map_iterator ( void )
{
	std::cout << "ITERATOR" << std::endl;

	NAMESPACE::map<int,char>	map = sample_map();
	std::cout << "-> sample map with 5 elements (keys go from 1 to 5, "
		<< "and values from 'a' to 'e')" << std::endl;

	std::cout << "map:\t";
	NAMESPACE::map<int,char>::const_iterator cit = map.begin();
	NAMESPACE::map<int,char>::iterator ite = map.end();
	for ( ; cit != ite; cit++ )
		std::cout << '\t' << cit->first << ' ' << cit->second;
	std::cout << std::endl;

	std::cout << "map reversed:";
	NAMESPACE::map<int,char>::const_reverse_iterator crite = map.rend();
	for ( NAMESPACE::map<int,char>::reverse_iterator rit = map.rbegin();
			rit != crite; ++rit )
		std::cout << '\t' << rit->first << ' ' << rit->second;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}

void	map_capacity ( void )
{
	std::cout << "CAPACITY" << std::endl;

	NAMESPACE::map<int,char>	map = sample_map();
	std::cout << "-> sample map with 5 elements (keys go from 1 to 5, "
		<< "and values from 'a' to 'e')" << std::endl;
	std::cout << "map.size() = " << map.size() << std::endl;
	std::cout << "map.max_size() = " << map.max_size() << std::endl;
	std::cout << "map.empty() = " << map.empty() << std::endl;
	std::cout << "----------" << std::endl;

	NAMESPACE::map<int,char>	map2;
	std::cout << "-> map2 default constructed" << std::endl;
	std::cout << "map2.empty() = " << map2.empty() << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}

void	map_elementaccess ( void )
{
	std::cout << "ELEMENT ACCESS" << std::endl;

	NAMESPACE::map<int,char>	map = sample_map();

}

void	map_modifiers ( void )
{
	std::cout << "MODIFIERS" << std::endl;

	NAMESPACE::map<int,char>	map;

	map.insert ( NAMESPACE::make_pair( 1, 'a' ) );
	map.insert ( NAMESPACE::make_pair( 2, 'b' ) );
	map.insert ( NAMESPACE::make_pair( 3, 'c' ) );
	map.insert ( NAMESPACE::make_pair( 4, 'd' ) );
	map.insert ( NAMESPACE::make_pair( 5, 'e' ) );

	for ( NAMESPACE::map<int,char>::const_iterator it = map.begin();
			it != map.end(); ++it )
	{
		std::cout << it->first << " " << it->second << std::endl;
	}

	std::cout << "----------" << std::endl << std::endl;
}
//	NAMESPACE::map<char,int, more<char> >	map;
