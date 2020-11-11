#pragma once
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

enum class Error
{
	NoError,
	CorruptedArchive
};


class Serializer
{
	static constexpr char Separator = ' ';
	ostream& out_;
public:
	explicit Serializer(ostream& out)
		: out_(out)
	{
	}
	
	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(forward<ArgsT>(args)...);
	}

private:
	Error my_save(bool);
	Error my_save(uint64_t);

	template <class T>
	Error my_save(T)
	{
		return Error::CorruptedArchive;
	}
	
	template <class T, class... Args>
	Error process(T&& value, Args&&... args)
	{
		if (my_save(value) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		return process(forward<Args>(args)...);
	}
	
	template <class T>
	Error process(T&& value)
	{
		return my_save(value);
	}
};


class Deserializer
{
	static constexpr char Separator = ' ';
	istream& in_;
public:
	explicit Deserializer(istream& in)
		: in_(in)
	{
	}
	
	template <class T>
	Error load(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(forward<ArgsT>(args)...);
	}

private:
	Error my_load(bool&);
	Error my_load(uint64_t&);

	template <class T>
	Error my_load(T&)
	{
		return Error::CorruptedArchive;
	}

	template <class T, class... Args>
	Error process(T&& value, Args&&... args)
	{
		if (my_load(value) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		return process(forward<Args>(args)...);
	}

	template <class T>
	Error process(T&& value)
	{
		return my_load(value);
	}
};
