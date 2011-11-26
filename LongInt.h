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
		//pass the integer as a string
		LongInt(std::string num);
		//assumes the LongInt holds a 0
		LongInt();
		//returns the number of digits in the LongInt
		int digits();
		//returns the number of digits in n
		static int digit(int n);
		//returns true if the LongInt is positive; false otherwise
		bool positive () const;
		//allows for printing into strings(eg, cout)
		friend std::ostream& operator<<(std::ostream& os, const LongInt& Int) ;
		//addition
		friend LongInt operator+(LongInt& a, const LongInt & b);
		friend LongInt operator+(LongInt& a, int b);
		//multiplication
		friend LongInt operator*(LongInt& a, const LongInt & b);
		friend LongInt operator*(LongInt& a, int b);
		//division
		friend LongInt operator/(LongInt& a, const LongInt & b);
		//subtraction
		friend LongInt operator-(LongInt& a, const LongInt & b);
		//power
		friend LongInt operator^(LongInt& a,int i);
		//returns true if the numerical value of the string is 0; for example, "0"
		//"0000" "-000000" "+0000" would cause isZero() to return true; false //otherwise
		static bool isZero(const std::string& s);
		//zeros out the LongInt so LongInt as if you had performed LongInt("0")
		void clear();

	protected:
		//division
		LongInt div(const LongInt& b);
		//multiplication
		LongInt mul(const LongInt& b);
		//subtraction
		LongInt sub(const LongInt& b);
		//raise the LongInt to the power of pow
		LongInt power(int pow);
		//addition
		LongInt add (const LongInt& b);
		//converts the LongInt into a string representation
		std::string toString() const;
		//addition
		LongInt add(const LongInt& b, int sgn);
		//subtraction
		LongInt sub(const LongInt& b,ADTList* la,ADTList* lb,int sgn);
		//returns the first (length)(eg, 5) non-zero digits of a LongInt from left
		//hand side
		int firstDigits(const LongInt& I,int length);
		//The following function compares which of the two numbers is greater, 
		//smaller, or equal.  
		//Returns 1 if a > b. 
		//Returns 0 if a == b. 
		//Returns -1 if a < b.  larger() does not take size into account!
		int larger(ADTList* a,ADTList* b);
		//returns the integers that are not in the first four digits; for example,
		//overflow(123456) would return 12
		static int overflow(int n);
		//returns -1 if there is an underflow, otherwise returns 0
		static int underflow(int n);
		//trims the number to at most 4 digits
		static void trim(int&);
		//1 for positive else 0
		int sign;
		ADTList* l;
};

#endif 
