#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <vector>

#include "avlTree.hpp"
#include "avlNode.hpp"

int main() {
   	int c, key;
   	AVLTree<int, int> avl;

	srand (time(NULL));
	int keys[20];
	std::vector<int> nonrepkeys;
	while (nonrepkeys.size() != 20)
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
			avl.insert(k, k + 1);
		}
	}

	avl.print();
   	while (1) {
	   	std::cout << "\n";
		std::cout << "1.Insert Element into the tree" << std::endl;
		std::cout << "2.print Balanced AVL Tree" << std::endl;
		std::cout << "3.search" << std::endl;
		std::cout << "4.delete" << std::endl;
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
				avl.insert(key, v);
				avl.print();		
			}
			break;
			case 2:
				// if (root == NULL) {
				// std::cout << "Tree is Empty" << std::endl;
				// continue;
				// }
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

			// case 3:
			// 	std::cout << "Inorder Traversal:" << std::endl;
			// 	avl.inorder(r);
			// 	std::cout << std::endl;
			// break;
			// case 4:
			// 	std::cout << "Preorder Traversal:" << std::endl;
			// 	avl.preorder(r);
			// 	std::cout << std::endl;
			// break;
			// case 5:
			// 	std::cout << "Postorder Traversal:" << std::endl;
			// 	avl.postorder(r);
			// 	std::cout << std::endl;
			// break;
			// case 6:
			// 	exit(1);
			// case 7:
			// 	AVLTree::print(r);
			default:
				std::cout << "Wrong Choice" << std::endl;
		}	
	}			
   	return 0;
}