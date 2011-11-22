#ifndef _LONGINT_H
#define _LONGINT_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <sstream>
#include "ADTList.h"

using namespace std;

const int POSITIVE = 1;
const int NEGATIVE = 0;

class LongInt {
	public:
		LongInt(std::string num);
		LongInt();
		int digits();
		bool positive () const;
		bool empty();
		static int overflow(int n);
		static int digit(int n);
		static int underflow(int n);
		LongInt sub(const LongInt& b,ADTList* la,ADTList* lb,int sgn);
		LongInt div(const LongInt& b);
		LongInt mul(const LongInt& b);
		LongInt sub(const LongInt& b);
		LongInt add(const LongInt& b, int sgn);
		LongInt power(int pow);
		LongInt add (const LongInt& b);
		std::string toString() const;
		friend std::ostream& operator<<(std::ostream& os, const LongInt& Int) ;
		friend LongInt operator+(LongInt& a, const LongInt & b);
		friend LongInt operator*(LongInt& a, const LongInt & b);
		friend LongInt operator/(LongInt& a, const LongInt & b);
		friend LongInt operator-(LongInt& a, const LongInt & b);
		friend LongInt operator^(LongInt& a,int i);

	protected:
		//1 for positive else 0
		int sign;
		ADTList* l;

		//returns the first (length)(eg, 5) non-zero digits of a LongInt
		int firstDigits(const LongInt& I,int length);

		//The following function compares which of the two numbers is greater, smaller, or 
		//equal.  Returns 1 if a > b. Returns 0 if a == b. Returns -1 if a < b.
		//larger() does not take size into account!
		int larger(ADTList* a,ADTList* b);
};

#endif 
