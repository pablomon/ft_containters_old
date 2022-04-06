#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <map>
#include <utility>

#include "avlTree.hpp"
#include "avlNode.hpp"
#include "avlIterator.hpp"

int main() {
   	int c, key;
   	AVLTree<int, int> avl;
	std::map<int,int> mapa;

	srand (time(NULL));
	int size = 15;
	int keys[size];
	std::vector<int> nonrepkeys;
	while (nonrepkeys.size() != size)
	{
		int k = rand() % 99;
		bool exists = false;
		for (size_t i = 0; i < nonrepkeys.size(); i++)
		{
			if (nonrepkeys[i] == k)
				exists = true;
		}
		if (!exists)
		{
			nonrepkeys.push_back(k);
			avl.insert(ft::make_pair<int,int>(k, k+1));
			mapa.insert(std::pair<int,int>(k, k+1));
		}
	}

	// for (size_t i = 0; i < 10; i++)
	// {
	// 	avl.insert(ft::make_pair<int,int>(i, i+1));
	// }
	

	avl.print();

/* map */
	// mapa.insert(std::pair<int, int>(10, 12));
	// mapa.insert(std::pair<int, int>(30, 3));
	// mapa.insert(std::pair<int, int>(5, 30));
	// mapa.insert(std::pair<int, int>(40, 22));
	// mapa.insert(std::pair<int, int>(60, 2));

	// std::map<int, int>::iterator it = mapa.begin();

	// std::cout << "end first: " << it->first << std::endl;

	// while (it != mapa.end())
	// {
	// 	std::cout << it->first << std::endl;
	// 	it++;
	// }

    // // Iterate over the map using Iterator till end.
	// it = mapa.begin();
	// for (size_t i = 0; i < 10; i++)
	// {
    //     std::cout << it->first << " :: " << it->second << std::endl;
    //     it++;
	// }
	// std::cout << std::endl;
	
	// mapa.erase(30);

	// it = mapa.end();
	// std::cout << it->first << std::endl;
	// it ++;
	// std::cout << it->first << std::endl;
	// it ++;
	// std::cout << it->first << std::endl;
	// it ++;
	// std::cout << it->first << std::endl;
	// it ++;
	

/* map iterator */
	std::map<int,int>::iterator map_it = mapa.end();
	std::cout << "end = " << map_it->first << std::endl;
	map_it = mapa.begin();
	std::cout << "begin = " << map_it->first << std::endl;
	map_it--;
	std::cout << "begin-- = " << map_it->first << std::endl;
	map_it++;
	std::cout << "begin++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "begin++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "begin++ = " << map_it->first << std::endl;
	map_it--;
	std::cout << "begin-- = " << map_it->first << std::endl;
	map_it--;
	std::cout << "begin-- = " << map_it->first << std::endl;
	map_it--;
	std::cout << "begin-- = " << map_it->first << std::endl;
	map_it--;
	std::cout << "begin-- = " << map_it->first << std::endl;
	map_it--;
	std::cout << "begin-- = " << map_it->first << std::endl;
	map_it = mapa.begin();
	while (map_it != mapa.end())
	{
		std::cout << map_it->first << std::endl;
		map_it++;
	}
	map_it = mapa.end();
	map_it++;
	std::cout << "end++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "end++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "end++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "end++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "end++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "end++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "end++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "end++ = " << map_it->first << std::endl;
	map_it++;
	std::cout << "end++ = " << map_it->first << std::endl;
	map_it--;
	std::cout << "end-- = " << map_it->first << std::endl;
	std::cout << "end = " << map_it->first << std::endl;	
	while (map_it != mapa.begin())
	{
		std::cout << map_it->first << std::endl;
		map_it--;
	}

/* mi iterator */
std::cout << "---------------\n";
	
	AVLTree<int,int>::iterator it = avl.end();
	std::cout << "end = " << it->first << std::endl;
	it = avl.begin();
	std::cout << "begin = " << it->first << std::endl;
	it--;
	std::cout << "begin-- = " << it->first << std::endl;
	it++;
	std::cout << "begin++ = " << it->first << std::endl;
	it++;
	std::cout << "begin++ = " << it->first << std::endl;
	it++;
	std::cout << "begin++ = " << it->first << std::endl;
	it--;
	std::cout << "begin-- = " << it->first << std::endl;
	it--;
	std::cout << "begin-- = " << it->first << std::endl;
	it--;
	std::cout << "begin-- = " << it->first << std::endl;
	it--;
	std::cout << "begin-- = " << it->first << std::endl;
	it--;
	std::cout << "begin-- = " << it->first << std::endl;
	it = avl.begin();
	while (it != avl.end())
	{
		std::cout << it->first << std::endl;
		it++;
	}
	it = avl.end();
	it++;
	std::cout << "end++ = " << it->first << std::endl;
	it++;
	std::cout << "end++ = " << it->first << std::endl;
	it++;
	std::cout << "end++ = " << it->first << std::endl;
	it++;
	std::cout << "end++ = " << it->first << std::endl;
	it++;
	std::cout << "end++ = " << it->first << std::endl;
	it++;
	std::cout << "end++ = " << it->first << std::endl;
	it++;
	std::cout << "end++ = " << it->first << std::endl;
	it++;
	std::cout << "end++ = " << it->first << std::endl;
	it++;
	std::cout << "end++ = " << it->first << std::endl;
	it--;
	std::cout << "end-- = " << it->first << std::endl;
	std::cout << "end = " << it->first << std::endl;	
	while (it != avl.begin())
	{
		std::cout << it->first << std::endl;
		it--;
	}


std::cout << "---------------\n";
	
	it = avl.end();
	std::cout << "end = " << avl.end()->first << std::endl;
	it = avl.begin();
	it--;
	std::cout << "begin-- = " << it->first << std::endl;
	it = avl.begin();
	while (it != avl.end())
	{
		std::cout << it->first << std::endl;
		it++;
	}
	std::cout << "----\n";
	it++;
	it++;
	it--;
	it--;
	it--;
	std::cout << "> "  << it->first << std::endl;
	it = avl.end();
	std::cout << "end = " << avl.end()->first << std::endl;
	while (it != avl.begin())
	{
		std::cout << it->first << std::endl;
		it--;
	}

   	return 0;
}