#pragma once
#include <string>
#include <iostream>

using namespace std;


class BigInt
{
	private:
		char* Int;
		size_t IntSize;
		bool IsNeg;
	public:
		BigInt();
		BigInt(int);
		BigInt(const BigInt&);
		BigInt(const string&);
		char* getInt() const;
		size_t getSize() const;
		bool getFlag() const;
		void setFlag(bool);
		void setSize(size_t);
		void delInt();
		void setInt(size_t);
		BigInt(BigInt&&);
		BigInt& operator =(const BigInt&);
		BigInt & operator =(BigInt &&);
		friend ostream & operator <<(ostream&, const BigInt&);
		BigInt operator-() const;
		char& operator[](size_t);
		const char& operator[](size_t) const;
		BigInt operator +(const BigInt&) const;
		BigInt operator -(const BigInt&) const;
		void del_zero();
		BigInt operator *(const BigInt&) const;
		bool operator ==(const BigInt&) const;
		bool operator !=(const BigInt&) const;
		bool operator <(const BigInt&) const;
		bool operator >=(const BigInt&) const;
		bool operator <=(const BigInt&) const;
		bool operator >(const BigInt&) const;
		~BigInt();
};
