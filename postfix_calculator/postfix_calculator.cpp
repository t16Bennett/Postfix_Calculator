/*
	postfix_calculator.cpp

	Implementation of the postfix calculator. 

    CSCI 262, Spring 2018, Project 2

	author: 
*/

#include "postfix_calculator.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

//Function that returns true if the expression provided can be evaluated and false if it cannot be evaluated
bool postfix_calculator::evaluate(string expr) {
	
	//declaring string stream to hold the expression
	istringstream expression(expr);
	
	//Evaluating loop that runs for the whole expression
    while(!expression.eof()){
    	
    	//Declaring and initializing needed variables to parse the expression and evaluate it
    	string temp;
    	expression >> temp;
    	double current_num;
    	ans = 0;
    	
    	//Determing if the current part of the expression is a number of an operator
    	try{
    		current_num = stod(temp);
    		is_string = false;
    		//cout << "Is number" << endl;
    	}
    	catch(invalid_argument ie){
    		is_string = true;
    		//cout << "Is operator" << endl;
    	}
    	
    	//If the part of the expression is a number, it will be pushed onto the main stack
    	if(!is_string){
    		//cout << "Push" << endl;
    		calc.push(current_num);
    	}
    	//If the part of the expression is an operator, it will be checked with known operators.
    	else{
    		if(temp == "^" || temp == "*" || temp == "/" || temp == "+" || temp == "-"){
    			
    			//Gather numbers from stack and update stack
    			if(calc.empty()){
    				return false;
    			}
    			num2 = top();
    			calc.pop();
    			//cout << "Pop" << endl;
    			if(calc.empty()){
    				return false;
    			}
    			num1 = top();
    			calc.pop();
    			//cout << "Pop" << endl;
    			
    			//Perform operations
    			if(temp == "*"){
    				ans = multiplication(num1, num2);
    				//cout << "*" << endl;
    			}
    			else if(temp == "/"){
    				//check for divide by 0
    				if(num2 != 0){
    					ans = division(num1, num2);
    					//cout << "/" << endl;
    				}
    				else{
    					cout << "Divide by zero" << endl;
    					return false;
    				}
    			}
    			else if(temp == "+"){
    				ans = addition(num1, num2);
    				//cout << "+" << endl;
    			}
    			else if(temp == "-"){
    				ans = subtraction(num1, num2);
    				//cout << "-" << endl;
    			}
    			else if(temp == "^"){
    				ans = power(num1, num2);
    			}
    			//Return false if there is no matching operators
    			else{
    				return false;
    			}
    			
    		//Push answer onto stack
    		calc.push(ans);
    		}
    		////If the part of the expression is an operator, it will be checked with known operators.
    		else if(temp == "sqrt" || temp == "log" || temp == "ln" || temp == "sin" || temp == "cos" || temp == "tan"){
    			
    			//Gather number and update stack
    			num1 = top();
    			calc.pop();
    			
    			//Perform operations
    			if(temp == "sqrt"){
    				ans = square_root(num1);
    			}
    			else if(temp == "log"){
    				ans = logarithm(num1);
    			}
    			else if(temp == "ln"){
    				ans = natural_log(num1);
    			}
    			else if(temp == "sin"){
    				ans = sine(num1);
    			}
    			else if(temp == "cos"){
    				ans = cosine(num1);
    			}
    			else if(temp == "tan"){
    				ans = tangent(num1);
    			}
    			//Return false if there is no matching operators
    			else{
    				return false;
    			}
    			//Push answer onto stack
    			calc.push(ans);
    		}
    		//Return false if there is no matching operators
    		else{
    			cout << "Operator Not Valid" << endl;
    			return false;
    		}
    	}
    }
    //Expression was evaluated, return true
    return true;
}

//Return the addition of two numbers
double postfix_calculator::addition(double x, double y){
	return x + y;
}

//Return the subtraction of two numbers
double postfix_calculator::subtraction(double x, double y){
	return x - y;
}

//Return the multiplication of two numbers
double postfix_calculator::multiplication(double x, double y){
	return x * y;
}
	
//Return the division of two numbers
double postfix_calculator::division(double x, double y){
	return x / y;
}

//Return the result of a number to the power of another number
double postfix_calculator::power(double x, double y){
	return pow(x, y);
}

//Return the square root of a number
double postfix_calculator::square_root(double x){
	return sqrt(x);
}

//Return the base 10 logarithm of a number
double postfix_calculator::logarithm(double x){
	return log10(x);
}

//Return the natural log of a number	
double postfix_calculator::natural_log(double x){
	return log(x);
}

//Return the sine of a number
double postfix_calculator::sine(double x){
	return sin(x);
}

//Return the cosine of a number	
double postfix_calculator::cosine(double x){
	return cos(x);
}

//Return the tangent of a number
double postfix_calculator::tangent(double x){
	return tan(x);
}

//Clear the main stack
void postfix_calculator::clear(){
	stack<double> clear_stack;
	calc = clear_stack;
}

//Return top of the stack
double postfix_calculator::top(){
	if(calc.size() > 0){
		double top = calc.top();
		return top;
	}
	return 0.0;
}

//Override the to_string method to return what is within the stack
string postfix_calculator::to_string(){
	stack<double> copy = calc;
	string show_stack = "";
	for(int i = 0; i < calc.size(); i++){
		show_stack = show_stack + " " + std::to_string(copy.top());
		copy.pop();
	}
	return show_stack;
}

//Default constructor
postfix_calculator::postfix_calculator(){
	calc = calc;
	is_string = is_string;
	num1 = num1;
	num2 = num2;
	ans = ans;
}
