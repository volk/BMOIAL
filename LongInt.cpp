#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <sstream>
#include "ADTList.h"
#include "LongInt.h"

LongInt::LongInt(std::string num) : sign(1) {
	if(LongInt::isZero(num) == true) {
		l = new ADTList();
		l->insertLeft(0);
		return;
	}

	int whole_digits;

	l = new ADTList();

	//extract sign if any
	if(num[0] == '+') {
		sign = 1;
		num.erase(num.begin());
	} else if(num[0] == '-') {
		sign = 0;
		num.erase(num.begin());
	}

	//break up every four characters into digits and add them to list
	whole_digits = num.length()/4;
	for(int i=0;i<whole_digits;i++) {
		int start = num.length()-4*(i+1);
		l->insertLeft(atoi(num.substr(start,4).c_str()));
	}

	int v = atoi(num.substr(0,num.length()-whole_digits*4).c_str());
	if(v != 0) {
		l->insertLeft(v);
	}
}

LongInt::LongInt() : sign(1) {
	l = new ADTList();
	l->insertLeft(0);
}

int LongInt::digits() {
	if(l->size() == 0) {
		return 0;
	}

	int length = (l->size()-1)*4;
	length += digit(l->firstLeft()->element());

	return length;
}

//returns POSITIVE if LongInt is >= 0 otherwise NEGATIVE
bool LongInt::positive () const {
	return sign == POSITIVE;
}

int LongInt::overflow(int n) {
	return n/10000;
}

int LongInt::digit(int n) {
	int i;
	for(i=1; n/(int)pow(10,i) != 0; i++);
	return i;
}

int LongInt::underflow(int n) {
	if(n >= 0)
		return 0;
	else
		return -1;
}

// a is >= b, and sign is the sign of the result
LongInt LongInt::sub(const LongInt& b,ADTList* la,ADTList* lb,int sgn) {
	//old_carry is used to store previous value of carry when carry is changed
	int carry = 0, old_carry = 0;
	int sum = 0;
	LongInt result;

	ADTList *lst_a = la; // top, larger than b
	ADTList *lst_b = lb; //bottom, smaller than a
	ADTList *lst_r = result.l; //result of a-b
	result.sign = sgn; // sign of result

	Node *na = lst_a->firstRight();
	Node *nb = lst_b->firstRight();

	sum = na->element() - nb->element();
	carry = underflow(sum);
	old_carry = carry;
	if(carry == -1) {
		sum = na->element() - nb->element() + 10000;
	}

	lst_r->firstRight()->setElement(sum);

	while(!lst_a->isFirst(na) && !lst_b->isFirst(nb)) {
		na = lst_a->nextLeft(na);
		nb = lst_b->nextLeft(nb);

		sum = na->element() - nb->element() + carry;
		old_carry = carry;
		carry = underflow(sum);
		if(carry == -1) {
			sum = na->element() - nb->element() + 10000 + old_carry;
		} 
		lst_r->insertLeft(sum);
	}

	na = lst_a->nextLeft(na);

	while(na != NULL) {
		sum = na->element() + carry;
		//only need to include carry once after finishing with the nb array
		carry = 0;

		lst_r->insertLeft(sum);
		na = lst_a->nextLeft(na);
	}

	return result;
}

LongInt LongInt::div(const LongInt& b) {
	//this will be returned as final result
	LongInt result("0");

	LongInt* dividend = new LongInt(toString());
	LongInt divisor(b.toString());

	//check if we even need to do division the special cases that the divisor is 
	//greater than dividend or if one of them is zero or if they are equal
	if(larger(dividend->l,divisor.l) == 0) {
		return LongInt("1");
	} else if(larger(dividend->l,divisor.l) == -1) {
		return LongInt("0");
	} else if(LongInt::isZero(divisor.toString()) == true) {
		//throw divide by zero exception here
		std::cout << std::endl << "Attempting to divide by zero!" << std::endl;
		return LongInt("0");
	} else if(LongInt::isZero(dividend->toString()) == true) {
		return LongInt("0");
	}

	//XOR the signs of both the dividend and divisor to get sign of result
	result.sign = (positive() == b.positive());

	//terminate when divisor is larger than dividend
	while(larger(dividend->l,divisor.l) != -1)
	{
		//if divisor and dividend are now equal, then simply multiply result by 10
		//and return
		if(larger(dividend->l,divisor.l) == 0) {
			result = result * 10;
			return result;
		}

//		cout << endl << "dividend(" << *dividend << ") divisor(" << divisor << ")" << endl;
		//extract first few digits of divisor and dividend and then divide both
		int quotient = 0;

		if(firstDigits(*dividend,4) >= firstDigits(divisor,4) ) {
			quotient = firstDigits(*dividend,4) / firstDigits(divisor,4);
			
			std::cout << "dividing " << firstDigits(*dividend,4) << " by " << 
				firstDigits(divisor,4) << " = " << quotient;

		} else if(firstDigits(*dividend,5) >= firstDigits(divisor,4) ) {
			quotient = firstDigits(*dividend,5) / firstDigits(divisor,4);

			std::cout << "dividing " << firstDigits(*dividend,5) << " by " << 
				firstDigits(divisor,4) << " = " << quotient;

		} else {
			//we will never reach this branch
//			std::cout << "dividing " << firstDigits(*dividend,5) << " by " << 
//				firstDigits(divisor,4) << " = " << quotient;
			std::cout << std::endl << "Will never reach here" << std::endl;
		}

		//minuend - subtrahend = difference
		LongInt subtrahend(divisor.toString());
		subtrahend = subtrahend * quotient;

		//pad right-hand side of subtrahend with 0s to match length of minuend
		int padding = dividend->digits()-subtrahend.digits();
		LongInt base("10");
		subtrahend = subtrahend * (base^padding);
//		std::cout << "\tsubtrahend " << subtrahend << endl;
		subtrahend = *dividend - subtrahend;

		delete dividend;
		dividend = new LongInt(subtrahend.toString());
//		cout << endl << "new dividend " << *dividend << endl;

		if(result.toString() != string("0")) {
			padding = LongInt::digit(quotient);
			result = result * (base^padding);
		}
		result = result+quotient;
		cout << endl << "dividend(" << *dividend << ") divisor(" << divisor << ")" << endl;

	}

	return result;
}

LongInt LongInt::mul(const LongInt& b) {
	LongInt result;

	ADTList *lst_a = l; // top number
	ADTList *lst_b = b.l; //bottom number
	result.sign = (positive() == b.positive()); //XOR the signs of both

	//rightmost node of both lists
	Node *na = lst_a->firstRight();
	Node *nb = lst_b->firstRight();
	Node *start = nb;

	//we will store all the mutliplication results here and add them together
	//at the end
	LongInt **resultList = new LongInt*[lst_b->size()];

	//allocate temporary storage lists
	for(int i=0;i<lst_b->size();i++) {
		resultList[i] = new LongInt("0");

		//pad 0s to the right side in units of four
		for(int j=1;j<=i;j++) {
			resultList[i]->l->insertLeft(0);
		}
	}

	int total = 0; //result of two multiplicands
	int carry = 0; // 
	int cur = 0; //current element in resultList
	ADTList *curList;


	while(start != NULL) {
		curList = resultList[cur]->l;

		na = lst_a->firstRight();
		//only needs to run on first Node in list
		bool ran_once = false;

		carry = 0;

		while(na != NULL) {
			total = na->element() * start->element() + carry;
			carry = overflow(total); 
			LongInt::trim(total);

			//only for first Node in list in first row
			if(ran_once == false) {
				curList->firstLeft()->setElement(total);
				ran_once = true;
			} else {
				curList->insertLeft(total);
			}

			na = lst_a->nextLeft(na);
		}

		if(carry != 0) { 
			curList->insertLeft(carry);
		}

		carry = 0;

		start = lst_b->nextLeft(start);
		cur++;
	}

	//sum up all lists and save in final LongInt
	for(int i=0;i<lst_b->size();i++) {
		result = result.add(*resultList[i]);
	}

	//free all memory allocated
	for(int i=0;i<lst_b->size();i++) {
		delete resultList[i];
	}

	delete resultList;

	return result;
}

//sub() basically checks if we need to add or subtract depending on sign of the
//inputs we are given
LongInt LongInt::sub(const LongInt& b) {
	//We need to determine which LongInt is greater and send it off to be 
	//subtracted. We will use tricks such as A-B = -(B-A) to subtract.

	//first check if the numbers are equal
	if(larger(l,b.l) == 0) {
		return LongInt("0");
	}

	if(positive() && b.positive()) {

		if(larger(l,b.l) == 1) 
			return sub(b,l,b.l,POSITIVE);
		else if(larger(l,b.l) == -1) 
			return sub(b,b.l,l,NEGATIVE);

	} else if(!positive() && !b.positive()) {

		if(larger(l,b.l) == 1) 
			return sub(b,l,b.l,NEGATIVE);
		else if(larger(l,b.l) == -1) 
			return sub(b,b.l,l,POSITIVE);

	} else if(!positive() && b.positive()){

		return add(b,NEGATIVE);

	} else {

		return add(b,POSITIVE);

	}

	//program will never reach here but compiler complains
	return LongInt("0");
}

LongInt LongInt::add(const LongInt& b, int sgn) {
	LongInt result;

	ADTList *lst_a = l; // top number
	ADTList *lst_b = b.l; //bottom number
	ADTList *lst_r = result.l; //result after addition
	result.sign = sgn; //we are given sign

	//rightmost node of both lists
	Node *na = lst_a->firstRight();
	Node *nb = lst_b->firstRight();

	int sum = na->element() + nb->element();
	int carry = overflow(sum); //if addition is more than 4 digits, save it overflow

	lst_r->firstRight()->setElement(sum);

	//
	while(!lst_a->isFirst(na) && !lst_b->isFirst(nb)) {
		na = lst_a->nextLeft(na);
		nb = lst_b->nextLeft(nb);

		sum = na->element() + nb->element() + carry;
		carry = overflow(sum);

		lst_r->insertLeft(sum);
	}

	while(!lst_a->isFirst(na)) {
		na = lst_a->nextLeft(na);

		sum = na->element() + carry;
		carry = overflow(sum);

		lst_r->insertLeft(sum);
	}

	while(!lst_b->isFirst(nb)) {
		nb = lst_b->nextLeft(nb);

		sum = nb->element() + carry;
		carry = overflow(sum);

		lst_r->insertLeft(sum);
	}

	if(carry != 0) {
		lst_r->insertLeft(carry);
	}

	return result;
}

LongInt LongInt::power(int pow) {

	//special cases
	if(pow < 0) {
		return LongInt("0");
	} else if(pow == 0) {
		return LongInt("1");
	}

	LongInt result("1");
	int pow_cpy = pow;

	unsigned int max_size = log10(pow_cpy)/log10(2)+2;
	LongInt **powerList = new LongInt*[max_size];
	powerList[0] = new LongInt(toString());

	//allocate storage for power values all the way up to the one
	//we want
	for(int i=1;i<(int)max_size;i++) {
		powerList[i] = new LongInt((powerList[i-1]->mul(*powerList[i-1])).toString());

	}

	for(int i=0;i<(int)max_size;i++) {
		if((pow_cpy&0x1) == true) {
			result = result.mul(*powerList[i]);
		}

		pow_cpy >>= 1;
	}

	//POSITIVE by default
	result.sign = POSITIVE;

	//check if negative in the special case power
	//is odd and sign of base is negative
	if(pow%2 == 1 && positive() == false) {
		result.sign = NEGATIVE;
	}

	return result;
}

//add() basically checks if we need to add or subtract depending on sign of the
//inputs we are given
LongInt LongInt::add(const LongInt& b) 
{

	if(positive() && b.positive()) {

		//result should be positive because we are adding two positive integers
		return add(b,POSITIVE);

	} else if(!positive() && !b.positive()) {

		//result should be negative we are adding two negative integers
		return add(b,NEGATIVE);

	} else {

		//In this branch, sign of local LongInt is not equal to the sign of b.
		//We need to determine which LongInt is greater and send it off to be 
		//subtracted. We will use tricks such as A-B = -(B-A) to subtract.

		if(!positive() && b.positive()) {
			//local LongInt is negative and b is positive

			//determine who is bigger by node size(each node is at most four digits)
			if(larger(l,b.l) == 1)
				return sub(b,l,b.l,NEGATIVE);
			else if(larger(l,b.l) == -1)
				return sub(b,b.l,l,POSITIVE);
			else 
				return LongInt("0");

		} else {
			//local LongInt is positive and b is negative

			//determine who is bigger by node size(each node is at most four digits)
			if(larger(l,b.l) == 1) 
				return sub(b,l,b.l,POSITIVE);
			else if(larger(l,b.l) == -1) 
				return sub(b,b.l,l,NEGATIVE);
			else 
				return LongInt("0");

		}
	}
}


std::string LongInt::toString() const{
	if(l->size() == 0) {
		return std::string("0");
	}

	std::stringstream ss;
	string s;
	int i;

	if(positive() == false) {
		ss << '-';
	}

	for(Node* n=l->firstLeft(); n != NULL; n = l->nextRight(n)) {
		ss << string(4-LongInt::digit(n->element()),'0') << n->element();
	}

	s = ss.str();
	//remove any 0s from front
	if(positive() == false) {
		i = 1;
	} else {
		i = 0;
	}

	for(; i < (int)s.length(); i++) {
		if(s[i] == '0') { 
			s.erase(s.begin()+i);

			if(positive() == false) {
				i = 0;
			} else {
				i = -1;
			}
		} else {
			break;
		}
	}

	if(s.length() == 0) {
		s += "0";
	}

	return s;
}

std::ostream& operator<<(std::ostream& os, const LongInt& Int) 
{ 
	os << Int.toString();
	return os;
} 

LongInt operator+(LongInt& a, const LongInt & b) {
	return a.add(b);
}

LongInt operator+(LongInt& a, int b) {
	std::stringstream ss;
	ss << b;
	return a.add(LongInt(string(ss.str())));
}

LongInt operator*(LongInt& a, const LongInt & b) {
	return a.mul(b);
}

LongInt operator*(LongInt& a, int b) {
	std::stringstream ss;
	ss << b;
	return a.mul(LongInt(string(ss.str())));
}

LongInt operator/(LongInt& a, const LongInt & b) {
	return a.div(b);
}

LongInt operator-(LongInt& a, const LongInt & b) {
	return a.sub(b);
}

LongInt operator^(LongInt& a,int i) {
	return a.power(i);
}

//returns the first (length)(eg, 5) non-zero digits of a LongInt; ignores sign
int LongInt::firstDigits(const LongInt& I,int length) {
	//we will use toString() because it truncates all 0s in the front

	string s = I.toString();

	if(s[0] == '+' || s[0] == '-') {
		s.erase(s.begin());
	} 

	if(s.length() <= (unsigned int)length) {
		return atoi(s.c_str());
	} else {
		return atoi(s.substr(0,(unsigned int)length).c_str());
	}
}

//The following function compares which of the two numbers is greater, smaller, or 
//equal.  Returns 1 if a > b. Returns 0 if a == b. Returns -1 if a < b.
//larger() does not take size into account!
int LongInt::larger(ADTList* a,ADTList* b) {

	//check size by node sizes, where each node has a 4 digit number
	if(a->size() > b->size()) {
		return 1;
	} else if(a->size() < b->size()) {
		return -1;
	} else {

		Node *na = a->firstLeft(), *nb = b->firstLeft();

		while(na != NULL && nb != NULL) {
			if(na->element() > nb->element()) {
				return 1;
			} else if(na->element() < nb->element()) {
				return -1;
			} else {
				na = a->nextRight(na);
				nb = b->nextRight(nb);
			}
		}

		return 0; // equal numbers
	}
}

void LongInt::clear()
{
	delete l;
	l = new ADTList();
	l->insertLeft(0);
	sign = POSITIVE;
}

bool LongInt::isZero(const std::string& num) 
{
	if(num.empty() == true) {
		return false;
	}

	int start_indx = 0;

	if(num[0] == '+' || num[0] == '-') {
		start_indx = 1;
	}

	for(int i=start_indx; i < (int)num.length(); i++) {

		if(num[i] != '0') { 
			return false;
		} 

	}

	return true;

}

void LongInt::trim(int& v)
{
	v = (abs(v))%10000;
}
