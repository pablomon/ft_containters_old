#include <iostream>
#include <assert.h>

#include "containers/vector.hpp"
#include <vector>
#include <typeinfo>
#include <time.h>
#include <sstream>


// logging
#define red "\033[0;31m"
#define green "\033[0;32m"
#define yellow "\033[0;33m"
#define blue "\033[0;36m"
#define reset "\033[0m"
#define log(x) std::cout << x
#define logn(x) std::cout << x << std::endl
#define title(x) std::cout << blue << "\n" << x << reset << std::endl
#define chapter(x) std::cout << yellow << x << reset << std::endl
#define chapterend(x) std::cout << green << x << reset << std::endl

#ifndef VECTOR
# define VECTOR ft::vector
#endif

#ifndef TYPE
# define TYPE std::string
#endif

template <typename T>
void PrintVector(const VECTOR<T>& vector, std::string name)
{
	std::cout << "  Vector " << name << ":\n";
	std::cout << "  size = " << vector.size() << ", ";
	std::cout << "capacity = " << vector.capacity() << std::endl;
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << "  [" << i << "] = " << vector[i] << std::endl;
}

void testConstructors()
{
	chapter("\nCONSTRUCTORS");
	{
		title("Empty constructor");
		VECTOR<TYPE> v = VECTOR<TYPE>();
		PrintVector(v, "v");
	}
	{
		title("Fill constructor");
		VECTOR<TYPE> v = VECTOR<TYPE>(4, "abc");
		assert(v[3] == "abc");
		PrintVector(v, "v");
	}
	{
		title("Range constructor");
		VECTOR<TYPE> vo = VECTOR<TYPE>();
		vo.push_back("11");
		vo.push_back("22");
		vo.push_back("33");
		PrintVector(vo, "vo");

		VECTOR<TYPE> v = VECTOR<TYPE>(vo.begin(), vo.end());
		assert(v[2] == "33");
		PrintVector(v, "v");
	}

	chapterend("CONSTRUCTORS OK");
}

void testAccess()
{
	chapter("\nELEMENT ACCESS");

	log("Create vector with values 1, 2, 3");
	VECTOR<TYPE> v;
	v.push_back("1");
	v.push_back("2");
	v.push_back("3");
	assert(v[2] == "3");
	PrintVector(v, "v");

	title("Operator []");
	log("Value at pos 2: ");
	assert(v[2] == "3");
	logn(v[2]);
	log("Value at pos 100: ");
	logn(v[100]);

	title("at");
	try
	{
		log("Value at pos 2: ");
		assert(v[2] == "3");
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
	assert(v.front() == "1");
	logn(v.front());
	log("Back: ");
	assert(v.back() == "3");
	logn(v.back());
	logn("Removng elements 1 and 2");
	v.pop_back();
	v.pop_back();
	log("Front: ");
	assert(v.front() == "1");
	logn(v.front());
	log("Back: ");
	assert(v.back() == "1");
	logn(v.back());

	chapterend("ACCESS OK");
}

void testModifiers()
{
	chapter("\nMODIFIERS");

	VECTOR<TYPE> v = VECTOR<TYPE>();
	PrintVector(v, "v");

	title("push_back");
	v.push_back("1");
	v.push_back("2");
	v.push_back("3");
	assert(v[2] == "3");
	PrintVector(v, "v");

	title("range assign");
	logn("create v2");
	VECTOR<TYPE> v2 = VECTOR<TYPE>(5, "42");
	PrintVector(v2, "v2");
	logn("assign v to v2");
	v2.assign(v.begin(), v.end());
	assert(v2[2] == "3");
	PrintVector(v2, "v2");
	title("fill assign");
	v2.assign(6, "42");
	assert(v2[5] == "42");
	PrintVector(v2, "v2");

	title("pop back");
	for (size_t i = 0; i < 6; i++)
	{
		logn(i);
		v2.pop_back();
	}
	PrintVector(v2, "v2");

	title("Insert single element");
	PrintVector(v, "v");
	logn("Insert 42 at the beginnig + 2");
	VECTOR<TYPE>::iterator it = v.insert(v.begin() + 2, "42");
	assert(v[2] == "42");
	logn(*it);
	logn("Insert 42 at the end");
	v.insert(v.end(), "42");
	assert(v[4] == "42");
	PrintVector(v, "v");

	title("Insert fill");
	logn("Insert  3 666s at the beginnig + 1");
	v.insert(++v.begin(), 3, "66");
	assert(v[1] == "66");
	assert(v[3] == "66");
	PrintVector(v, "v");

	title("Insert range");
	log("Vector3:");
	VECTOR<TYPE> v3;
	v3.push_back("10");
	v3.push_back("20");
	v3.push_back("30");
	PrintVector(v3, "v3");
	logn("Insert vector3 into second position");
	v.insert(v.begin() + 2, v3.begin(), v3.end());
	assert(v[2] == "10");
	assert(v[4] == "30");
	PrintVector(v, "v");

	title("Erase single");
	logn("Erase vector v pos 2");
	it = v.erase(v.begin() + 2);
	assert(*it == "20");
	log("return iterator value = ");
	logn(*it);
	PrintVector(v, "v");

	title("Erase range");
	logn("Erase everything in v except first and last");
	it = v.erase(++v.begin(), --v.end());
	assert(*it == "42");
	log("return iterator value = ");
	logn(*it);
	PrintVector(v, "v");

	title("Swap");
	logn("Vector v:");
	PrintVector(v, "v");
	logn("Vector v3:");
	PrintVector(v3, "v3");
	logn("Swap vectors");
	v.swap(v3);
	assert(v[2] == "30");
	assert(v3[1] == "42");
	PrintVector(v, "v");
	PrintVector(v3, "v3");

	title("\nClear");
	v.clear();
	assert(v.size() == 0);
	PrintVector(v, "v");

	chapterend("MODIFIERS OK");
}

void testCapacity()
{
	chapter("\nCAPACITY");
	VECTOR<TYPE> v = VECTOR<TYPE>();
	logn("hola");
	v.push_back("1");
	v.push_back("2");
	v.push_back("3");
	assert(v[2] == "3");
	PrintVector(v, "v");

	title("size");
	logn(v.size());

	title("max_size");
	logn(v.max_size());

	title("resize");
	logn("resize to 10 elements");
	v.resize(10);
	logn(v[9]);
	assert(v[9] == "");
	PrintVector(v, "v");
	logn("resize to 2 elements");
	v.resize(2);
	assert(v.size() == 2);
	PrintVector(v, "v");

	title("reserve");
	logn("reserve at least 15 elements");
	v.reserve(15);
	assert(v.capacity() >= 15);
	PrintVector(v, "v");
	chapterend("\nCAPACITY OK");
}

void testIterators()
{
	chapter("\nITERATORS");
	log("Create vector v with values 1, 2, 3");
	VECTOR<TYPE> v;
	v.push_back("a");
	v.push_back("b");
	v.push_back("c");
	assert(v[2] == "c");
	PrintVector(v, "v");

	title("begin");
	logn("Begin value:");
	logn(*v.begin());
	logn("Begin + 1 value:");
	logn(*(v.begin() + 1));

	title("end");
	logn("End - 1 value:");
	logn(*(v.end() - 1));
	logn("End - 2 value:");
	logn(*(v.end() - 2));

	title("rbegin");
	logn("rbegin value:");
	logn(*(v.rbegin()));
	logn("rbegin + 1 value:");
	logn(*(v.rbegin() + 1));

	title("rend");
	logn("rend - 1 value:");
	logn(*(v.rend() - 1));
	logn("rend - 2 value:");
	logn(*(v.rend() - 2));

	chapterend("ITERATORS OK");
}

template <typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

void speedTest()
{
# define TEST_SIZE 10000000
	chapter("\nSpeed test");
	title("Allocation");
	std::cout << "Create a vector with " << TEST_SIZE << " strings\n";
	clock_t t1, t2;
	{
		t1 = clock();
		std::vector<std::string> v;
		for (size_t i = 0; i < TEST_SIZE; i++)
			v.push_back(ToString(i));
		t2 = clock();
		log("std total s = ");
		logn((double)(t2 - t1) / CLOCKS_PER_SEC); 
	}

	{
		t1 = clock();
		ft::vector<std::string> v;
		for (size_t i = 0; i < TEST_SIZE; i++)
			v.push_back(ToString(i));
		t2 = clock();
		log("ft total s = ");
		logn((double)(t2 - t1) / CLOCKS_PER_SEC); 
	}

	title("Access");
	std::cout << "Acess " << TEST_SIZE << " strings\n";
	{
		std::string s;
		std::vector<std::string> v;
		for (size_t i = 0; i < TEST_SIZE; i++)
			v.push_back(ToString(i));
		t1 = clock();
		for (size_t i = 0; i < v.size(); i++)
			s = v[i];
		t2 = clock();
		log("std total s = ");
		logn((double)(t2 - t1) / CLOCKS_PER_SEC); 
	}
	{
		std::string s;
		std::vector<std::string> v;
		for (size_t i = 0; i < TEST_SIZE; i++)
			v.push_back(ToString(i));
		t1 = clock();
		for (size_t i = 0; i < v.size(); i++)
			s = v[i];
		t2 = clock();
		log("ft total s = ");
		logn((double)(t2 - t1) / CLOCKS_PER_SEC); 
	}
}

void vector_test()
{
	chapter("\nT E S T I N G   F T _ V E C T O R");
	// testConstructors();
	// testCapacity();
	// testAccess();
	// testModifiers();
	// testIterators();
	speedTest();
}

int main(void)
{
	vector_test();

	return 0;
}
