#include "tests.hpp"
#include "../containers/stack.hpp"
#include <stack>
#include <iomanip>

template <class T_STACK>
int	cmp(const T_STACK &lhs, const T_STACK &rhs)
{
	int res = 0;
	std::cout << "=============\n";
	std::cout << "eq: " << (lhs == rhs);
	res += (lhs == rhs); res = res << 1;
	std::cout << " | ne: " << (lhs != rhs) << std::endl;
	res += (lhs != rhs); res = res << 1;
	std::cout << "lt: " << (lhs < rhs);
	res += (lhs < rhs); res = res << 1;
	std::cout << " | le: " << (lhs <= rhs) << std::endl;
	res += (lhs <= rhs); res = res << 1;
	std::cout << "gt: " << (lhs >  rhs);
	res += (lhs > rhs); res = res << 1;
	std::cout << " | ge: " << (lhs >= rhs) << std::endl;
	res += (lhs >= rhs); res = res << 1;
	std::cout << "=============\n";
	std::cout << "res = " << res << "\n\n";
	return res;
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
	std::cout << std::endl;
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

	chapterend("DEFAULT COPY OK");
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

	chapterend("DEFAULT CONTAINER OK");
}

void s_relational_operators()
{
	chapter("\nRelational operators");
	NAMESPACE::stack<TYPE>::container_type	ctnr;

	int res;
	ctnr.push_back("1");
	ctnr.push_back("2");
	ctnr.push_back("3");

	NAMESPACE::stack<TYPE> stk1(ctnr);

	PrintStack(stk1, "stack1");
	title("Comparison to itself");
	logn("stack1 VS stack1");
	res = cmp(stk1, stk1);
	assert(res = 74);

	title("Comparison to an equal stack");
	NAMESPACE::stack<TYPE> stk2(ctnr);
	PrintStack(stk2, "stack2");
	logn("stack1 VS stack2");
	res = cmp(stk1, stk2);
	assert(res = 74);

	title("Comparison to a different stack");
	stk2.push("60");
	stk2.push("61");
	stk2.push("62");
	PrintStack(stk2, "stack2");
	logn("stack1 VS stack2");
	res = cmp(stk1, stk2);
	assert(res = 56);

	logn("stack2 VS stack1");
	cmp(stk2, stk1); 
	assert(res = 38);

	logn("Modifying stack1");
	stk1.push("42");
	PrintStack(stk1, "stack1");

	logn("stack1 VS stack2");
	res = cmp(stk1, stk2); 
	assert(res = 56);
	logn("stack2 VS stack1");
	res = cmp(stk2, stk1); 
	assert(res = 38);

	chapterend("RELATIONAL OPERATORS OK");
}

void stack_tests()
{
	chapter("\nT E S T I N G   S T A C K");
	s_default_container();
	s_default_copy();
	s_relational_operators();
}