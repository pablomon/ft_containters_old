#include "tests.hpp"
#include "../containers/map.hpp"
#include <map>
#include <iomanip>

#define NS ft

void map_tests()
{
	chapter("\nT E S T I N G   M A P");

	

// #define NS std
// {
// 	NS::map<int,int> mapa;
// 	mapa.insert(NS::pair<int,int>(1,1));
// 	mapa.insert(NS::pair<int,int>(2,2));

// 	NS::map<int,int> mapa2 = mapa;

// 	mapa.erase(1);
// 	for (NS::map<int,int>::iterator it = mapa.begin(); it != mapa.end(); it++)
// 	{
// 		std::cout << it->first << std::endl;
// 	}
	
// 	for (NS::map<int,int>::iterator it = mapa2.begin(); it != mapa2.end(); it++)
// 	{
// 		std::cout << it->first << std::endl;
// 	}
// }
{
	std::cout << std::endl;
	NS::map<std::string,std::string> mapa;
	NS::map<std::string,std::string>::iterator it1 = mapa.insert(NS::pair<std::string,std::string>("k1","v1")).first;
	std::cout << it1->first << std::endl;
	mapa.insert(it1, NS::pair<std::string,std::string>("k3","v3"));
	NS::map<std::string,std::string>::iterator it2 = mapa.insert(NS::pair<std::string,std::string>("k2","v2")).first;
	std::cout << it2->first << std::endl;
	std::cout << std::endl;

	// NS::map<std::string,std::string> mapa2 = mapa;

	// mapa.erase(1);
	// mapa.erase(2);
	mapa.insert(it1, it2);


	// for (NS::map<std::string,std::string>::iterator it = it1; it != it2; it++)
	// {
	// 	std::cout << it->first << std::endl;
	// }

	for (NS::map<std::string,std::string>::iterator it = mapa.begin(); it != mapa.end(); it++)
	{
		std::cout << it->first << std::endl;
	}
	
	// for (NS::map<std::string,std::string>::iterator it = mapa2.begin(); it != mapa2.end(); it++)
	// {
	// 	std::cout << it->first << std::endl;
	// }
}
}