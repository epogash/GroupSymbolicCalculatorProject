/**************************
Fraction.cpp
***************************/

#include "Fraction.h"
//Fraction class to handle fractions
Fraction::Fraction(int num, int denom){
	setNumerator(num);
	setDenominator(denom);
}

Fraction::Fraction(){
	numerator = 0;
	denominator = 1;
}

string Fraction::toString(){
//returns different strings depending on what is in the object
	stringstream ss;
	ss << numerator;
	string num = ss.str();
	ss.str("");
	ss << denominator;
	string denom = ss.str();
	if (numerator == 0){
		return "0";
	}
	if (denominator == 0){
        throw 3;
		return "Error: Divide by 0.";
	}
	if (denominator == 1){
		return num;
	}
	else{
	return num + "/" + denom;
	}
}

void Fraction::setNumerator(int num){
	numerator = num;
}

void Fraction::setDenominator(int denom){
	denominator = denom;
}

int Fraction::gcdHelper(){

	if(numerator == denominator){
		return numerator;
	}

	int x = denominator;
	int y = numerator;

	if (numerator > denominator){
		return gcd(y,x);
	}

	else{
		return gcd(x,y);
	}
}

int Fraction::gcd(int x, int y){
	if (y == 0){
		return x;
	}

	else {
		return gcd(y, x%y);
	}
}

void Fraction::simplify(){
	int gcd = gcdHelper();

	//manipulating signs of outcome below

	//take absolute value of gcd
	if (gcd <0) {
		gcd *= -1;
	}

	//positive numerator
	if (numerator >= 0){
		//positive denominator, positive fraction
		if (denominator > 0){
			setNumerator(numerator/gcd);
			setDenominator(denominator/gcd);
		}
		//negative denominator, negative fraction
		if (denominator < 0){
			setNumerator(-numerator/gcd);
			setDenominator(-denominator/gcd);
		}
	}

	//negative numerator
	else{
		//positive denominator, negative fraction
		if (denominator > 0){
			setNumerator(numerator/gcd);
			setDenominator(denominator/gcd);
		}
		//negative denominator, positive fraction
		if (denominator < 0){
			setNumerator(-numerator/gcd);
			setDenominator(-denominator/gcd);
		}
	}

}

