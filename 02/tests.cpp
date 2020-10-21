#include <iostream>
#include <string>
#include <functional>
#include <cassert>
#include "parser.h"

using namespace std;


string TestNum(int num)
{
	return "Num = " + to_string(num) + "\n";
}


string TestStr(const string & str)
{
	return "Str = " + str + "\n";
}   

string NewTestStr(const string & str)
{
	return "Str = " + str + str + "\n";
}   


string TestStart()
{
	return "Start ";
}


string TestFinish()
{
	return " Finish";
}

void Test_1()
{
	TokenParser FirstParser;
	FirstParser.setStartCallback(TestStart);
	FirstParser.setFinishCallback(TestFinish);
	FirstParser.setNumCallback(TestNum);
	FirstParser.setStrCallback(TestStr);
	string s = "hello 1010friend\t777  \r\ni am parser";
	assert(FirstParser.parse(s) == "Start " "Str = hello\n" "Str = 1010friend\n" "Num = 777\n" "Str = i\n" "Str = am\n" "Str = parser\n"" Finish");
}
	

void Test_2()
{
	TokenParser SecondParser;
	string s = "456 df 345 aa ";
	assert(SecondParser.parse(s) == "Defaul function for start is missing\n"
    "Default function is missing\n"
    "Default function is missing\n""Default function is missing\n"
    "Default function is missing\n" "Defaul function for finish is missing\n");
}


void Test_3()
{
	TokenParser ThirdParser = TokenParser(TestNum, TestStr, TestStart, TestFinish);
	string s = "Very interesting 1010183 text\n\njhfjdhf67\t14 ";
	assert(ThirdParser.parse(s) == "Start ""Str = Very\n""Str = interesting\n""Num = 1010183\n""Str = text\n""Str = jhfjdhf67\n""Num = 14\n"" Finish");
}

void Test_4()
{
	TokenParser FourthParser = TokenParser(TestNum, TestStr, TestStart, TestFinish);
	FourthParser.setStrCallback(NewTestStr);
	string s = "Very interesting 1010183 text\n\njhfjdhf67\t14 ";
	assert(FourthParser.parse(s) == "Start ""Str = VeryVery\n""Str = interestinginteresting\n""Num = 1010183\n""Str = texttext\n""Str = jhfjdhf67jhfjdhf67\n""Num = 14\n"" Finish");
}

void Test_Only_Str()
{
	TokenParser LastParser = TokenParser(TestNum, TestStr, TestStart, TestFinish);
	string s = "Very interesting text";
	assert(LastParser.parse(s) == "Start ""Str = Very\n""Str = interesting\n""Str = text\n"" Finish");
}

int main(int argc, char* argv[])
{
	Test_1();
	Test_2();
	Test_3();
	Test_4();
	Test_Only_Str();
	cout << "Success!" << endl;
	return 0;
}
