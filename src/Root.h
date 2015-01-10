/**************************
Root.h
***************************/

#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;

class Root
{
public:
	Root(int index, int radicand);
	Root(int value, int index, int radicand);
	~Root();
	int getIndex();
	int getRadicand();
	int getValue();
	string toString();
	
	void simplify();
	
private:
	int value;
	int index;//squared, cubed, etc
	int radicand;//inside number

};
