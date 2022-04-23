#if !defined(TESTS_HPP)
#define TESTS_HPP

#include <iostream>
#include <assert.h>
#include <time.h>
#include "../utils/utils.hpp"

// types
#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

#ifndef TYPE
# define TYPE std::string
#endif

void vector_tests();
void stack_tests();
void map_tests();

#endif // TESTS_HPP