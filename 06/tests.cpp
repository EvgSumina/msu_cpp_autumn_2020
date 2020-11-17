#include "format.hpp"
#include <cassert>
#include <iostream>

int main()
{
	const std::string p = "{1} + {1} = {0}";
	std::cout << format(p, 2, "one") << std::endl;
	auto text = format("{1} + {1} = {0}", 2, "one");
	assert(text == "one + one = 2");

	bool error = false;
	try
	{
		text = format("12} {0}", 1, 2);
	}
	catch(const ParenthesisError& e)
	{
		error = true;
	}
	assert(error == true);

	error = false;
	try
	{
		text = format("{}", 1, 2);
	}
	catch(const CountArgumentError& e)
	{
		error = true;
	}
	assert(error == true);

	error = false;
	try
	{
		text = format("1 + 2 = {3}", 1, 2, 3);
	}
	catch(const CountArgumentError& e)
	{
		error = true;
	}
	assert(error == true);

	error = false;
	try
	{
		text = format("{abs{0}", 1, 2);
	}
	catch(const WrongArgumentError& e)
	{
		error = true;
	}
	assert(error == true);

	error = false;
	try
	{
		text = format("{0}{", 1, 2);
	}
	catch(const ParenthesisError& e)
	{
		error = true;
	}
	assert(error == true);
	
	std::cout << "Success" << std::endl;
	return 0;
}
