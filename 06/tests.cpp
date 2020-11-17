#include "format.hpp"
#include <cassert>
#include <iostream>

int main()
{
	const std::string p = "{1} + {1} = {0}";
	std::cout << format(p, 2, "one") << std::endl;
	auto text = format("{1} + {1} = {0}", 2, "one");
	assert(text == "one + one = 2");

	try
	{
		text = format("12} {0}", 1, 2);
	}
	catch(const std::logic_error& e)
	{
		std::stringstream str;
		str << e.what();
		assert(str.str() == "Closing parenthesis error");
	}

	try
	{
		text = format("{}", 1, 2);
	}
	catch(const std::logic_error& e)
	{
		std::stringstream str;
		str << e.what();
		assert(str.str() == "No argument error");
	}

	try
	{
		text = format("1 + 2 = {3}", 1, 2, 3);
	}
	catch(const std::logic_error& e)
	{
		std::stringstream str;
		str << e.what();
		assert(str.str() == "Too many arguments");
	}

	try
	{
		text = format("{abs{0}", 1, 2);
	}
	catch(const std::logic_error& e)
	{
		std::stringstream str;
		str << e.what();
		assert(str.str() == "Wrong argument type");
	}

	try
	{
		text = format("{0}{", 1, 2);
	}
	catch(const std::logic_error& e)
	{
		std::stringstream str;
		str << e.what();
		assert(str.str() == "No closing parenthesis error");
	}
	
	std::cout << "Success" << std::endl;
	return 0;
}
