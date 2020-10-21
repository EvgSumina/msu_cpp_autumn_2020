#include <iostream>
#include <string>
#include <functional>
#include "parser.h"

using namespace std;


string TestNum(int num)
{
	return to_string(num);
}


string TestStr(const string & str)
{
	return str;
}   


string TestStart()
{
	return "Start ";
}


string TestFinish()
{
	return " Finish";
}


string TestConStr(const string & str)
{
	return str + str;
}

void Test_1()
{
	TokenParser FirstParser;
	FirstParser.setStartCallback(TestStart);
	FirstParser.setFinishCallback(TestFinish);
	FirstParser.setNumCallback(TestNum);
	FirstParser.setStrCallback(TestStr);
	string s = "hello 1010friend\t777  \r\ni am parser";
	if (FirstParser.parse(s) != "Start hello1010friend777iamparser Finish")
	{
	throw -1;
	}
}
	

void Test_2()
{
	TokenParser SecondParser = TokenParser(TestNum, TestStr, TestStart, TestFinish);
	string s = "  ";
	if (SecondParser.parse(s) != "Start  Finish")
	{
		throw -1;
	}
}


void Test_3()
{
	TokenParser ThirdParser;
	string s = "456 df 345 aa ";
	if (ThirdParser.parse(s) != "")
	{
		throw -1;
	}
}

int main(int argc, char* argv[])
{
	Test_1();
	Test_2();
	Test_3();
	cout << "Success!" << endl;
	return 0;
}
