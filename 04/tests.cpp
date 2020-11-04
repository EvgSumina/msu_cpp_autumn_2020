#include <iostream>
#include <limits>
#include <sstream>
#include <cassert>
#include "BigInt.h"

using namespace std;


int main()
{
	BigInt x(003);
	BigInt y(x);
	BigInt z("-003");
	cout << x << endl;
	assert(x == y);
	assert(y == x);
	assert(x != z);
	assert(x == -z);

	BigInt x_1 = 2;
	assert(x_1 < x);
	assert(-x_1 > -x);

	x = 100;
	assert(BigInt(200) > x);
	assert(BigInt(50) < x);
	assert(BigInt(-500) < x);
	assert(BigInt(-500) < BigInt(-200));
	assert(x <= x);
	assert(x >= x);

	assert((BigInt(100) - BigInt(100)) == BigInt("0"));
	assert((BigInt(-10) + BigInt(10)) == BigInt("0"));
	assert((BigInt(10) + BigInt(-10)) == BigInt("0"));
	assert((BigInt(-10) + BigInt(-10)) == BigInt("-20"));

	assert((BigInt(10) - BigInt(10)) ==  BigInt("0"));
	assert((BigInt(10) - BigInt(-10)) ==  BigInt("20"));
	assert((BigInt(-10) - BigInt(10)) ==  BigInt("-20"));
	assert((BigInt(-10) - BigInt(-10)) ==  BigInt("0"));

	assert((BigInt(0) + BigInt(-1)) ==  BigInt("-1"));
	assert((BigInt(0) - BigInt(1)) ==  BigInt("-1"));
	assert((BigInt(0) + BigInt(0)) ==  BigInt("0"));

	assert((BigInt(99) + BigInt(100)) ==  BigInt("199"));
	assert((BigInt(99) - BigInt(100)) ==  BigInt("-1"));
	assert((BigInt(-99) + BigInt(100)) ==  BigInt("1"));
	assert((BigInt(99) - BigInt(-100)) ==  BigInt("199"));

	assert((BigInt(15) * BigInt(4)) ==  BigInt("60"));
	assert((BigInt(-15) * BigInt(-4)) ==  BigInt("60"));
	assert((BigInt(-15) * BigInt(4)) ==  BigInt("-60"));
	assert((BigInt(15) * BigInt(-4)) ==  BigInt("-60"));

	assert((BigInt(4) * BigInt(15)) ==  BigInt("60"));
	assert((BigInt(15) * BigInt(0)) ==  BigInt("0"));

	assert((BigInt("9999999999999990000000000010193888888") * BigInt("10000000000")) ==  BigInt("99999999999999900000000000101938888880000000000"));

	std::cout << "Success!\n";

	return 0;
}
