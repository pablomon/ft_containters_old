#if !defined(TESTS_HPP)
#define TESTS_HPP

#include <iostream>
#include <assert.h>
#include <time.h>
#include "../utils/utils.hpp"

// types
#ifndef STD
# define VECTOR ft::vector
# define STACK ft::stack
#else
# define VECTOR std::vector
# define STACK std::stack
#endif

#ifndef TYPE
# define TYPE std::string
#endif

void vector_tests();
void stack_tests();

#endif // TESTS_HPP