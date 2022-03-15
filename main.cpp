#include <iostream>
#include <assert.h>

#include "vector.hpp"

// logging
#define red "\033[0;31m"
#define green "\033[0;32m"
#define yellow "\033[0;33m"
#define blue "\033[0;36m"
#define reset "\033[0m"
#define log(x) std::cout << x
#define logn(x) std::cout << x << std::endl
#define title(x) std::cout << blue << x << reset << std::endl
#define chapter(x) std::cout << yellow << x << reset << std::endl
#define chapterend(x) std::cout << green << x << reset << std::endl

#define VECTOR ft::vector

template <typename T>
void PrintVector(const VECTOR<T>& vector)
{
	std::cout << "\n***Vector contents***" << std::endl;
	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cout << "[" << i << "] = " << vector[i] << std::endl;
	}
	std::cout << "*********************" << std::endl;
}

void testConstructors()
{
	chapter("\nCONSTRUCTORS");
	{
		title("Empty constructor");
		VECTOR<int> v = VECTOR<int>();
		PrintVector(v);
	}
	{
		title("Fill constructor");
		VECTOR<int> v = VECTOR<int>(4, 6);
		assert(v[3] == 6);
		PrintVector(v);
	}
	{
		title("Range constructor");
		VECTOR<int> vo = VECTOR<int>();
		vo.push_back(11);
		vo.push_back(22);
		vo.push_back(33);
		VECTOR<int> v = VECTOR<int>(vo.begin(), vo.end());
		assert(v[2] == 33);
		PrintVector(v);
	}

	chapterend("CONSTRUCTORS OK");
}

void testAccess()
{
	chapter("\nELEMENT ACCESS");

	log("Create vector with values 1, 2, 3");
	VECTOR<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	assert(v[2] == 3);
	PrintVector(v);

	title("Operator []");
	log("Value at pos 2: ");
	assert(v[2] == 3);
	logn(v[2]);
	log("Value at pos 100: ");
	logn(v[100]);

	title("at");
	try
	{
		log("Value at pos 2: ");
		assert(v[2] == 3);
		logn(v.at(2));
		log("Value at pos 100: ");
		logn(v.at(100));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	title("Front & back");
	log("Front: ");
	assert(v.front() == 1);
	logn(v.front());
	log("Back: ");
	assert(v.back() == 3);
	logn(v.back());
	logn("Removng elements 1 and 2");
	v.pop_back();
	v.pop_back();
	log("Front: ");
	assert(v.front() == 1);
	logn(v.front());
	log("Back: ");
	assert(v.back() == 1);
	logn(v.back());

	chapterend("ACCESS OK");
}

void testModifiers()
{
	chapter("\nMODIFIERS");

	VECTOR<int> v = VECTOR<int>();
	PrintVector(v);

	title("push_back");
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	assert(v[2] == 3);
	PrintVector(v);

	title("range assign");
	logn("create v2");
	VECTOR<int> v2 = VECTOR<int>(5, 42);
	PrintVector(v2);
	logn("assign v to v2");
	v2.assign(v.begin(), v.end());
	assert(v2[2] == 3);
	PrintVector(v2);
	title("fill assign");
	v2.assign(6, 42);
	assert(v2[5] == 42);
	PrintVector(v2);

	title("pop back");
	for (size_t i = 0; i < 6; i++)
	{
		v2.pop_back();
	}
	PrintVector(v2);
	
	title("Insert single element");
	PrintVector(v);
	logn("Insert 42 at the beginnig");
	ft::vector<int>::iterator it = v.begin();
	v.insert(it, 42);
	assert(v[0] == 42);
	PrintVector(v);

	title("Erase");
	title("Swap");

	title("\nClear");
	v.clear();
	assert(v.size() == 0);
	PrintVector(v);

	chapterend("MODIFIERS OK");
}

void testIterators()
{
	chapter("\nITERATORS");

	chapterend("ITERATORS OK");
}

int main(void)
{
	chapter("\nT E S T I N G   F T _ V E C T O R");
	testConstructors();
	testAccess();
	testModifiers();
	testIterators();

	return 0;
}