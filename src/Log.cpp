/**************************
Log.cpp
***************************/

#include "Calculator.h"
#include <vector>
#include <sstream>

//LOG CLASS FOR LOGS
Log::Log(int base, int value){
    if(base <= 0){
        throw 6;
    }else{
        this->base = base;
    }

    if(value <= 0){
        throw 5;
    }else{
        this->value = value;
    }
	vector <int> multiples;
		for(int i = 2; i <= value; i++) {
				while(value % i == 0) {
					value /= i;
					multiples.push_back(i);
				}
			}

	this->valueMultiples = multiples.size();
}

string Log::toString(){
//depending on what is in the logs, prints log
	string result = "";
	vector <int> multiples;
		if(value == base){
			return "1";
		}
	for(int i = 2; i <= value; i++) {
			while(value % i == 0) {
				value /= i;
				multiples.push_back(i);
			}
		}

	stringstream ss;
	stringstream ss2;
	ss2 << base;
	if(multiples.size() == 1){
		ss << multiples.at(0);
		result = "log_" + ss2.str() +":" + ss.str();
		return result;
	}
	for(int i = 0; i < multiples.size(); i++){
		ss << multiples.at(i);
		if(ss.str() == ss2.str()){
			result += "1";
		} else {
			result += "log_" + ss2.str() + ":" + ss.str();
		}
		if(i != multiples.size() - 1){
			result +="+";
		}
		ss.str("");
	}
	return result;
}

Log::~Log(){

}

