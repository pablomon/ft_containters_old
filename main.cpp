#include <iostream>

#include "vector.hpp"

#define logn(x) std::cout << x << std::endl
#define log(x) std::cout << x

int main(void)
{
	logn("Vector tests");
	logn("\nTest empty constructor:");
	vector<int> v = vector<int>();

	logn("\nTest push_back:");
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	PrintVector(v);

	{
		logn("\nTest copy constructor:");
		vector<int> v2 = v;
		PrintVector(v2);

		logn("\nTest destructor:");
	}

	logn("\ntest operator[]:");
	log("Value at pos 2: ");
	logn(v[2]);
	log("Value at pos 100: ");
	logn(v[100]);

	logn("\ntest at:");
	try
	{
		log("Value at pos 2: ");
		logn(v.at(2));
		log("Value at pos 100: ");
		logn(v.at(100));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	logn("\nTest pop_back:");
	v.pop_back();
	v.pop_back();
	PrintVector(v);

	logn("\nFront & back test:");
	log("Front: ");
	logn(v.front());
	log("Back: ");
	logn(v.back());
	logn("Adding elements 2 and 3");
	v.push_back(2);
	v.push_back(3);
	log("Front: ");
	logn(v.front());
	log("Back: ");
	logn(v.back());

	
}