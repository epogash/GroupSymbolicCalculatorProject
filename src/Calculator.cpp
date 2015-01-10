/**************************
 Calculator.cpp
 ***************************/

#include "Calculator.h"

Calculator::Calculator() { //Instantiate an instance of calculator

}

string Calculator::evaluate(string expression) {//this is where we handle ANS
	string temp = expression;
	if (expression == "(ANS)" || expression == "(ans)") {
		expression = "ANS";
		evaluate(expression);
	}
	if (expression == "") {
		throw 1;
	} else if (expression.length() == 1) {
		if (expression.at(0) < 58 && expression.at(0) > 46) {
			cout << expression << endl;
			answerList.insert(answerList.begin(), expression);
			expressionList.insert(expressionList.begin(), temp);
		} else {
			throw 1;
		}
	} else if (matchedParen(expression) == false) {
		throw 2;
	} else if ((expression.at(0) == ('a') || expression.at(0) == ('A'))
			&& (expression.at(1) == ('n') || expression.at(1) == ('N'))
			&& (expression.at(2) == ('s') || expression.at(2) == ('S'))
			&& expression.length() == 3) {
		if (answerList.empty()) {
			throw 8;
		} else {
			cout << answerList[0] << endl;
		}

	} else {
		temp = replaceANS(temp);
		expression = removeSpaces(replaceSQRT(replaceANS(expression)));
		string result = theShiz(shuntingYard(expression));
#ifdef WIN32
		cout << "The answer is, windows :" << endl << result << endl;
#else
		cout << "The answer is, nonwindows :"<< endl << result << endl;
#endif
		answerList.insert(answerList.begin(), result);
		expressionList.insert(expressionList.begin(), temp);
		return result;
	}
	return "";
}

bool Calculator::matchedParen(string input) { //this is to make sure we have the same number of opening and closing paranthesis
	int openCount = 0;
	int closedCount = 0;

	for (int i = 0; i < input.length(); i++) {
		if (input.at(i) == '(') {
			openCount++;
		}
		if (input.at(i) == ')') {
			closedCount++;
		}
	}
	if (openCount == closedCount) {
		return true;
	} else {
		return false;
	}
}

bool Calculator::isFraction(string arg) { // this is to check if the argument is a fraction
	bool fraction = false;
	if(arg.length() < 3) {
		return false;
	}
	for (int i = 0; i < arg.length(); i++) {
		stringstream temp;
		if (arg.at(i) != '/') {
			temp << arg.at(i);
		}
		if (!isNumber(temp.str()) && arg.at(i) != '/') {
			return false;
		}

		if (arg.at(i) == '/')
			fraction = true;
	}
	return fraction;
}
//OBSOLETE*
bool Calculator::isSqRoot(std::string arg) { //this is to chekc is something is a sqrt
	if (arg.at(0) == 's' && arg.at(1) == 'q' && arg.at(2) == 'r'
			&& arg.at(3) == 't' && arg.at(4) == ':') { //checking if the charcters are in the write order
		if (arg.at(5) == '-') {
			throw 7;
			cout << "Error can't sqrt neg";
		}
		return true;
	}
	return false;
}
//

bool Calculator::isLog(string arg) { // this is to check if something is a log
	if (arg.length() < 7) {
		return false;
	}
	if (arg.at(0) == 'l' && arg.at(1) == 'o' && arg.at(2) == 'g' // checking if the characters are in the right order
			&& arg.at(3) == '_') {
		for (int i = 5; i < arg.length() - 1; i++) {
			if (arg.at(i) == ':') {
				return true;
			}
		}
	}
	return false;
}
bool Calculator::isNumber(string arg) { // this is to check if the argument is a number
	for (int i = 0; i < arg.length(); i++) {
		if (!((arg.at(i) <= '9') && (arg.at(i) >= '0')) && arg.at(0) != '-') { //-sign are ignored because we dont want the test to fail b/c the number is negative
			return false;
		}
		if (arg[i] == '/') {
			return false;
		}
	}

	return true;
}

bool Calculator::isOperator(string input) { // this is where we check if the argument is a mathmatical argument other than a root or a log
	if ((input[0] == '-' && input.length() == 1) || input[0] == '+'
			|| input[0] == '*' || input[0] == '/' || input[0] == '^') {
		return true;
	} else {
		return false;
	}
}

bool Calculator::isNRT(std::string arg) { // this is where we check for roots other than sqrt
	for (int i = 0; i < arg.length(); i++) {
		if ((arg.at(i) == '-' && (i != 0 && arg.at(i - 1) != ':'))
				|| arg.at(i) == '+') {
			return false;
		}
	}
	for (int i = 0; i < arg.length(); i++) {
		if (((arg.length() - i) >= 3)
				&& (arg.at(i) == 'r' && arg.at(i + 1) == 't'
						&& arg.at(i + 2) == ':')) {
			return true;
		}
	}
	return false;
}

bool Calculator::isFloatingPoint(string arg) { // this is a part of the bonus method  and checks whether input is a floating point or not

	bool isFloating = false;
	for (int i = 1; i < arg.length(); i++) {
		if (arg.at(i) == '.') {
			isFloating = true;
		}
	}
	if (!isFloating) {
		return false;
	}
	stringstream beforeDecimal;
	stringstream afterDecimal;
	int i = 0;
	for (; i < arg.length(); i++) {
		if (arg.at(i) == '.') {
			++i;
			break;
		}
		beforeDecimal << arg.at(i);
	}
	for (; i < arg.length(); i++) {
		afterDecimal << arg.at(i);
	}
	if (beforeDecimal.str().at(0) == '-') {
		beforeDecimal.str("");
		for (int i = 1; i < arg.length(); i++) {
			if (arg.at(i) == '.') {
				++i;
				break;
			}
			beforeDecimal << arg.at(i);
		}
	}

	if (isNumber(beforeDecimal.str()) && isNumber(afterDecimal.str())) {
		return true;
	}
	return false;
}

int Calculator::fractionNum(string arg) { // this method return the numerator of the fraction
	stringstream ss;
	int num;
	string temp;
	for (int i = 0; i < arg.size(); i++) {
		if (arg.at(i) == '/') {
			temp = ss.str();
			num = atoi(temp.c_str());
			return num;
		} else {
			ss << arg.at(i);
		}
	}
	temp = ss.str();
	num = atoi(temp.c_str());
	return num;
}

int Calculator::fractionDenom(string arg) { // this method returns the denominator of a fraction
	stringstream ss;
	int denom;
	string temp;
	for (int i = 0; i < arg.size(); i++) {
		if (arg.at(i) == '/') {
			for (int j = i + 1; j < arg.size(); j++) {
				ss << arg.at(j);
			}
		}
	}
	temp = ss.str();
	denom = atoi(temp.c_str());
	return denom;
}

int Calculator::rootIndex(string arg) { // this method returns the root index of a root(sqrt would return 2)
	stringstream ss;
	int index;
	string temp;
	for (int i = 0; i < arg.size(); i++) {
		if (arg.at(i) == 'r') {
			temp = ss.str();
			index = atoi(temp.c_str());
			return index;

		} else if (arg.at(i) == '*') {
			ss.str("");
		} else {
			ss << arg.at(i);
		}
	}

}

int Calculator::rootRadicand(string arg) { // this method returns the radicand or argument of the root
	stringstream ss;
	int radicand;
	string temp;
	for (int i = 0; i < arg.size(); i++) {
		if (arg.at(i) == ':') {
			for (int j = i + 1; j < arg.size(); j++) {
				ss << arg.at(j);

			}
		}

	}

	temp = ss.str();
	radicand = atoi(temp.c_str());
	return radicand;
}

int Calculator::findCoeff(string arg) { // if we have a constant value such as pi or e(this can also be used in other ways) this returns its coefficient
	stringstream ss;
	string temp;
	int value;
	for (int i = 0; i < arg.size(); i++) {
		if (arg.at(i) == '*') {
			break;
		} else if (arg.at(i) <= 'z' && arg.at(i) >= 'a') {
			ss.str("1");
			break;
		} else if (arg.at(0) == '-') {
			ss.str("1");
		}
		ss << arg.at(i);

	}
	temp = ss.str();
	value = atoi(temp.c_str());
	return value;

}

int Calculator::findBase(string arg) { // this return the base of a log
	stringstream ss;
	int radicand;
	string temp;
	for (int i = 0; i < arg.size(); i++) {
		if (arg.at(i) == '_') {
			for (int j = i + 1; j < arg.size(); j++) {
				if (arg.at(i) == ':') {
					break;
				}
				ss << arg.at(j);

			}
		}

	}

	temp = ss.str();
	radicand = atoi(temp.c_str());
	return radicand;
}

string Calculator::findConstVal(string arg) { // if we have a constant with a coefficient this returns the constant
	stringstream ss;
	string constant;
	stringstream soClose;
	int coeff = findCoeff(arg);
	if (coeff != 1) {
		ss << coeff;
		string yada = ss.str();
		int toIgnore = yada.size();
		bool inParanthesis = false;
		bool endofCBool = false;
		for (int i = toIgnore + 1; i < arg.size(); i++) {
			soClose << arg.at(i);
			constant = soClose.str();
		}
	} else if (coeff == 1) {
		constant = arg;
	}
	return constant;
}

int Calculator::getPriority(string input) { // this is where the set the token values for the shunting yard algorithm
	int priority;
	if (input[0] == ('+') || input[0] == ('-')) {
		priority = 0;
	} else if (input[0] == ('*') || input[0] == ('/')) {
		priority = 1;
	} else if (input[0] == ('^')) {
		priority = 2;
	} else {
		throw 1;
		cout << "invalid output" << endl;
	}
	return priority;
}

bool Calculator::ifPop(string input, string input2) { // this returns true or false depending on the token priority and helps maintain the order of operations
	return getPriority(input) <= getPriority(input2);
}

string Calculator::addFloating(string arg1, string arg2) { // this method is for adding floating points and is apart of our bonus methods
	double float1 = atof(arg1.c_str());
	double float2 = atof(arg2.c_str());
	stringstream ss;
	double answer = float1 + float2;
	ss << answer;
	return ss.str();
}

string Calculator::multiplyFloating(string arg1, string arg2) { // this method is for multiplying floating points and is apart of our bonus methods
	double float1 = atof(arg1.c_str());
	double float2 = atof(arg2.c_str());
	stringstream ss;
	double answer = float1 * float2;
	ss << answer;
	return ss.str();
}

string Calculator::subtractFloating(string arg1, string arg2) { // this method is for subtracting floating points and is apart of our bonus methods
	double float1 = atof(arg1.c_str());
	double float2 = atof(arg2.c_str());
	stringstream ss;
	double answer = float2 - float1;
	ss << answer;
	return ss.str();
}
string Calculator::divideFloating(string arg1, string arg2) { // this methods is for dividing floating points and is apart of our bonus methods
	double float1 = atof(arg1.c_str());
	double float2 = atof(arg2.c_str());
	stringstream ss;
	double answer = float2 / float1;
	ss << answer;
	return ss.str();
}

string Calculator::exponentiateFloating(string arg1, string arg2) { // this method is for exponentiating floating points and is apart of our bonus methods
	double float1 = atof(arg1.c_str());
	double float2 = atof(arg2.c_str());
	stringstream ss;
	double answer = pow(float2, float1);
	ss << answer;
	return ss.str();
}
string Calculator::shuntingYard(string expression) {
//**********MAKE STRING OF VECTORS FROM INPUT***************
	vector<string> objectList;
	string object;
	string result;
	bool isOne = true;
	if (expression.at(0) == '*' || expression.at(0) == '/'
			|| expression.at(0) == '+' || expression.at(0) == '^') {
		throw 999;
		cout << "error" << endl;
	}

	//check to see if there are operators, if not then it's one number or function
	if (expression.length() > 1) {
		for (int i = 1; i < expression.length(); i++) {
			if (expression.at(i) == '*'
					|| (expression.at(i) == '-' && expression.at(i - 1) != ':')
					|| expression.at(i) == '/' || expression.at(i) == '+'
					|| expression.at(i) == '^') {
				isOne = false;
				break;
			}
		}
	}
	if (isOne && (!isLog(expression) && !isNRT(expression))
			&& !isFloatingPoint(expression)) {
		return expression;
	}

	if (isOne && isLog(expression)) { //evaluate a single log
		isOne = false;

		stringstream ss;
		stringstream ss2;
		int i = 0;
		//start after log_ then store the integer, which is the base
		for (i = 4; expression.at(i) != ':'; i++) {
			ss << expression.at(i);
		}
		int j = i + 1;
		//read after base and after ':', so it is the 'value' property of the log
		for (++i; i < expression.length(); i++) {
			ss2 << expression.at(i);
		}
		//Construct First Log
		if (isNumber(ss.str()) && isNumber(ss2.str())) {

			int base = atoi(ss.str().c_str());
			int value = atoi(ss2.str().c_str());
			Log *result1;
			if (base <= 1) {
				throw 6;
			} else if (value <= 0) {
				throw 5;
			} else if (base > value) {
				result1 = new Log(value, base);
				expression = result1->toString();
			} else {
				result1 = new Log(base, value);
				expression = result1->toString();
			}
			//check if multiples > 1 then do shunting yard, otherwise dont
			if (base == value) {
				result = shuntingYard("1");
				return result;
			} else if (result1->valueMultiples > 1 && base < value) {
				return shuntingYard(expression);
			} else if (result1->valueMultiples > 1 && base > value) {
				expression = shuntingYard(expression);
				expression = "1/" + expression;
				return expression;
			} else {
				if (base > value) {
					return "1/" + expression;
				} else {
					return expression;
				}
			}
		} else {
			stringstream ss3;

			if (expression.at(j) == '(') {
				for (j = j + 1; expression.at(j) != ')'; j++) {
					ss3 << expression.at(j);
				}
				if (ss3.str() == ss.str()) {
					return "1";
				}
				if (isNumber(ss3.str())) {
					int base = atoi(ss.str().c_str());
					int value = atoi(ss3.str().c_str());
					Log *result = new Log(base, value);
					expression = result->toString();
					return expression;
				} else {
					return "(" + expression + ")";
				}
			}
			if (ss.str() == ss2.str()) {
				return "1";
			}
			return expression;
		}

	}

	if (isOne && isNRT(expression)) { //evaluate a single root
		isOne = false;
		if (rootIndex(expression) < 0) {

			stringstream si;
			si << "-1/" << abs(rootIndex(expression));
			stringstream ss;
			ss << rootRadicand(expression);
			return exponentiate(si.str(), ss.str());
		} else {
			Root *root = new Root(findCoeff(expression), rootIndex(expression),
					rootRadicand(expression));
			root->simplify();
			return root->toString();

		}
	} else if (isOne && isFloatingPoint(expression)) { //convert a floating point number to a simplified fraction
		int i = 0;
		stringstream beforeDecimal;
		stringstream afterDecimal;
		for (; i < expression.length(); i++) {
			if (expression.at(i) == '.') {
				++i;
				break;
			}
			beforeDecimal << expression.at(i);
		}
		int numberOfDecimalPlaces = expression.length() - i;
		for (; i < expression.length(); i++) {
			afterDecimal << expression.at(i);
		}

		string num = beforeDecimal.str() + afterDecimal.str();
		int numerator = atoi(num.c_str());
		beforeDecimal.str("");
		afterDecimal.str("");
		int tensMultiple = 1;
		for (i = 0; i < numberOfDecimalPlaces; i++) {
			tensMultiple *= 10;
		}
		Fraction *decimalFraction = new Fraction(numerator, tensMultiple);
		decimalFraction->simplify();
		string result = decimalFraction->toString();
		return result;
	}

	object += expression.at(0);
	if (object.at(0) == '(') {
		objectList.push_back(object);
		object = "";
	}
	for (int i = 1; i < expression.length(); i++) {
		if (expression.at(i) == '-'
				&& (expression.at(i - 1) == '+' || expression.at(i - 1) == '*'
						|| expression.at(i - 1) == '-'
						|| expression.at(i - 1) == '/'
						|| expression.at(i - 1) == '^'
						|| expression.at(i - 1) == '('
						|| expression.at(i - 1) == ':')) {
			object += expression.at(i);
		} else if (expression.at(i) != '+' && expression.at(i) != '-'
				&& expression.at(i) != '*' && expression.at(i) != '/'
				&& expression.at(i) != '^' && expression.at(i) != '('
				&& expression.at(i) != ')') {
			object += expression.at(i);
			if (i == (expression.length() - 1)) {
				objectList.push_back(object);
			}
		} else {
			if (object != "") {
				objectList.push_back(object);
				object = "";
			}
			string nextOperator(1, expression.at(i));
			objectList.push_back(nextOperator);
		}

	}
	vector<string> input = objectList;

	//simplify all logs and floating points before converting to reverse polish notation and calculating
	for (int i = 0; i < input.size(); i++) {
		if (expression.at(i) != '+'
				&& (expression.at(i) != '-' || isFloatingPoint(input[i]))
				&& expression.at(i) != '*' && expression.at(i) != '/'
				&& expression.at(i) != '^' && expression.at(i) != '('
				&& expression.at(i) != ')') {
			if (isLog(input[i]) || isFloatingPoint(input[i])) {
				input[i] = shuntingYard(input[i]);
			}
		}
	}
//***********************CONVERT TO REVERSE POLISH NOTATION**************************
	queue<string> output;
	stack<string> o_perator;
	for (int i = 0; i < input.size(); i++) {
		if (isOperator(input[i]) && input[i].length() == 1) {

			if (o_perator.empty()) {
				o_perator.push(input[i]);
			} else {
				if (o_perator.top() == "(") {
					o_perator.push(input[i]);
				} else if (ifPop(input[i], o_perator.top())) {
					output.push(o_perator.top());
					o_perator.pop();
					o_perator.push(input[i]);
				} else {
					o_perator.push(input[i]);
				}
			}
		} else if (input[i] == "(") {
			o_perator.push(input[i]);
		} else if (input[i] == ")") {
			//pop and push onto queue until left parentheses is hit
			while (o_perator.top() != "(") {
				output.push(o_perator.top());
				o_perator.pop();
				//if there is a closed parentheses
			}
			if (o_perator.size() >= 1) {
				//pop left parentheses from stack, don't push onto output queue
				o_perator.pop();
			} else {
				throw 2;
				cout << "Throw Error: Mismatched parentheses" << endl;
			}

		} else {
			output.push(input[i]);
		}
	}

	for (stack<string> dump = o_perator; !dump.empty(); dump.pop()) {
		output.push(dump.top());
	}

	//Calculate from RPN 
	stack<string> theStack;
	int i = 0;
	result = "";
	for (queue<string> dump = output; !dump.empty(); dump.pop()) {

		if (isOperator(dump.front()) && i != 0) {
			string op = dump.front();
			//Assuming 2 operands used
			if (theStack.size() < 2) {
				throw 4;
				cout
						<< "Error: There are not enough values for the expression. first"
						<< endl;
			} else {
				string arg1 = theStack.top();
				theStack.pop();
				string arg2 = theStack.top();
				theStack.pop();
				if (op == "+")
					result = add(arg1, arg2);
				else if (op == "-")
					result = subtract(arg1, arg2);
				else if (op == "*")
					result = multiply(arg1, arg2);
				else if (op == "^")
					result = exponentiate(arg1, arg2);
				else if (op == "/")
					result = divide(arg1, arg2);
				//push to stack the result of operation
				stringstream ss;
				ss << result;
				theStack.push(ss.str());

			}
		} else {
			theStack.push(dump.front());
		}
		i++;
	}
	if (theStack.size() == 1) {
		return theStack.top();
	} else if (theStack.size() == 2) {
		string result1 = theStack.top();
		theStack.pop();
		result = theStack.top() + "(" + result1 + ")";
		if (!isNumber(result1)) {
			return result;
		}
		if (isLog(result) && isNumber(result1)) {
			result = shuntingYard(result);
			return result;
		} else if (isLog(result) && !isNumber(result)) {
			return result;
		} else {
			throw 4;
			cout << "Error: not enough values for expression to be solved"
					<< endl;
			return "";
		}
	} else {
		throw 4;
		cout << "Error: There are not enough values for the expression."
				<< endl;
		return "";
	}
}

string Calculator::theShiz(string expression) { // this method accomplishes two things it simulataneously simplifies constant addition as well as recursively calls shunting yard after moving like terms together
	//**********MAKE VECTOR OF STRINGS FROM INPUT***************
	vector<string> objectList;
	string object;
	string result;
	if (expression.at(0) == '*' || expression.at(0) == '/' // the leading character cant be an operator
			|| expression.at(0) == '+' || expression.at(0) == '^') {
		throw 999;
		cout << "error" << endl;
	}
	object += expression.at(0);
	if (object.at(0) == '(') {
		objectList.push_back(object);
		object = "";
	}
	if (expression.length() > 1) { // the following code creates a vector of strings separated by + and - signs
		for (int i = 1; i < expression.length(); i++) {
			if (expression.at(i) != '+'
					&& ((expression.at(i) == '-' && expression.at(i - 1) == ':')
							|| (expression.at(i) != '-')) /*&& expression.at(i) != '(' && expression.at(i) != ')'*/) {
				object += expression.at(i);
				if (i == (expression.length() - 1)) {
					objectList.push_back(object);
				}
			} else {
				if (object != "") {
					objectList.push_back(object);
					object = "";
				}
				string nextOperator(1, expression.at(i));
				objectList.push_back(nextOperator);
			}

		}
	} else {
		return expression;
	}
	vector<string> input = objectList;

	if(input.size() == 1){ //if the input size is one and there aren't any multiplication or divide signs then we dont need to reorganize the vector and recall shunting yard
	        bool mult = false;
	        for(int i=0; i<input[0].length(); i++){
	            if(input[0].at(i) == '*' || input[0].at(i) == '/'){
	                mult = true;
	            }
	        }
	        if(mult == false){
	            return input[0];
	        }
		}

	vector<string> reOrgedVector;
	vector<string> temp;
	for (int i = 0; i < input.size(); i++) { //in this for loop we are setting the temp equal to the input vector then pushing all the non-constant terms onto the new vector
		string tempoop = input[i];
		temp.push_back(tempoop);
		if (!isOperator(temp[i])
				&& (isNumber(temp[i]) || isFraction(temp[i]))) {
			if (i == 0) {
				reOrgedVector.push_back(temp[i]);
			} else {
				reOrgedVector.push_back(temp[i - 1]);
				reOrgedVector.push_back(temp[i]);

			}
		}

	}
	vector<string> constVector; //going to store constants here...they will be simplified then added to
	for (int i = 0; i < temp.size(); i++) { //in this for loop pushing all constant terms to end of new vector
		int tempCounter = 0;
		string constant = temp[i];
		stringstream tempConstant;
		if (!isNumber(constant) && !isFraction(constant)
				&& !isOperator(constant)) {
			for (int j = 0; j < temp.size(); j++) {
				if (findConstVal(constant) == findConstVal(temp[j])) {
					if (j != 0 && temp[j - 1] == "-") {
						tempCounter -= findCoeff(temp[j]);
					} else {
						tempCounter += findCoeff(temp[j]);

					}
					temp.erase(temp.begin() + j);
				}
			}
			if (tempCounter > 1) {
				tempConstant << "+" << tempCounter << "*"
						<< findConstVal(constant);
				reOrgedVector.push_back(tempConstant.str());
			} else if (tempCounter == 1) {
				tempConstant << "+" << findConstVal(constant);
				reOrgedVector.push_back(tempConstant.str());
			} else if (tempCounter < 0) {
				tempConstant << tempCounter << "*" << findConstVal(constant);
				reOrgedVector.push_back(tempConstant.str());
			} else {

			}
		}

		else {
			//temp.erase(temp.begin()+j);

		}

		//i--;
	}

	stringstream exp1;
	if (reOrgedVector[0].at(0) == '+') { // if the first term of the vector is a plus sign we can delete it
		reOrgedVector[0].erase(reOrgedVector[0].begin());
	}
	if (reOrgedVector[0] == "+") {
		reOrgedVector.erase(reOrgedVector.begin());
	}
	for (int i = 0; i < reOrgedVector.size(); i++) { // we store the reorganized vector in a string
		exp1 << reOrgedVector[i];
	}

	string exp2 = shuntingYard(exp1.str()); // if set expression 2 to a potentially more simplified expression 1

	if (exp2 != exp1.str()) { // if expression one wasn't simplified at all then we have simplified as much as we can if not then we rerun our method to see if it simplifies further
		return theShiz(exp2);
	}
	return exp1.str();
}

string Calculator::convertToFloatingPoint(string expression) { // this is where input is converted to a floating point and where a slightly edited shunting yard will handle them
	const string e = "2.718281828";
	const string pi = "3.141592654";
	Calculator *calculator = new Calculator();
	//CONVERT TO VECTOR OF STRINGS

	vector<string> objectList;
	string object;
	string result;

	object += expression.at(0);
	if (object.at(0) == '(') {
		objectList.push_back(object);
		object = "";
	}
	if (expression.length() > 1) {
		for (int i = 1; i < expression.length(); i++) { //string of vectors is formed, divided and indexed based on operators
			if (expression.at(i) == '-'
					&& (expression.at(i - 1) == '+'
							|| expression.at(i - 1) == '-'
							|| expression.at(i - 1) == '*'
							|| expression.at(i - 1) == '/'
							|| expression.at(i - 1) == '^'
							|| expression.at(i - 1) == '('
							|| expression.at(i - 1) == ':')) {
				object += expression.at(i);
			} else if (expression.at(i) != '+' && expression.at(i) != '*'
					&& expression.at(i) != '/' && expression.at(i) != '^'
					&& expression.at(i) != '(' && expression.at(i) != ')') {
				object += expression.at(i);
				if (i == (expression.length() - 1)) {
					objectList.push_back(object);
				}
			}

			else {
				if (object != "") {
					objectList.push_back(object);
					object = "";
				}
				string nextOperator(1, expression.at(i));
				objectList.push_back(nextOperator);
			}

		}
	} else {
		objectList.push_back(object);
	}
	vector<string> input = objectList;

	for (int i = 0; i < input.size(); i++) {

		if (isFraction(input[i])) {  //check each string, and simplify it if it is a fraction, log, e, pi, or nthroot, converting to its respective floting point form
			int num1 = fractionNum(input[i]);
			int den1 = fractionDenom(input[i]);
			float ans = (float) num1 / den1;
			stringstream ss;
			ss << ans;
			result = ss.str();
			input[i] = result;
		} else if (isLog(input[i])) {
			double base = findBase(input[i]);
			double value = rootRadicand(input[i]);

			double ans = log(value) / log(base);
			stringstream ss;
			ss << ans;
			result = ss.str();
			input[i] = result;
		} else if (input[i] == "e") {
			input[i] = e;
		} else if (input[i] == "pi") {
			input[i] = pi;
		} else if (isNRT(input[i])) {
			double radicand = rootRadicand(input[i]);
			double index = rootIndex(input[i]);
			double nthRoot = pow(radicand, 1.0 / index);
			stringstream ss;
			ss << nthRoot;
			result = ss.str();
			input[i] = result;
		}
	}
	queue<string> output;
	stack<string> o_perator;
	for (int i = 0; i < input.size(); i++) {
		if (isOperator(input[i]) && input[i].length() == 1) {

			if (o_perator.empty()) {
				o_perator.push(input[i]);
			} else {
				if (o_perator.top() == "(") {
					o_perator.push(input[i]);
				} else if (ifPop(input[i], o_perator.top())) {
					output.push(o_perator.top());
					o_perator.pop();
					o_perator.push(input[i]);
				} else {
					o_perator.push(input[i]);
				}
			}
		} else if (input[i] == "(") {
			o_perator.push(input[i]);
		} else if (input[i] == ")") {
			//pop and push onto queue until left parentheses is hit
			while (o_perator.top() != "(") {
				output.push(o_perator.top());
				o_perator.pop();
				//if there is a closed parentheses
			}
			if (o_perator.size() >= 1) {
				//pop left parentheses from stack, don't push onto output queue
				o_perator.pop();
			} else {
				cout << "Throw Error: Mismatched parentheses" << endl;
			}
		} else {
			output.push(input[i]);
		}
	}

	for (stack<string> dump = o_perator; !dump.empty(); dump.pop()) {
		output.push(dump.top());
	}
	stack<string> theStack;
	int i = 0;
	result = "";
	for (queue<string> dump = output; !dump.empty(); dump.pop()) {
		if (isOperator(dump.front()) && i != 0) {
			string op = dump.front();
			//Assuming 2 operands used
			if (theStack.size() < 2) {
				cout
						<< "Error: There are not enough values for the expression. first"
						<< endl;
			} else {
				string arg1 = theStack.top();
				theStack.pop();
				string arg2 = theStack.top();
				theStack.pop();
				//use floating point methods to convert to floating point forms
				if (op == "+")
					result = addFloating(arg1, arg2);  
				else if (op == "-")
					result = subtractFloating(arg1, arg2);
				else if (op == "*")
					result = multiplyFloating(arg1, arg2);
				else if (op == "^")
					result = exponentiateFloating(arg1, arg2);
				else if (op == "/")
					result = divideFloating(arg1, arg2);
				//push to stack the result of operation
				stringstream ss;
				ss << result;
				theStack.push(ss.str());

			}
		} else {

			theStack.push(dump.front());
		}
		i++;
	}
	if (theStack.size() == 1) {
		return theStack.top();
	} else {
		cout << "Error: There are not enough values for the expression."
				<< endl;
		return "";
	}
}

string Calculator::removeSpaces(string input) { // rather than handle spaces they are removed before the input is handled
	string output = "";
	for (int i = 0; i < input.length(); i++) {
		if (input.at(i) != ' ') {
			output += input.at(i);
		}
	}
	return output;
}

string Calculator::replaceSQRT(string input) { // rather than hand sqrt and nrt separately we replace sqrt with 2rt
	for (int i = 0; i < (input.length()); i++) {
		if (input.at(i) == 's' || input.at(i) == 'S') {
			if (input.at(i + 1) == 'q' || input.at(i + 1) == 'Q') {
				if (input.at(i + 2) == 'r' || input.at(i + 2) == 'R') {
					if (input.at(i + 3) == 't' || input.at(i + 3) == 'R') {
						input.at(i) = '2';
						input.at(i + 1) = ' ';
					}
				}
			}

		}
	}
	return input;
}

bool Calculator::foundANS(string expression) { // a boolean to check and make sure we found the old answer fromt the vector
	bool isUsed = false;
	for (int i = 0; i < (expression.length() - 2); i++) {
		if ((expression.at(i) == 'a') || (expression.at(i)) == 'A') {
			if ((expression.at(i + 1) == 'n')
					|| (expression.at(i + 1) == 'N')) {
				if ((expression.at(i + 2) == 's')
						|| (expression.at(i + 2) == 'S')) {
					isUsed = true;

				}
			}
		}
	}
	return isUsed;
}

string Calculator::replaceANS(string expression) { // a method to replace what the ans command will return
	if (foundANS(expression) == false) {
		return expression;
	} else {
		for (int i = 0; i < (expression.length() - 2); i++) {
			if ((expression.at(i) == 'a') || (expression.at(i)) == 'A') {
				if ((expression.at(i + 1) == 'n')
						|| (expression.at(i + 1) == 'N')) {
					if ((expression.at(i + 2) == 's')
							|| (expression.at(i + 2) == 'S')) {
						string string1 = expression.substr(0, i);
						string string2 = expression.substr((i + 3),
								(expression.length() - 1));
						string newstring = string1 + "(" + answerList[0] + ")"
								+ string2;
						return replaceANS(newstring);
					}
				}
			}
		}
	}
}
