#include <iostream>
#include <functional>
#include "parser.h"

using namespace std;


TokenParser::TokenParser()
{
    start = nullptr;
    finish = nullptr;
    CallNum = nullptr;
    CallStr = nullptr;
}


TokenParser::TokenParser(const IfNum & CallNum, const IfStr & CallStr, const limits & start, const limits & finish): CallNum(CallNum), CallStr(CallStr), start(start), finish(finish) {}

void TokenParser::setNumCallback (const IfNum & function)
{
	CallNum = function;
}

void TokenParser::setStrCallback (const IfStr & function)
{
	CallStr = function;
}

void TokenParser::setStartCallback (const limits & function)
{
	start = function;
}

void TokenParser::setFinishCallback (const limits & function)
{
	finish = function;
}

string TokenParser::register_token(const string & token)
{
	if (token != "")
	{
		bool flag = true;
		for (unsigned int i = 0; i < token.length(); i++)
			flag = isdigit(token[i]);
		
		if (CallNum && flag) 
		{
			return CallNum(stoi(token));
		}
		if (CallStr) 
		{
			return CallStr(token);
		}
	}
	return token;
}

string TokenParser::parse(const string& text) 
{
	string result = "";
	if (start != nullptr)
	{
		 result += start();
	}
	else
	{
		return result;
	}
	string token = "";
	unsigned int i = 0;
	while (i < text.length())
	{
		if (!isspace(text[i]))
		{
			token += text[i];
		}
		else
		{
			result += register_token(token);
			token = "";
		}
		i++;
	}
	result += register_token(token);
	if (finish != nullptr)
	{
		result += finish();
	}
	else
	{
		return "";
	}
	return result;
}

