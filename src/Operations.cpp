#include "Calculator.h"
/**************************
Operations.cpp
***************************/

string Calculator::add(string arg1, string arg2){

	int numResult;
	string result;
	//INTEGER CASES
	if(isNumber(arg1) && isNumber(arg2)){             
	    int num1 = atoi(arg1.c_str());                 //pulls out ints from string input
	    int num2 = atoi(arg2.c_str());
	    numResult = num2 + num1;                   //adds the ints together
	    stringstream ss;
	    ss << numResult;
	    result = ss.str();                                   //converts result back to string and returns it
	    return result;
	}
	//FRACTION CASES
	else if(isFraction(arg1) && isNumber(arg2)){
      return add(arg2, arg1);                                    //this recalls the add method if arg1 was a fraction and arg2 an integer so i only have to handle arg1 being an int and arg2 being a fraction
    }
    else if(isNumber(arg1) && isFraction(arg2)){                                //if int and fract
    	int numInt;
        int denInt;//then cast them into the proper int variable
        numInt = fractionNum(arg2);                                                          //converts to ints for calculation
        denInt = fractionDenom(arg2);
		int arg=atoi(arg1.c_str());
		int combinedNum= (arg*denInt)+numInt;
		Fraction *fraction=new Fraction(combinedNum, denInt);               //creates new fraction object using new numerator and denominator
		fraction->simplify();                                                                 //simplifies the fraction
		result=fraction->toString();                                                   //makes the fraction a string to return it
		return result;
        }

    else if (isFraction(arg1) && isFraction(arg2)){                  //dividing fractions
    	stringstream ss;
        int num1 = fractionNum(arg1);
        int den1 = fractionDenom(arg1);
    	int num2 = fractionNum(arg2);
        int den2 = fractionDenom(arg2);

        if (den1 != den2){                                     //if denominators arent equal
        	num1 = num1*den2;
        	num2 = num2*den1;
        	den1 = den1*den2;
        	den2 = den1;
        }
        if (den1 == den2){                                     //if denominators are equal
        	num1 = (num1+num2);
        	num2 = den1;
    		Fraction *fraction = new Fraction(num1, num2);             //creates new fraction object with correct num and denom
    		fraction->simplify();
    		result=fraction->toString();
        	return result;                                            //returns result
        }
    }

    else if(isNumber(arg1) && isLog(arg2)){                       //adding int to log
    	stringstream ss;
    	stringstream ss2;
    	int i = 0;
    	//start after log_ then store the integer, which is the base
    	for(i = 4; arg2.at(i) != ':'; i++){
    	  	ss << arg2.at(i);
    	}

    	//read after base and after ':', so it is the 'value' property of the log
    	for(++i; i < arg2.length(); i++){
    	   	ss2 << arg2.at(i);
    	}
    	//Construct First Log
    	if(isNumber(ss.str()) && isNumber(ss2.str())){
    	    int base = atoi(ss.str().c_str());
    	    int value = atoi(ss2.str().c_str());
    	    Log *result = new Log(base,value);
    	    arg2 = result->toString();
    	    if(result->valueMultiples > 1) {
    	    	arg2 = shuntingYard(arg2);
    	    }
    	}
    	string finalResult = arg2 + "+" + arg1;
    	//if both numbers then add them
    	if(isNumber(arg1) && isNumber(arg2)){
    	  	finalResult = shuntingYard(finalResult);
    	}
    	return finalResult;
    }
    else if(isLog(arg1) && isNumber(arg2)){
    	stringstream ss;
    	stringstream ss2;
    	    	int i = 0;
    	    	//start after log_ then store the integer, which is the base
    	    	for(i = 4; arg1.at(i) != ':'; i++){
    	    	  	ss << arg1.at(i);
    	    	}

    	    	//read after base and after ':', so it is the 'value' property of the log
    	    	for(++i; i < arg1.length(); i++){
    	    	   	ss2 << arg1.at(i);
    	    	}
    	    	//Construct First Log
    	    	if(isNumber(ss.str()) && isNumber(ss2.str())){
    	    	    int base = atoi(ss.str().c_str());
    	    	    int value = atoi(ss2.str().c_str());
    	    	    Log *result = new Log(base,value);
    	    	    arg1 = result->toString();
    	    	    if(result->valueMultiples > 1) {

    	    	    	arg1 = shuntingYard(arg1);
    	    	    }
    	    	}
    	    	string finalResult = arg2 + "+" + arg1;
    	    	//if both numbers then add them
    	    	if(isNumber(arg1) && isNumber(arg2)){
    	    	  	finalResult = shuntingYard(finalResult);
    	    	}
    	    	return finalResult;
    }

	else if(isNRT(arg1) && isNRT(arg2)){                                           //adding roots together

    	Root *root1=new Root(findCoeff(arg1), rootIndex(arg1), rootRadicand(arg1));       //these methods create roots from the args passed in
    	Root *root2=new Root(findCoeff(arg2), rootIndex(arg2), rootRadicand(arg2));

    	root1->simplify();          //simplify the roots as far as possible
    	root2->simplify();

    	if(root1->getIndex() == root2->getIndex() && root1->getRadicand() == root2->getRadicand()){           //if the index and radicand for both roots is the same, we add the int values outside the radical together
    		if(root1->getRadicand() == 1){
    			int value = root1->getValue() + root2->getValue();
				stringstream ss;
				ss << value;
				return ss.str();

    		}

    		int value = root1->getValue() + root2->getValue();
    		stringstream ss;
    		ss << value << "*" << root1->getIndex() << "rt:" << root1->getRadicand();
    		return ss.str();
    	}


    	string result = root2->toString() + "+" + root1->toString();                  //if the index or radicand arent equal, return a string the simply concatinates the two roots

    	return result;

   }

	else {
				result = arg2 + "+" + arg1;               //if we end up with some strange, otherwise un-handleable case, we simply return the expression to the user
				return result;
			}

}

string Calculator::subtract(string arg1, string arg2){                                 //most of these cases are very similar to the add method
	int numResult;
	string result;
	if(isNumber(arg1) && isNumber(arg2)){
	    int num1 = atoi(arg1.c_str());
	    int num2 = atoi(arg2.c_str());
	    numResult = num2 - num1;
	    stringstream ss;
	    ss << numResult;
	    result = ss.str();
	    return result;
	}else if(isFraction(arg1) && isNumber(arg2)){
        int valArg2=atoi(arg2.c_str());
        int num;
        int denom;
        num=fractionNum(arg1);
        denom=fractionDenom(arg1);
        int combNum=(valArg2*denom)-num;
        Fraction *fraction=new Fraction(combNum, denom);
        fraction->simplify();
        result=fraction->toString();
        return result;
    }else if(isFraction(arg2) && isNumber(arg1)){
        int valArg1=atoi(arg1.c_str());
        int num;
        int denom;
        num=fractionNum(arg2);
        denom=fractionDenom(arg2);
        int combNum=num-(valArg1*denom);
        Fraction *fraction=new Fraction(combNum, denom);
        fraction->simplify();
        result=fraction->toString();
        return result;
    }else if(isFraction(arg1) && isFraction(arg2)){
        int num1=fractionNum(arg1);
        int num2=fractionNum(arg2);
        int denom1=fractionDenom(arg1);
        int denom2=fractionDenom(arg2);
        int newNum1=num1*denom2;
        int newDenom1=denom1*denom2;
        num2=num2*denom1;
        int combNum=num2-newNum1;
        Fraction *fraction=new Fraction(combNum,newDenom1);
        fraction->simplify();
        result=fraction->toString();
        return result;

    }
	else {
		result = arg2 + "-" + arg1;
		return result;
	}
}

string Calculator::multiply(string arg1, string arg2){
	int numResult;
	string result;
	if(isNumber(arg1) && isNumber(arg2)){
		 int num1 = atoi(arg1.c_str());
		 int num2 = atoi(arg2.c_str());
		 numResult = num2 * num1;                                              //reads in strings, converts to ints, multiplies them, converts the answer back to string, and returns it
		 stringstream ss;
		 ss << numResult;
		 result = ss.str();
		 return result;
	}
	if(isNumber(arg2)&&isFraction(arg1)){
        return multiply(arg2, arg1);
	}
	if(isNumber(arg1)&&isFraction(arg2)){
        int num=fractionNum(arg2);
        int denom=fractionDenom(arg2);
        int arg1Val=atoi(arg1.c_str());
        num=num*arg1Val;                                                        //multiplying int times fraction
        Fraction *fraction=new Fraction(num,denom);
        fraction->simplify();
        result=fraction->toString();
        return result;
	}
	if(isFraction(arg1)&&isFraction(arg2)){
        int num1=fractionNum(arg1);
        int num2=fractionNum(arg2);
        int denom1=fractionDenom(arg1);
        int denom2=fractionDenom(arg2);                                              //multiplying two fractions together. multiply each numerator and denominator together, convert to string, and return
        int combNum=num1*num2;
        int combDenom=denom1*denom2;
        Fraction *fraction= new Fraction(combNum, combDenom);
        fraction->simplify();
        result=fraction->toString();
        return result;
	}

	//DIS BE THE ROOT SHIZ! LEAVE IT ALONE!

	else if(isNumber(arg1) && isNRT(arg2)){
		return multiply(arg2, arg1);
	}
	else if(isNRT(arg1) && isNumber(arg2)){
		stringstream ss;
		Root *root1 = new Root(findCoeff(arg1),rootIndex(arg1),rootRadicand(arg1));
		root1->simplify();
		if(root1->getRadicand() == 1){                                                                            //multiplying a root times an int
			ss << atoi(arg2.c_str()) * root1->getValue();
			return ss.str();
		}
		else if(root1->getRadicand() > 1 || root1->getRadicand() < 0){
			ss << atoi(arg2.c_str()) * root1->getValue() << "*" << root1->getIndex() << "rt:" << root1->getRadicand();
			return ss.str();
		}
		else {
			return "0";
		}
	}

	else if(isNRT(arg2) && isNRT(arg1)) {
		Root *root1 = new Root(findCoeff(arg1),rootIndex(arg1),rootRadicand(arg1));             //multiplying two roots together
		Root *root2 = new Root(findCoeff(arg2),rootIndex(arg2),rootRadicand(arg2));
		root1->simplify();
		root2->simplify();                                                                                                           
		if(root1->getIndex() == root2->getIndex()){                                        //checks to see if the indexes are equal
			Root *root3 = new Root(root1->getValue()*root2->getValue(),root1->getIndex(),root1->getRadicand()*root2->getRadicand());        //if they are, our answer is a new root with the int values and radicands multiplied together
			root3->simplify();
														//convert the answer to a string and return it
			return root3->toString();

		}
		result = root2->toString() + "*" + root1->toString();
		return result;
	}


	else {
		result = arg2 + "*" + arg1;
		return result;
	}
}

string Calculator::divide(string arg1, string arg2){
	string result;
	if(isNumber(arg1) && isNumber(arg2)){
		int num1 = atoi(arg1.c_str());
		int num2 = atoi(arg2.c_str());
		Fraction *fraction = new Fraction(num2, num1);                    //if dividing ints, we create a fraction using the two numbers being divided
		fraction->simplify();                                                    //simplify it
		result = fraction->toString();
		return result;                                                      //return it
	}
	if(isNumber(arg1)&&isFraction(arg2)){
        int num=fractionNum(arg2);
        int denom=fractionDenom(arg2);
        int arg1Val=atoi(arg1.c_str());
        denom=denom*arg1Val;                                                  //dividing fraction by int
        Fraction *fraction=new Fraction(num,denom);
        fraction->simplify();
        result=fraction->toString();
        return result;
	}else if(isFraction(arg1)&&isNumber(arg2)){
        int num=fractionNum(arg1);
        int denom=fractionDenom(arg1);
        int arg2Val=atoi(arg2.c_str());                                           //dividing int by fraction
        denom=denom*arg2Val;
        Fraction *fraction=new Fraction(num,denom);
        fraction->simplify();
        result=fraction->toString();
        return result;
	}else if(isFraction(arg1) && isFraction(arg2)){
        int num=fractionNum(arg1);
        int denom=fractionDenom(arg1);                                //dividing two fractions. get the reciprocal, then multiply
        Fraction *fraction=new Fraction(denom,num);
        fraction->simplify();
        string invFraction=fraction->toString();
        result = multiply(invFraction, arg2);
        return result;
	}
	else if(isNumber(arg2) && isNRT(arg1)){
		Root *root1 = new Root(findCoeff(arg1),rootIndex(arg1),rootRadicand(arg1));
		root1->simplify();
		string temp = root1->toString();                               
		if (temp == "0"){
				result = arg2 + "/" + temp;
				return result;
		};
		result = arg2 + "/(" + temp + ")";
		return result;
	}
	else if (isNRT(arg1) && isNRT(arg2)){
		Root *root1 = new Root(findCoeff(arg1),rootIndex(arg1),rootRadicand(arg1));
		Root *root2 = new Root(findCoeff(arg2),rootIndex(arg2),rootRadicand(arg2));                       //dividing two roots
		root1->simplify();
		root2->simplify();                                                                                       
		Root *root5 = new Root((int)pow((double)root1->getValue(), (double)root1->getIndex()) * root1->getRadicand(), 1, 1);    //this creates a "root"(technically a root object, but with index and radicand of 1) that will be the new denominator
		root5->simplify();

		Root *root4 = new Root((int)pow((double)root1->getValue(), (double)(root1->getIndex() - 1)), root1->getIndex(), (int)pow((double)root1->getRadicand(), (double)(root1->getIndex() - 1)));   //we've multiplied the equal to what we had to multiply the denominator by in order to rationalize the fraction
		root4->simplify();
		if (root1->getRadicand() == 0){           //If 0 in denom, can't do it. returns error
			throw 3;
			cout << "Error: Can't divide by zero!" << endl;
			result = arg2 + "/" + "0";
			return result;
		}
		arg2 = root2->toString();
		arg1 = root4->toString();
		result = arg1 + "*" + arg2;                   //gives us our new numerator
		if (root5->toString() != "1"){
			result += "/" + root5->toString();  // tacks on the new, rationalized denominator
		}
		return result;                                                                      // return result


	}
	else {
		result = arg2 + "/" + arg1;
		return result;
	}
}

string Calculator::exponentiate(string arg1, string arg2){
	int numResult;
	string result;

	if((arg1.at(0) == '(' && arg1.at(1) == '-')){

		string result = "";
		for(int i = 2; i < arg1.length(); i++) {
			result += arg1.at(i);
		}

		result = "1/" + exponentiate(result, arg2);
		return result;
	} else if (arg1.at(0) == '-') {
		string result = "";
				for(int i = 1; i < arg1.length(); i++) {
					result += arg1.at(i);
				}
				result = shuntingYard( "1/" + exponentiate(result, arg2));
				return result;
	}
	if(isNumber(arg1) && isNumber(arg2)){
		 int num1 = atoi(arg1.c_str());
	     int num2 = atoi(arg2.c_str());
	     if(num2 == 1){
	    	 return arg2;
	     }
		 numResult = pow(num2, num1);
		 stringstream ss;
		 ss << numResult;
		 result = ss.str();
		 return result;
	}


	else if(isFraction(arg1) && isNumber(arg2)){
		int num1 = atoi(arg1.c_str());
		int num2 = atoi(arg2.c_str());
		if(num2 == 1){
			return arg2;
		}
		int numerator = fractionNum(arg1);
		int denominator = fractionDenom(arg1);
		int index = atoi(arg2.c_str());
		index = pow(index, numerator);
		Root *root = new Root(denominator, index);
		root->simplify();
		result = root->toString();
		return result;
	}


	else {
		if(arg1 == "1"){
			return arg2;
		} else if(arg2 == "1"){
			return arg2;
		}
		result = arg2 + "^" + arg1;
		return result;
	}
}
