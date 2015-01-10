/**************************
Fraction.h
***************************/

#include <string.h>
#include <sstream>
#include <iostream>
using namespace std;

class Fraction
{
public:
		Fraction();
		Fraction(int num, int denom);
		
		string toString();
		
		void simplify();
		
protected:
		int gcdHelper();
		int gcd(int x, int y);
		
		void setNumerator(int num);
		void setDenominator(int denom);
		
		int numerator;
		int denominator;
};
