/**************************
 Menu.cpp
 ***************************/

#include "Menu.h"
#include <fstream>

//menu constructor
Menu::Menu(){
	title();
	Calculator C;
	quitFlag = false;
}

void errorCode(int x) {
	switch (x) {
	case 1:
		cout << "Invalid input." << endl;
		break;
	case 2:
		cout << "Mismatched parentheses." << endl;
		break;
	case 3:
		cout << "Stop dividing by 0." << endl;
		break;
	case 4:
		cout << "Not enough values for the expression to be solved." << endl;
		break;
	case 5:
		cout << "The value of log cannot be less than 1." << endl;
		break;
	case 6:
		cout << "The base of log cannot be less than 2." << endl;
		break;
	case 7:
		cout << "Even root of a negative radicand is not allowed." << endl;
		break;
	case 8:
		cout << "There is no ANS keyword yet." << endl;
		break;
	case 999: cout << "No operand before operation" << endl;
		break;
	}
}

//main method, runs the menu the user interacts with
void Menu::menu() {

	if (quitFlag == false) {

		cout << "To view the help menu, enter HELP" << endl;
		cout << "To use the calculator, enter CALC" << endl;
		cout << "To view your previous answers, enter LIST" << endl;
		cout << "To return to this menu, enter BACK" << endl;
		cout << "To use the floating point calculator, enter FLOATING" << endl;
		cout << "To end the program, enter QUIT" << endl;

		//user's input for main menu selections
		string input;

		//the user input for our calculator
		string expression;

		do {
			try {
				cin >> input;

				input = stringToUpper(input);

				if (input == "HELP") {
					help();
				}

				else if (input == "CALC") {
					cout
							<< "\nWhen you are finished, enter BACK to return to the menu.";
					cin.ignore();
					do {
						cout << "\nEnter an expression" << endl;
						getline(cin, expression);
						if (stringToUpper(expression) == "QUIT") {
							cout << "Goodbye!" << endl;
							quitFlag = true;
						} else if ((stringToUpper(expression) != "BACK")) {
							try {
								string result = C.evaluate(expression);
							} catch (int x) {
								cout << '\a' << flush;
								cout << "An error has occured, error code: "
										<< x << endl;
								errorCode(x);
							}
						}
					} while ((stringToUpper(expression) != "BACK")
							&& (quitFlag == false));
				}

				else if (input == "LIST") {
					list();
				}

				else if (input == "BACK") {

				} else if (input == "FLOATING") {
					cout
							<< "\nWhen you are finished, enter BACK to return to the menu.";
					cin.ignore();
					do {
						cout << "\nEnter an expression" << endl;
						getline(cin, expression);
						if (stringToUpper(expression) == "QUIT") {
							cout << "Goodbye!" << endl;
							quitFlag = true;
						} else if ((stringToUpper(expression) != "BACK")) {
							try {
								string result = C.evaluate(expression);
								string floatResult = C.convertToFloatingPoint(result);
								cout << "The floating point result is: " +  floatResult << endl;
							} catch (int x) {
								cout << "An error has occured, error code: "
										<< x << endl;
								errorCode(x);
							}
						}
					} while ((stringToUpper(expression) != "BACK")
							&& (quitFlag == false));
				} else if (input == "QUIT") {
					quitFlag = true;
					cout << "Goodbye!" << endl;
				}

				else {
					throw 1;
				}
			} catch (int x) {
				cout << '\a' << flush;
				cout << "An error has occured, error code: " << x << endl;
				errorCode(x);
			}

			//reprint this helpful stuff if you don't quit the program
			if (quitFlag == false) {
				cout << "\nTo view the help menu, enter HELP" << endl;
				cout << "To use the calculator, enter CALC" << endl;
				cout << "To view your previous answers, enter LIST" << endl;
				cout << "To use the floating point calculator, enter FLOATING" << endl;
				cout << "To end the program, enter QUIT" << endl;
			}
		}

		while (quitFlag == false);

	}
}

//method prints the help menu
void Menu::help() {
	string input;
	cout << "\nWhen you're done reading, enter BACK or QUIT" << endl;

	do {
		cout
				<< "\nHelp Menu\n\t1. About\n\t2. Formatting Guidelines\n\t3. The ANS keyword\n\t4. Other Information\nWhich topic would you like to view?"
				<< endl;
		cin >> input;
		try {

			if (stringToUpper(input) == "QUIT") {
				cout << "Goodbye!" << endl;
				quitFlag = true;
			} else if (stringToUpper(input) == "BACK") {
				//do nothing
			} else {
				if ((input != "1") && (input != "2") && (input != "3")
						&& (input != "4")) {
					throw 1;
				} else {
					switch (input.at(0)) {
					case '1':
						cout
								<< "\n\t1. About\n\tYou are using shizCALC, a symbolic calculator.\n\tThis project was developed by Eric, Ian, Josh, Matt, Morgan, and Qien.\n\t\tTo exit this program, enter QUIT from any screen.\n\t\tTo return to the main menu, enter BACK from any screen.\n\t\tTo evaluate expressions, enter CALC from the main menu.\n\t\tTo view previous solutions, enter LIST from the main menu."
								<< endl;
						break;

					case '2':
						cout
								<< "\n\t2. Formatting Guidelines\n\t\ta. Roots\n\t\t\tsqrt:x\n\t\t\tnrt:x\n\t\t\t\tExample: sqrt:64\n\t\t\t\tExample: 3rt:-27\n\t\tb. Logarithms\n\t\t\tlog_b:x\n\t\t\t\tExample: log_2:64\n\t\t\t\tExample: log_64:4\n\t\t\t\tExample: log_e:e\n\t\tc. Fractions\n\t\t\tn/d\n\t\t\t\tExample: 24/4 = -24/-4 = (20+4)/4\n\t\td. Exponents\n\t\t\tb^p\n\t\t\t\tExample: 6^2\n\t\t\t\tExample: (-3)^3 = -3^3\n\t\t\t\tExample: 4^(-2) = 4^-2\n\t\te. Spacing\n\t\t\tSpaces between operands are permissible but not required.\n\t\t\t\tExample: 2 + 3 = 2+3"
								<< endl;
						break;

					case '3':
						cout
								<< "\n\t3. The ANS keyword\n\tThe keyword ANS (or ans) can be used in the calculator to represent\n\tthe last solution the program provided. To check the current value of\n\tANS, simply type ANS into the calculator. To use it, type an expression such as\n\tANS^2 + 3. To change the keyword to any previous solution, visit the LIST\n\tmenu and choose the SET option."
								<< endl;
						break;

					case '4':
						cout
								<< "\n\t4. Other Information\n\t\tDelete this if we don't need it.\n\tsuch info\twow\n\t  much learn\n\tshiz\tvery help "
								<< endl;
						break;
					}
				}
			}

		} catch (int x) {
			cout << '\a' << flush;
			errorCode(x);
		}
	} while ((stringToUpper(input) != "BACK") && quitFlag == false);

}

//manipulate list of previous answers
void Menu::list() {

	string input;
	int index;

	//are there any answers in the vector yet?
	if (C.answerList.empty()) {
		cout << "\nTry using the calculator first.\n";
	}

	else {
		//automatically print up to 5 most recent answers
		cout << "\n";
		for (int i = 0; i < 5 && i < C.answerList.size(); i++) {
			cout << (i + 1) << ". " << C.expressionList[i] << " = "
					<< C.answerList[i] << endl;
		}
		cout << endl;

		//if there are more than 5 previous outputs in the vector allow the user to see the rest
		if (C.answerList.size() > 5) {
			cout << "To see the rest of the elements, enter MORE" << endl;
		}
		cout << "To set a previous answer as the ans keyword, enter SET"
				<< endl;
		cout<< "To see a previous answer to floating point form, enter FLOAT" << endl;
		cin >> input;
		input = stringToUpper(input);

		if (input == "MORE") {
			cout << "\n";
			//error check
			if (C.answerList.size() < 5) {
				cout << "There aren't any more answers to view!\n\n";
			} else {
				//print them
				for (int i = 5; i < C.answerList.size(); i++) {
					cout << (i + 1) << ". " << C.expressionList[i] << " = "
							<< C.answerList[i] << endl;
				}
				//gives option to set a previous output to ans keyword after viewing the entire list
				cout
						<< "\nTo set a previous answer as the ans keyword, enter SET\nOtherwise enter BACK"
						<< endl;
				cin >> input;
				input = stringToUpper(input);
				if (input == "SET") {
					setANS();
				} else if (input == "BACK") {

				} else if (input == "QUIT") {
					cout << "Goodbye!" << endl;
					quitFlag = true;
				} else {
					throw 1;
					cout << "That was not a valid input." << endl;
				}
			}

		}

		else if (input == "SET") {
			setANS();
		}
		else if(input == "FLOAT"){
			int index;
			cout << "\nWhich answer do you want to see as a floating point value?" << endl;
			cout << "Enter an integer from 1-" << C.answerList.size() << endl;
			while (!(cin >> index)) {
					cout << "\nThat wasn't an integer. Please enter an integer from 2-"
							<< C.answerList.size() << endl;
					cin.clear();
					//NEED TO FIX
				}
			if (index < 1 || index > C.answerList.size()) {
				throw 1;
				cout << "\nThat wasn't a valid input." << endl;
			}
			else {
				cout << C.convertToFloatingPoint(C.answerList[index - 1]) << endl;
			}
		}
		else if (input == "BACK") {

		}

		else if (input == "QUIT") {
			quitFlag = true;
			cout << "Goodbye!" << endl;
		}

		else {
			throw 1;
			cout << "That was not a valid input." << endl;
		}

	}
}

void Menu::setANS(){
	int index;

	cout << "\nWhich answer do you want to set to ANS?" << endl;
	cout << "Enter an integer from 2-" << C.answerList.size() << endl;

	while(!(cin >> index)){
		cout << "\nThat wasn't an integer. Please enter an integer from 2-" << C.answerList.size() << endl;
		cin.clear();
		//NEED TO FIX
	}

	//error check
	if (index < 2 || index > C.answerList.size()){
	    throw 1;
		cout << "\nThat wasn't a valid input." << endl;
	}

	else {
		C.answerList.insert(C.answerList.begin(), C.answerList[index-1]);
		C.expressionList.insert(C.expressionList.begin(), C.expressionList[index-1]);
		cout << "\nThe ANS keyword is now set to " << C.answerList[0] << "." << endl;
	}
}


//converts string input to uppercase
string Menu::stringToUpper(string convert) {
	for (int i = 0; i < convert.length(); i++) {
		int aVal = convert.at(i);
		if ((aVal < 123) && (aVal > 96)) {
			convert.at(i) = aVal - 32;
		}
	}
	return convert;
}

void Menu::title(){
	Calculator C;
	quitFlag = false;

}
