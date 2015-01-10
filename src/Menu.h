/**************************
Menu.h
***************************/

#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "Calculator.h"

using namespace std;

class Menu
{
public:
	Menu();
	void menu();
	void title();
	Calculator C;
	
private:
	void help();
	void list();
	void setANS();
	void calc();
	string stringToUpper(string convert);
	bool quitFlag;
		
};

#endif 