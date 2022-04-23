#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <vector>

#include "avlTree.hpp"
#include "avlNode.hpp"

int main() {
   	int c, key;
   	ft::avlTree<int, int> avl;

	int size = 7;
	srand (time(NULL));
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
			ft::pair<int,int> pair;
			pair.first = k;
			pair.second = k + 1;
			avl.insert(pair);
		}
	}

	avl.print();
   	while (1) {
	   	std::cout << "\n";
		std::cout << "1.Insert Element into the tree" << std::endl;
		std::cout << "2.print Balanced AVL Tree" << std::endl;
		std::cout << "3.search" << std::endl;
		std::cout << "4.delete" << std::endl;
		std::cout << "5.get begin" << std::endl;
		std::cout << "Enter your Choice: ";
		std::cin >> c;
		switch (c) {
			case 1:
			{
				std::cout << "Enter key: ";
				std::cin >> key;
				int v;
				std::cout << "Enter value:";
				std::cin >> v;

				ft::pair<int,int> pair;
				pair.first = key;
				pair.second = v;
				avl.insert(pair);
				avl.print();		
			}
			break;
			case 2:
				std::cout << "Balanced AVL Tree:" << std::endl;
				avl.print();		
				std::cout<<std::endl;
			break;
			case 3:
			{
				std::cout << "Enter key to search for: " << std::endl;
				std::cin >> key;
				int val = avl.getValue(key);

				std::cout << val;
			}
			break;
			case 4:
			{
				std::cout << "Enter key to delete: " << std::endl;
				std::cin >> key;
				bool res = avl.remove(key);
				if (!res)
					std::cout << "Not found." << std::endl;
				else
				{
					std::cout << "Deleted" << std::endl;
					avl.print();		
				}
			}
			break;
			// case 5:
			// {
			// 	avlNode<int,int> *n = avl.getInOrderBegin();
			// 	std::cout << "Begin key = " << n->getPair().first << std::endl;
			// }
			// break;
			default:
				std::cout << "Wrong Choice" << std::endl;
		}	
	}			
   	return 0;
}