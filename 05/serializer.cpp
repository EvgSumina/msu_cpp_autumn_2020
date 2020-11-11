#include "serializer.h"

using namespace std;

Error Serializer::my_save(bool value)
{
	if (value)
		out_ << "true" << Separator;
	else
		out_ << "false" << Separator;

	return Error::NoError;
}

Error Serializer::my_save(uint64_t value)
{
	if (value == 0)
		out_ << "0" << Separator;
	else
	{
		string str = "";
		int sign;

		value > 0 ? sign = 1 : sign = -1;
		value *= sign;
		while (value > 0)
		{
			str = (char)(value % 10 + '0') + str;
			value /= 10;
		}
		if (sign == -1)
			str = '-' + str;
		out_ << str << Separator;
	}

	return Error::NoError;
}

Error Deserializer::my_load(bool& value)
{
	string text;
	in_ >> text;

	if (text == "true")
		value = true;
	else if (text == "false")
		value = false;
	else
		return Error::CorruptedArchive;

	return Error::NoError;
}

Error Deserializer::my_load(uint64_t& value)
{
	string text;
	in_ >> text;
	value = 0;

	for (size_t i = 0; i < text.size(); i++)
	{
		if (!isdigit(text[i]))
		{
			return Error::CorruptedArchive;
		}
		value = text[i] - '0' + 10 * value;
	}

	return Error::NoError;
}

