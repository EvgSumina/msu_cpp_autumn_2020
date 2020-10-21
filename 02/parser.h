#include <iostream>
#include <functional>
#pragma once

using namespace std;

using IfNum = function<string (int)>;
using IfStr = function<string (const string &)>;
using limits = function<string ()>;

class TokenParser
{
	IfNum CallNum; 
	IfStr CallStr; 
	limits start;
	limits finish;
public:
	TokenParser();
	TokenParser(const IfNum &, const IfStr &, const limits &, const limits &);
	void setNumCallback (const IfNum &);
	void setStrCallback (const IfStr &);
	void setStartCallback (const limits &);
	void setFinishCallback (const limits &);
	string register_token(const string & token);
	string parse (const string & text);
};
