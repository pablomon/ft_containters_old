#include "tests.hpp"
#include "../containers/stack.hpp"
#include <stack>
#include <iomanip>

template <class T_STACK>
void	cmp(const T_STACK &lhs, const T_STACK &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs);
	// std::cout << " | ne: " << (lhs != rhs) << std::endl;
	// std::cout << "lt: " << (lhs <  rhs) 
	// std::cout << " | le: " << (lhs <= rhs) << std::endl;
	// std::cout << "gt: " << (lhs >  rhs) 
	// std::cout << " | ge: " << (lhs >= rhs) << std::endl;
}

template <typename T>
void PrintStack(NAMESPACE::stack<T>& stk, std::string name = "s")
{
	std::cout << "  Stack " << name << ":\n";
	std::cout << "  empty = " << std::boolalpha << stk.empty() << ", ";
	std::cout << "size = " << stk.size();
	if (stk.size() > 0)
		std::cout << ", top = " << stk.top();
	std::cout << std::endl;

	NAMESPACE::stack<T> saveStack;
	while (stk.size() > 0)
	{
		saveStack.push(stk.top());
		stk.pop();
	}
	int i = 0;
	while (saveStack.size() > 0)
	{
		std::cout << "  [" << i << "] = " << saveStack.top() << std::endl;
		stk.push(saveStack.top());
		saveStack.pop();
		i++;
	}
}

void s_default_copy()
{
	chapter("\nDefault container copy");
	NAMESPACE::stack<TYPE>::container_type	ctnr;

	ctnr.push_back("21");
	ctnr.push_back("42");
	ctnr.push_back("1337");
	ctnr.push_back("19");
	ctnr.push_back("0");
	ctnr.push_back("183792");

	NAMESPACE::stack<TYPE> stk(ctnr);

	PrintStack(stk);

	std::cout << "\nAdding 6 elements" << std::endl;
	stk.push("1");
	stk.push("2");
	stk.push("3");
	stk.push("4");
	stk.push("5");
	stk.push("6");

	PrintStack(stk);
}

void s_default_container()
{
	chapter("\nDefault container basic operations");
	NAMESPACE::stack<TYPE> stk;

	PrintStack(stk);

	std::cout << "Adding 4 elements" << std::endl;
	stk.push("41");
	stk.push("29");
	stk.push("10");
	stk.push("42");

	PrintStack(stk);

	std::cout << "Removing 2 elements" << std::endl;
	stk.pop();
	stk.pop();

	PrintStack(stk);
}

void s_relational_operators()
{
	// NAMESPACE::stack<TYPE>::container_type	ctnr;

	// ctnr.push_back("21");
	// ctnr.push_back("42");
	// ctnr.push_back("1337");
	// ctnr.push_back("19");
	// ctnr.push_back("0");
	// ctnr.push_back("183792");

	// NAMESPACE::stack<TYPE> stck(ctnr);
	// NAMESPACE::stack<TYPE> stck2(ctnr);

	// bool res = stck == stck2 ? true : false;
	// std::cout << res << std::endl;
	// cmp(stck, stck);  // 0
	// cmp(stck, stck2); // 1

	// stck2.push("60");
	// stck2.push("61");
	// stck2.push("62");

	// cmp(stck, stck2); // 2
	// cmp(stck2, stck); // 3

	// stck.push("42");

	// cmp(stck, stck2); // 4
	// cmp(stck2, stck); // 5

	// stck.push("100");

	// cmp(stck, stck2); // 6
	// cmp(stck2, stck); // 7
}

void stack_tests()
{
	chapter("\nT E S T I N G   S T A C K");
	// default_container();
	// default_copy();
	s_relational_operators();
}