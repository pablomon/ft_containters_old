// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "containers/map.hpp"
#include <map>

#define log(x) std::cout << x << std::endl
#define NS ft

template <class T>
void printmap(NS::map<T,T> mapa, std::string name)
{
	std::cout << "printing " << name << std::endl;
	std::cout << "  size = " << mapa.size() << std::endl;
	for (NS::map<std::string, std::string>::iterator it = mapa.begin(); it != mapa.end(); it++)
		std::cout << "  " << it->first << std::endl;
	std::cout << "end of print" << std::endl;
	std::cout << std::endl;
}


int main()
{
	std::cout << "Running...." << std::endl;

	//const iterators
	{
		std::cout << "-------" << std::endl;
		NS::map<int,int> map;
		map.insert(NS::pair<int,int>(1,1));
		map.insert(NS::pair<int,int>(2,2));
		map.insert(NS::pair<int,int>(3,3));
		printmap(map, "map");

		// map.m_tree.print();
		std::cout << "----" << std::endl;
		NS::map<int,int>::const_iterator beg = map.begin();
	}

	return 0;
	//// iterators
	//{
	//	std::cout << "-------" << std::endl;
	//	NS::map<std::string, std::string> map;
	//	map.insert(NS::pair<std::string, std::string>("k1", "v1"));
	//	map.insert(NS::pair<std::string, std::string>("k2", "v2"));
	//	map.insert(NS::pair<std::string, std::string>("k6", "v6"));
	//	map.insert(NS::pair<std::string, std::string>("k7", "v7"));
	//	printmap(map, "map");

	//	// map.m_tree.print();
	//	std::cout << "----" << std::endl;
	//	NS::map<std::string, std::string>::iterator beg = map.begin();
	//	NS::map<std::string, std::string>::iterator end = map.end();
	//	while (end != beg)
	//	{
	//		--end;
	//		std::cout << end->first << '\n';
	//	}
	//	std::cout << "----" << std::endl;
	//}
	//



	//// const iterators
	//{
	//	std::cout << "-------" << std::endl;
	//	NS::map<std::string, std::string> map;
	//	map.insert(NS::pair<std::string, std::string>("k1", "v1"));
	//	map.insert(NS::pair<std::string, std::string>("k2", "v2"));
	//	map.insert(NS::pair<std::string, std::string>("k6", "v6"));
	//	map.insert(NS::pair<std::string, std::string>("k7", "v7"));
	//	printmap(map, "map");

	//	// map.m_tree.print();
	//	std::cout << "----" << std::endl;
	//	NS::map<std::string, std::string>::const_iterator beg = map.cbegin();
	//	NS::map<std::string, std::string>::const_iterator end = map.cend();
	//	while (end != beg)
	//	{
	//		--end;
	//		std::cout << end->first << '\n';
	//	}
	//	std::cout << "----" << std::endl;
	//}

	//// reverse iterators
	//{
	//	std::cout << "-------" << std::endl;
	//	NS::map<std::string, std::string> map;
	//	map.insert(NS::pair<std::string, std::string>("k1", "v1"));
	//	map.insert(NS::pair<std::string, std::string>("k2", "v2"));
	//	map.insert(NS::pair<std::string, std::string>("k6", "v6"));
	//	map.insert(NS::pair<std::string, std::string>("k7", "v7"));
	//	printmap(map, "map");

	//	// map.m_tree.print();
	//	std::cout << "----" << std::endl;
	//	NS::map<std::string, std::string>::reverse_iterator rbeg = map.rbegin();
	//	NS::map<std::string, std::string>::reverse_iterator rend = map.rend();
	//	while (rbeg != rend)
	//	{
	//		std::cout << rbeg->first << '\n';
	//		++rbeg;
	//	}
	//	std::cout << "----" << std::endl;
	//}

	// // const reverse iterators
	// {
	// 	std::cout << "-------" << std::endl;
	// 	NS::map<std::string, std::string> map;
	// 	map.insert(NS::pair<std::string, std::string>("k1", "v1"));
	// 	map.insert(NS::pair<std::string, std::string>("k2", "v2"));
	// 	map.insert(NS::pair<std::string, std::string>("k3", "v3"));
	// 	printmap(map, "map");

	// 	// map.m_tree.print();
	// 	std::cout << "----" << std::endl;
	// 	NS::map<std::string, std::string>::const_reverse_iterator rbeg = map.rbegin();
	// 	//NS::map<std::string, std::string>::const_reverse_iterator rend = map.rend();
	// 	//while (rbeg != rend)
	// 	//{
	// 	//	std::cout << rbeg->first << '\n';
	// 	//	++rbeg;
	// 	//}
	// 	//std::cout << "----" << std::endl;
	// }

	{
		NS::map<std::string, std::string> mapaend;
		mapaend.insert(NS::pair<std::string, std::string>("k1", "v1"));
		// Esto tiene que dar un segfault
		//NS::map<std::string, std::string>::iterator itmapaend = mapaend.end();
		//std::cout << "Printing end() : " << itmapaend->first << std::endl;

		NS::map<std::string, std::string> mapa;
		NS::map<std::string, std::string>::iterator it1 = mapa.insert(NS::pair<std::string, std::string>("k1", "v1")).first;
		mapa.insert(it1, NS::pair<std::string, std::string>("k3", "v3"));
		NS::map<std::string, std::string>::iterator it2 = mapa.insert(NS::pair<std::string, std::string>("k2", "v2")).first;
		printmap(mapa, "mapa");
		NS::map<std::string,std::string> mapa2 = mapa;
		printmap(mapa2, "mapa2");
		log("erase k1 y k2");
		mapa.erase("k1");
		mapa.erase("k2");
		printmap(mapa, "mapa");
		log("insert mapa2 begin to end in mapa");
		mapa.insert(mapa2.begin(), mapa2.end());

		printmap(mapa, "mapa");
		printmap(mapa2, "mapa2");

		mapa2.erase(mapa2.begin(), mapa2.begin()++);
		std::cout << mapa.size() << std::endl;

		NS::map<std::string, std::string> mapa3(mapa2.begin(), mapa2.end());
		printmap(mapa3, "mapa3");

		NS::map<std::string, std::string> mapa4;
		printmap(mapa4, "mapa4 hola");

		NS::map<std::string, std::string>::iterator ite1 = mapa.insert(NS::pair<std::string, std::string>("e1", "e1")).first;
		NS::map<std::string, std::string>::iterator ite2 = mapa.insert(NS::pair<std::string, std::string>("e2", "e2")).first;
		mapa4.erase(ite1, ite2);
		printmap(mapa4, "mapa4");

		std::cout << "-------" << std::endl;
		NS::map<std::string, std::string>::iterator itebegin = mapa4.begin();
		NS::map<std::string, std::string>::iterator iteend = mapa4.end();
		for (NS::map<std::string, std::string>::iterator it = itebegin; it != iteend; it++)
			std::cout << it->first << std::endl;
		std::cout << "-------" << std::endl;

		//access
		std::cout << "-------" << std::endl;
		NS::map<std::string, std::string> access_map;
		access_map.insert(NS::pair<std::string, std::string>("acc1", "acc1"));
		access_map["acc1"];
		access_map["acc2"];
		
		std::cout << access_map["acc1"] << std::endl;
		std::cout << access_map["acc2"] << std::endl;
		std::cout << "-------" << std::endl;
		
		NS::map<std::string, std::string> endmap;
		endmap.insert(NS::pair<std::string, std::string>("em1", "em1"));
		NS::map<std::string, std::string>::iterator itembegin = endmap.begin();

		std::cout << (itembegin)->first << std::endl;

		itembegin--;
		itembegin--;

		std::cout << (itembegin)->first << std::endl;

		NS::map<std::string, std::string>::iterator itend = endmap.end();
		endmap.insert(NS::pair<std::string, std::string>("em2", "em2"));

		std::cout << (--itend)->first << std::endl;

		NS::map<std::string, std::string>::iterator itend2 = endmap.end();
		std::cout << (--itend2)->first << std::endl;
		std::cout << "-------" << std::endl;
		
		//clear
		std::cout << "-------" << std::endl;
		NS::map<std::string, std::string> clearmap;
		clearmap.insert(NS::pair<std::string, std::string>("cm1", "cm1"));
		clearmap.insert(NS::pair<std::string, std::string>("cm2", "cm2"));
		printmap(clearmap, "clear map");

		clearmap.clear();
		printmap(clearmap, "clear map");
		std::cout << "-------" << std::endl;

		//swap
		std::cout << "-------" << std::endl;
		NS::map<std::string, std::string> swapmapa;
		swapmapa.insert(NS::pair<std::string, std::string>("swa1", "swa1"));
		swapmapa.insert(NS::pair<std::string, std::string>("swa2", "swa2"));
		printmap(swapmapa, "swapmapa");
		NS::map<std::string, std::string> swapmapb;
		swapmapb.insert(NS::pair<std::string, std::string>("swb1", "swb1"));
		printmap(swapmapb, "swapmapb");

		swapmapa.swap(swapmapb);
		printmap(swapmapa, "swapmapa");
		printmap(swapmapb, "swapmapb");

		//size and maxsize
		std::cout << "-------" << std::endl;
		NS::map<std::string, std::string> sizemap;
		printmap(sizemap, "size map");
		sizemap.insert(NS::pair<std::string, std::string>("sm1", "sm1"));
		sizemap.insert(NS::pair<std::string, std::string>("sm2", "sm2"));
		sizemap.insert(NS::pair<std::string, std::string>("sm3", "sm3"));
		sizemap.insert(NS::pair<std::string, std::string>("sm4", "sm4"));
		printmap(sizemap, "size map");
		sizemap.erase("sm1");
		printmap(sizemap, "size map");
		sizemap.erase(sizemap.begin(), sizemap.end());
		printmap(sizemap, "size map");
		log("max size:");
		log(sizemap.max_size());
		std::cout << "-------" << std::endl;

		//key compare
		{
			std::cout << "-------" << std::endl;
			std::map<char, int> mymap;

			std::map<char, int>::key_compare mycomp = mymap.key_comp();

			mymap['a'] = 100;
			mymap['b'] = 200;
			mymap['c'] = 300;

			std::cout << "mymap contains:\n";

			char highest = mymap.rbegin()->first;     // key value of last element

			std::map<char, int>::iterator it = mymap.begin();
			do {
				std::cout << it->first << " => " << it->second << '\n';
			} while (mycomp((*it++).first, highest));

			std::cout << '\n';
			std::cout << "-------" << std::endl;
		}
		
		//value compare
		{
			NS::map<char, int> mymap;

			mymap['x'] = 1001;
			mymap['y'] = 2002;
			mymap['z'] = 3003;

			std::cout << "mymap contains:\n";

			NS::map<char, int>::iterator itend = mymap.end();
			itend--;
			NS::pair<char, int> highest = *itend;
			NS::map<char, int>::iterator it = mymap.begin();
			while (mymap.value_comp()(*it, highest))
			{
				std::cout << it->first << " => " << it->second << '\n';
				it++;
			}
		}

		//find
		{
			std::cout << "-------" << std::endl;
			NS::map<std::string, std::string> map;
			map.insert(NS::pair<std::string, std::string>("k1", "v1"));
			map.insert(NS::pair<std::string, std::string>("k2", "v2"));
			map.insert(NS::pair<std::string, std::string>("k3", "v3"));
			map.insert(NS::pair<std::string, std::string>("k4", "v4"));
			printmap(map, "map");
			NS::map<std::string, std::string>::iterator it;
			it = map.find("k3");
			std::cout << it->first << " => " << it->second << std::endl;
			it = map.find("k5");
			if (it == map.end())
				std::cout << "not found, iterator = end()" << std::endl;
			std::cout << "-------" << std::endl;
		}

		//count
		{
			std::cout << "-------" << std::endl;
			NS::map<std::string, std::string> map;
			map.insert(NS::pair<std::string, std::string>("k1", "v1"));
			map.insert(NS::pair<std::string, std::string>("k2", "v2"));
			printmap(map, "map");
			std::cout << "count k1 = " << map.count("k1") << std::endl;
			std::cout << "count k666 = " << map.count("k666") << std::endl;
			std::cout << "-------" << std::endl;
		}

		//bounds and equal_range
		{
			std::cout << "-------" << std::endl;
			NS::map<std::string, std::string> map;
			map.insert(NS::pair<std::string, std::string>("k1", "v1"));
			map.insert(NS::pair<std::string, std::string>("k2", "v2"));
			map.insert(NS::pair<std::string, std::string>("k6", "v6"));
			map.insert(NS::pair<std::string, std::string>("k7", "v7"));
			printmap(map, "map");

			NS::map<std::string, std::string>::iterator it;

			it = map.lower_bound("k1");
			std::cout << "lowerbound(k1) = " << it->first << std::endl;
			it = map.lower_bound("k0");
			std::cout << "lowerbound(k0) = " << it->first << std::endl;
			it = map.lower_bound("k4");
			std::cout << "lowerbound(k4) = " << it->first << std::endl;
			it = map.lower_bound("k7");
			std::cout << "lowerbound(k7) = " << it->first << std::endl;
			std::cout << "-------" << std::endl;

			it = map.upper_bound("k1");
			std::cout << "upperbound(k1) = " << it->first << std::endl;
			it = map.upper_bound("k0");
			std::cout << "upperbound(k0) = " << it->first << std::endl;
			it = map.upper_bound("k4");
			std::cout << "upperbound(k4) = " << it->first << std::endl;
			it = map.upper_bound("k7");

			if (it == map.end())
				std::cout << "equal" << std::endl;
			else
				std::cout << "upperbound(k7) = " << it->first << std::endl;
			// cit = map.lower_bound("k1");
			// std::cout << "const lowerbound(k1) = " << cit->first << std::endl;
			// cit = map.lower_bound("k0");
			// std::cout << "const lowerbound(k0) = " << cit->first << std::endl;
			// cit = map.lower_bound("k4");
			// std::cout << "const lowerbound(k4) = " << cit->first << std::endl;
			std::cout << "-------" << std::endl;

			NS::pair<NS::map<std::string, std::string>::iterator,NS::map<std::string, std::string>::iterator> range;
			range = map.equal_range("k2");
			std::cout << "equal_range(k2) = <" << range.first->first << ", " << range.second->first << ">" << std::endl;
			range = map.equal_range("k0");
			std::cout << "equal_range(k0) = <" << range.first->first << ", " << range.second->first << ">" << std::endl;
			range = map.equal_range("k5");
			std::cout << "equal_range(k5) = <" << range.first->first << ", " << range.second->first << ">" << std::endl;
			range = map.equal_range("k10");
			std::cout << "equal_range(k10) = <" << range.first->first << ", " << range.second->first << ">" << std::endl;
		}
	}

	return 0;
}