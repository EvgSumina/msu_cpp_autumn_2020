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
	out_ << value << Separator;

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

	try
	{
		value = stoull(text);
	}
	catch(const logic_error& e)
	{
		return Error::CorruptedArchive;
	}
	return Error::NoError;
}

