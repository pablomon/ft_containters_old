#if !defined(UTILS_HPP)
#define UTILS_HPP

#include <string>
#include <sstream>
#include <iostream>

// logging
#define red "\033[0;31m"
#define green "\033[0;32m"
#define yellow "\033[0;33m"
#define blue "\033[0;36m"
#define defcolor "\033[0m"
#define log(x) std::cout << x
#define logn(x) std::cout << x << std::endl
#define title(x) std::cout << blue << "\n" << x << defcolor << std::endl
#define chapter(x) std::cout << yellow << x << defcolor << std::endl
#define chapterend(x) std::cout << green << x << defcolor << std::endl

template<class T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

double Timer();

#endif // UTILS_HPP
