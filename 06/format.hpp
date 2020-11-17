#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <exception> 
#include <iostream>


template <class T>
std::string to_str(T&& val)
{
	std::stringstream str;
	str << val;
	return str.str();
}


template <class ... Args>
std::string format(const std::string& str, Args&& ... args)
{
	std::vector<std::string> args_vect = {to_str(std::forward<Args>(args)) ...};
	std::string result, buf;
	size_t str_len = str.size();
	size_t arg_len = args_vect.size();
	bool open_paren = false;
	bool closed_paren = true;
	char c;

	for (size_t i = 0; i < str_len; i++)
	{
		c = str[i];
		if (closed_paren)
		{
			if (c == '{')
			{
				open_paren = true;
				closed_paren = false;
			}
			else if (c == '}')
			{
				throw std::logic_error("Closing parenthesis error");
			}
			else
			{
				result += str[i];
			}
		}
		else if(open_paren)
		{
			if (std::isdigit(c))
			{
				buf += c;
			}
			else if (c == '}')
			{
				if (buf.empty())
				{
					throw std::logic_error("No argument error");
				}
				else if (std::stoi(buf) >= arg_len || std::stoi(buf) < 0)
				{
					throw std::logic_error("Too many arguments");
				}
				else
				{
					open_paren = false;
					closed_paren = true;
					result += args_vect[std::stoi(buf)];
					buf.clear();
				}
			}
			else
			{
				throw std::logic_error("Wrong argument type");
			}
		}
	}
	if (open_paren)
	{
		throw std::logic_error("No closing parenthesis error");
	}
	return result;
}

