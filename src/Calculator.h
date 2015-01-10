/**************************
Calculator.h
***************************/

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stack>
#include <queue>
#include <stdlib.h>
#include <math.h>

#include "Log.h"
#include "Fraction.h"
#include "Root.h"

using namespace std;

class Calculator
{
public:
	Calculator();
	
	vector<string> answerList;
	vector<string> expressionList;
	bool matchedParen(string input);
	string evaluate(string expression);
	string convertToFloatingPoint(string arg1);
	
private:
	string addFloating(string arg1, string arg2);
	string multiplyFloating(string arg1, string arg2);
	string subtractFloating(string arg1, string arg2);
	string divideFloating(string arg1, string arg2);
	string exponentiateFloating(string arg1, string arg2);
	bool isFraction(string arg);
	bool isSqRoot(string arg);
	bool isNRT(string arg);
	bool isLog(string arg);
	bool isNumber(string arg);
	bool isOperator(string input);
	bool isFloatingPoint(string arg);
	int fractionNum(string arg);
	int fractionDenom(string arg);
	int rootIndex(string arg);
	int rootRadicand(string arg);
	int findCoeff(string arg);
	int findBase(string arg);
	string findConstVal(string arg);
	int getPriority(string input);
	bool ifPop(string input, string input2);
	string add(string arg1, string arg2);
	string subtract(string arg1, string arg2);
	string multiply(string arg1, string arg2);
	string divide(string arg1, string arg2);
	string exponentiate(string arg1, string arg2);
	string shuntingYard(string expression);
	string theShiz(string expression);
	string removeSpaces(string input);
	string replaceSQRT(string input);
	bool foundANS(string expression);
	string replaceANS(string expression);
	
};

#endif 
