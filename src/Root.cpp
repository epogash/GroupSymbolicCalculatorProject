/**************************
Root.cpp
***************************/

#include "Root.h"
//ROOT CLASS
Root::Root(int index, int radicand) {

		value = 1;
		this->index = index;
		this->radicand = radicand;

}
Root::Root(int value, int index, int radicand){
        if(index%2 == 0 && radicand < 0){
            throw 7;
        }else{
		this->index = index;
		this->radicand = radicand;
        }
        this->value = value;
}


Root::~Root(){


}

int Root::getIndex(){

	return index;
}
int Root::getRadicand(){

	return radicand;
}
int Root::getValue(){

	return value;
}
string Root::toString(){
//DEPENDING ON WHAT IS IN THE ROOT, RETURNS SPECIAL STRING
	stringstream ss;
	if (radicand == 0){
		return "0";
	}
	if (radicand == 1){
		ss << value;
		return ss.str();
	}
	if (value == 1){
		if (index == 2){
			ss << "sqrt:" << radicand;
			return ss.str();
		}
		else{
			ss << index << "rt:" << radicand;
			return ss.str();
		}
	}
	else{
		if (index == 2){
			ss << value << '*' << "sqrt:" << radicand;
			return ss.str();
		}
		else{
			ss << value << '*' << index << "rt:" << radicand;
			return ss.str();
		}
	}

}

void Root::simplify() {
	//HANDLES NEG RADICANDS, ODD ROOTS OF NEGATIVE INDEXS
	if(index%2 != 0 && radicand < 0){
		bool isNeg = true;
		radicand = abs(radicand);
		int fact = 2;
		while ((int)pow((double)fact, (double)index) <= radicand){
			if (radicand % (int)pow((double)fact, (double)index) == 0){
				radicand /= (int)pow((double)fact, (double)index);
				value *= fact;
			}
			else{
				fact++;
			}
		}
		if(isNeg && radicand > 1){
			radicand *= -1;
		}
		else if(isNeg && radicand == 1){
			value *= -1;
		}
	}
		else{
			int fact = 2;
			while ((int)pow((double)fact, (double)index) <= radicand){
				if (radicand % (int)pow((double)fact, (double)index) == 0){
					radicand /= (int)pow((double)fact, (double)index);
					value *= fact;
				}
				else{
					fact++;
				}
			}
		}
}

