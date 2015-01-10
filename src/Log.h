/**************************
Log.h
***************************/

#include <string.h>
#include <iostream>
#include "Calculator.h"

using namespace std;

class Log
{

public:
	Log(int base, int value);
	~Log();

	string toString();
	int valueMultiples;
	
private:
	int value;
	int base;

};
