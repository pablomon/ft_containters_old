#include <iostream>
#include "containers/vector.hpp"
#include <vector>
#include <assert.h>
#include <time.h>
#include "utils/utils.hpp"

#define NS std

template <typename T>
void PrintVector(const NS::vector<T>& vector, std::string name)
{
	std::cout << "  Vector " << name << ":\n";
	std::cout << "  size = " << vector.size() << ", ";
	std::cout << "capacity = " << vector.capacity() << std::endl;
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << "  [" << i << "] = " << vector[i] << std::endl;
}

int main()
{
	log("- Const iterators -");
	{
		log("Create vector v with values 1, 2, 3");
		NS::vector<int>v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);

		title("begin");
		logn("Begin value:");
		NS::vector<int>::const_iterator it = v.begin();
		logn(*it);
		assert(*it == 1);
		logn("Begin + 1 value:");
		assert(*(it + 1) == 2);
		logn(*(it + 1));
	}

	return 0;
}
