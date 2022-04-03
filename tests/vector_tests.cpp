#include "tests.hpp"
#include "../containers/vector.hpp"
// #include "../Vector.hpp"
#include <vector>

template <class T, class Alloc>
void	cmp(const NAMESPACE::vector<T, Alloc> &lhs, const NAMESPACE::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs);
	std::cout << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs < rhs);
	// std::cout << " | le: " << (lhs <= rhs) << std::endl;
	// std::cout << "gt: " << (lhs >  rhs);
	// std::cout << " | ge: " << (lhs >= rhs) << std::endl;
}

template <typename T>
void PrintVector(const NAMESPACE::vector<T>& vector, std::string name)
{
	std::cout << "  Vector " << name << ":\n";
	std::cout << "  size = " << vector.size() << ", ";
	std::cout << "capacity = " << vector.capacity() << std::endl;
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << "  [" << i << "] = " << vector[i] << std::endl;
}

void v_testConstructors()
{
	chapter("\nCONSTRUCTORS");
	{
		title("Empty constructor");
		NAMESPACE::vector<TYPE> v = NAMESPACE::vector<TYPE>();
		PrintVector(v, "v");
	}
	{
		title("Fill constructor");
		NAMESPACE::vector<TYPE> v = NAMESPACE::vector<TYPE>(4, "abc");
		assert(v[3] == "abc");
		PrintVector(v, "v");
	}
	{
		title("Range constructor");
		NAMESPACE::vector<TYPE> vo = NAMESPACE::vector<TYPE>();
		vo.push_back("11");
		vo.push_back("22");
		vo.push_back("33");
		PrintVector(vo, "vo");

		NAMESPACE::vector<TYPE> v = NAMESPACE::vector<TYPE>(vo.begin(), vo.end());
		assert(v[2] == "33");
		PrintVector(v, "v");
	}

	chapterend("CONSTRUCTORS OK");
}

void v_testAccess()
{
	chapter("\nELEMENT ACCESS");

	log("Create vector with values 1, 2, 3");
	NAMESPACE::vector<TYPE> v;
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

void v_testModifiers()
{
	chapter("\nMODIFIERS");

	NAMESPACE::vector<TYPE> v = NAMESPACE::vector<TYPE>();
	PrintVector(v, "v");

	title("push_back");
	v.push_back("1");
	v.push_back("2");
	v.push_back("3");
	assert(v[2] == "3");
	PrintVector(v, "v");

	title("range assign");
	logn("create v2");
	NAMESPACE::vector<TYPE> v2 = NAMESPACE::vector<TYPE>(5, "42");
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
	NAMESPACE::vector<TYPE>::iterator it = v.insert(v.begin() + 2, "42");
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
	NAMESPACE::vector<TYPE> v3;
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

void v_testCapacity()
{
	chapter("\nCAPACITY");
	NAMESPACE::vector<TYPE> v = NAMESPACE::vector<TYPE>();
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

void v_testIterators()
{
	chapter("\nITERATORS");
	log("Create vector v with values 1, 2, 3");
	NAMESPACE::vector<TYPE> v;
	v.push_back("a");
	v.push_back("b");
	v.push_back("c");
	assert(v[2] == "c");
	PrintVector(v, "v");

	title("begin");
	logn("Begin value:");
	NAMESPACE::vector<TYPE>::iterator it = v.begin();
	logn(*it);
	assert(*it == "a");
	logn("Begin + 1 value:");
	assert(*(v.begin() + 1) == "b");
	logn(*(v.begin() + 1));
	
	title("end");
	logn("End - 1 value:");
	assert(*(v.end() - 1) == "c");
	logn(*(v.end() - 1));
	logn("End - 2 value:");
	assert(*(v.end() - 2) == "b");
	logn(*(v.end() - 2));

	title("rbegin");
	logn("rbegin value:");
	assert(*(v.rbegin()) == "c");
	logn(*(v.rbegin()));
	logn("rbegin + 1 value:");
	logn(*(v.rbegin() + 1));
	assert(*(v.rbegin() + 1) == "b");

	title("rend");
	logn("rend - 1 value:");
	assert(*(v.rend() - 1) == "a");
	logn(*(v.rend() - 1));
	logn("rend - 2 value:");
	assert(*(v.rend() - 2) == "b");
	logn(*(v.rend() - 2));

	chapterend("ITERATORS OK");
}

void v_relational_operators()
{
	NAMESPACE::vector<TYPE> vct(4);
	NAMESPACE::vector<TYPE> vct2(4);

	cmp(vct, vct);  // 0
	cmp(vct, vct2); // 1

	vct2.resize(10);

	cmp(vct, vct2); // 2
	cmp(vct2, vct); // 3

	vct[2] = 42;

	cmp(vct, vct2); // 4
	cmp(vct2, vct); // 5

	swap(vct, vct2);

	cmp(vct, vct2); // 6
	cmp(vct2, vct); // 7	
}

void v_speedTest()	
{
# define TEST_SIZE 10000000
	chapter("\nSpeed test");
	title("Allocation");
	std::cout << "Create a vector with " << TEST_SIZE << " strings\n";
	NAMESPACE::vector<std::string> v;
	Timer();
	for (size_t i = 0; i < TEST_SIZE; i++)
		v.push_back(ToString(i));
	log("total s = ");
	logn(Timer());

	title("Access");
	std::cout << "Acess " << TEST_SIZE << " strings\n";
	std::string s;
	Timer();
	for (size_t i = 0; i < v.size(); i++)
		s = v[i];
	log("total s = ");
	logn(Timer()); 
}

void vector_tests()
{
	chapter("\nT E S T I N G   V E C T O R");
	// v_testConstructors();
	// v_testCapacity();
	// v_testAccess();
	// v_testModifiers();
	// v_testIterators();
	v_relational_operators();
	// v_speedTest();
}