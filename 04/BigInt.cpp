#include <iostream>
#include "BigInt.h"
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;


BigInt::BigInt(): Int(nullptr), IntSize(0), IsNeg(false){}


BigInt::BigInt(int num)
{
	num < 0? IsNeg = true : IsNeg = false;
	if (IsNeg)
		num = -num;
	string str = to_string(num);
	Int = new char[str.length()];
	copy(str.c_str(), str.c_str() + str.length(), Int);
	IntSize = str.length();
}


BigInt::BigInt(const BigInt& CopyInt): IntSize(CopyInt.getSize()), IsNeg(CopyInt.getFlag())
{
	Int = new char[IntSize];
	copy(CopyInt.getInt(), CopyInt.getInt() + IntSize, Int);
	(*this).del_zero();
}


BigInt::BigInt(const string& str)
{
	if (str[0] == '-')
	{
		IntSize = str.length() - 1;
		Int = new char[IntSize + 1];
		copy(&str.c_str()[1], &str.c_str()[1] + IntSize + 1, Int);
		IsNeg = true;
	}
	else
	{
		IntSize = str.length();
		Int = new char[IntSize + 1];
		copy(str.c_str(), str.c_str() + IntSize + 1, Int);		
		IsNeg = false;
	}
	(*this).del_zero();
}


char* BigInt::getInt() const
{
	return Int;
}


size_t BigInt::getSize() const
{
	return IntSize;
}


bool BigInt::getFlag() const
{
	return IsNeg;
}


void BigInt::setFlag(bool flag)
{
	IsNeg = flag;
}


void BigInt::setSize(size_t size)
{
	IntSize = size;
}


void BigInt::delInt()
{
	delete []Int;
	Int = nullptr;
}


void BigInt::setInt(size_t size)
{
	delete []Int;
	IntSize = size;
	if (size == 0)
		Int = nullptr;
	else
		Int = new char[size];
}


BigInt::BigInt(BigInt&& MovedInt): Int(MovedInt.getInt()), IntSize(MovedInt.getSize()), IsNeg(MovedInt.getFlag())
{
	MovedInt.Int = nullptr;
	MovedInt.IntSize = 0;
	MovedInt.IsNeg = false;
}


BigInt& BigInt::operator=(const BigInt& copied)
{
	if (this == &copied)
		return *this;
	IntSize = copied.getSize();
	IsNeg = copied.getFlag();
	char* ptr = new char[IntSize];
	delete[] Int;
	Int = ptr;
	copy(copied.Int, copied.Int + IntSize, Int);
	return *this;
}


BigInt & BigInt::operator =(BigInt && moved)
{
	if(this == &moved)
		return *this;
	IntSize = moved.getSize();
	IsNeg = moved.getFlag();
	delete []Int;
	Int = moved.getInt();
	moved.Int = nullptr;
	moved.IntSize = 0;
	return *this;
}
	

ostream& operator<<(ostream& out, const BigInt& myInt)
{
	if(myInt.getFlag())
	{
		out << "-";
	}
	for (int i = 0; i < myInt.getSize(); i++)
	{
		out << myInt[i];
	}
	return out;
}


BigInt BigInt::operator-() const
{
	BigInt result = BigInt(*this);
	result.setFlag(!result.getFlag());
	return result;
}


char& BigInt::operator[](size_t i)
{
	if (i >= IntSize)
	{
		throw out_of_range("Out of range");
	}
	return Int[i];
}


const char& BigInt::operator[](size_t i) const
{
	if (i >= IntSize)
	{
		throw out_of_range("Out of range");
	}
	return Int[i];
}


BigInt BigInt::operator+(const BigInt& SecondInt) const
{
	int first;
	int second;
	int addition = 0;
	if(IsNeg && !SecondInt.getFlag())
	{
		BigInt z(*this);
		z.setFlag(false);
		return SecondInt - z;
	}
	if (!IsNeg && SecondInt.getFlag())
	{
		BigInt z(SecondInt);
		z.setFlag(false);
		return *this - z;
	}
	string str(max(SecondInt.getSize(), IntSize) + 1, '\0');
	BigInt result(str);
	size_t Firstlimit = result.getSize() - IntSize;
	size_t Secondlimit = result.getSize() - SecondInt.getSize();
	for(int i = result.getSize() - 1; i >= 1; i--)
	{
		if(i >= Firstlimit)
		{
			first = Int[i - Firstlimit] - '0';
		}
		else
		{
			first = 0;
		}
		if(i >= Secondlimit)
		{
			second = SecondInt[i - Secondlimit] - '0';
		}
		else
		{
			second = 0;
		}
		first = first + second;
		result[i] = (first + addition) % 10 + '0';
		if (i > 1)
		{
			addition = first / 10;
		}
		else
		{
			result[0] = (first + addition) / 10 + '0';
		}
	}
	if(IsNeg)
	{
		result.setFlag(true);
	}
	else
	{
		result.setFlag(false);
	}
	result.del_zero();
	return result;
}
	

BigInt BigInt::operator-(const BigInt& SecondInt) const
{
	int first;
	int second;
	int sub = 0;
	if(IsNeg && !SecondInt.getFlag())
	{
		return -((-*this) + SecondInt);
	}
	if(!IsNeg && SecondInt.getFlag())
	{
		return *this + (-SecondInt);
	}
	if(!IsNeg && !SecondInt.getFlag())
	{
		if(*this < SecondInt)
		{
			return -(SecondInt - *this);
		}
	}
	if(IsNeg & SecondInt.getFlag())
	{
		return (-SecondInt) - (-*this);
	}
	string str(max(SecondInt.getSize(), IntSize), '\0');
	BigInt result(str);
	size_t Firstlimit = result.getSize() - IntSize;
	size_t Secondlimit = result.getSize() - SecondInt.getSize();
	for(int i = result.getSize() - 1; i >= 0; i--)
	{
		if(i >= Firstlimit)
		{
			first = Int[i - Firstlimit] - '0';
		}
		else
		{
			first = 0;
		}
		if(i >= Secondlimit)
		{
			second = SecondInt[i - Secondlimit] - '0';
		}
		else
		{
			second = 0;
		}
		if(first - sub >= second)
		{
			first = first - sub - second;
			sub = 0;
		}
		else
		{
			first = first + 10 - sub - second;
			sub = 1;
		}
		result[i] = first + '0';
	}
	result.del_zero();
	return result;
}


void BigInt::del_zero()
{
	int i = 0;
	while ((Int[i] == '0') && (i < IntSize))
	{
		i++;
	}
	if (i == 0)
		return;
	if (i == IntSize)
	{
		IntSize = 1;
		Int[1] = '\0';
		return;
	}
	char* ptr = new char[IntSize - i + 1];
	int j = 0;
	while(i <= IntSize)
	{
		ptr[j] = Int[i];
		i++;
		j++;
	}
	IntSize = j - 1;
	delete []Int;
	Int = ptr;
	copy(ptr, ptr + j, Int);
	return;
}


BigInt BigInt::operator*(const BigInt& SecondInt) const
{
	char t;
	string ptr(SecondInt.getSize() + IntSize, '\0');
	BigInt result(ptr);
	int* res = new int[SecondInt.getSize() + IntSize];
	if (IsNeg && SecondInt.getFlag() || !IsNeg && !SecondInt.getFlag())
		result.setFlag(false);
	else
		result.setFlag(true);
	for (unsigned int i = 0; i < SecondInt.getSize() + IntSize; i++)
	{
		res[i] = 0;
	}
	for (unsigned int i = 0; i < IntSize; i++)
	{
		int c = 0;
		for (unsigned int j = 0; j < SecondInt.getSize(); j++)
		{
			int first = Int[IntSize - i - 1] - '0';
			int second = SecondInt[SecondInt.getSize() - j - 1] - '0';
			res[SecondInt.getSize() + IntSize - (i + j) - 1] += c + first * second;
			c = res[SecondInt.getSize() + IntSize - (i + j) - 1] / 10;
			res[SecondInt.getSize() + IntSize - (i + j) - 1] %= 10;
		}
		res[SecondInt.getSize() + IntSize - (i + SecondInt.getSize()) - 1] += c;
	}
	for (unsigned int i = 0; i < SecondInt.getSize() + IntSize; i++)
	{
		t = res[i] + '0';
		result[i] = t;
	}
	delete []res;
	result.del_zero();
	return result;
}


bool BigInt::operator ==(const BigInt& SecondInt) const
{
	if(IntSize != SecondInt.getSize())
		return false;
	if (IsNeg != SecondInt.getFlag())
		return false;
	for (unsigned int i = 0; i < IntSize; i++)
	{
		if(Int[i] != SecondInt[i])
			return false;
	}
	return true;
}


bool BigInt::operator!=(const BigInt& SecondInt) const
{
	return !(*this == SecondInt);
}


bool BigInt::operator<(const BigInt& SecondInt) const
{
	if(*this == SecondInt)
	{
		return false;
	}
	if(IsNeg)
	{
		if(SecondInt.getFlag())
			return ((-*this) > (-SecondInt));
		else
			return true;
	}
	else if(SecondInt.getFlag())
		return false;
	else
	{
		if(IntSize != SecondInt.getSize())
			return IntSize < SecondInt.getSize();
		else
		{
			for (unsigned int i = IntSize - 1; i >= 0; --i) 
			{
				if (Int[i] != SecondInt[i])
					return Int[i] < SecondInt[i];
			}
			return false;
		}
	}
}


bool BigInt::operator>=(const BigInt& SecondInt) const
{
	return !(*this < SecondInt);
}


bool BigInt::operator<=(const BigInt& SecondInt) const
{
	return ((*this < SecondInt) || (*this == SecondInt));
}


bool BigInt::operator>(const BigInt& SecondInt) const
{
	return !(*this <= SecondInt);
}


BigInt::~BigInt()
{
	if(Int != nullptr)
	{
		delete []Int;
	}
}
