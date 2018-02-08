#include <string>
#include <algorithm>
#include <math>

#include "math.h"
#include "../globals.h"

Math::Support support ();

Math::Function argum(std::string s, int i) {
	std::string *parts;
	parts = Math::Support::divide(',', s, 0);

	Math::Function r (parts[i]);

	return r;
}

Math::Function::~Function() {
	delete expression;
	
	for (int i = 0; i < children; i++)
		delete connectedNodes[i];
		
	delete connectedNodes;
}

Math::Function::Function(std::string expr) {
	this->expression = expression;
	clean();
	
	if (std::count(expression.begin(), expression.end(), 'a') > 0)
		animated = true;
	else
		animated = false;
	
	std::string* parts;
	int i, j;
	int num;
	char c[5] = {'+','*','-','/','^'};
	char t[5] = {'1','2','3','4','5'};

	//if +, *, -, / or ^
	for (i = 0; i < 5; i++) {
		num = std::count(expression.begin(), expression.end(), c[i]);
		j = 1;
		if (num >= 1) {
			if (i == 2) {
				parts = Math::Support::divide(c[i], s, num);
				while (!(parts[1].size() > 0 && verify_str_par(parts[0])) && j > 0) {
					j--;
					parts = Math::Support::divide(c[i], s, j);
				}
			}
			else {
				parts = Math::Support::divide(c[i], s, 1);
				while (!(parts[1].len > 0 && verify_str_par(parts[0])) && j <= num) {
					j++;
					parts = Math::Support::divide(c[i], s, j);
				}
			}
			if (parts[1].size() > 0 && verify_str_par(parts[0])) {
				type = t[i];
				connectedNodes = new Math::Function[2];
				children = 2;
				connectedNodes[0] = new Math::Function(parts[0]);
				connectedNodes[1] = new Math::Function(parts[1]);
					
				return;
			}
		}
	}

	//if expr is a parameter 'a'
	if (expression[0] == 'a' && expression.size() == 1) {
		type = 'h';
		animated = true;
		
		return;
	}

	char c1[5] = {'l','c','r','a','d'};
	char id[5] = {'6','8','d','f','e'};
	int l[5] = {4,4,5,4,6};
	
	children = 1;

	for (i = 0; i < 6; i++) {
		if (expression[0] == c1[i]) {
			std::string arg = expression.substr(l[i], expression.npos());
			
			type = id[i];
			connectedNodes = new Math::Function[1];
			connectedNodes[0] = new Math::Function(arg);
			
			return;
		}
	}

	if (expression[0] == 't') {
		std::string arg = expression.substr(5, expression.npos());
		
		type = 'g';
		value = argum(arg,0).value;
		connectedNodes = new Math::Function[1];
		connectedNodes[0] = argum(arg, 1);
		
		return;
	}

	if (expression[0] == 's') {
		if (expression[1] == 'i') {
			//sinc
			std::string arg;
			if (expression[3] == 'c') {
				arg = expression.substr(5, expression.npos());				
				type = 'b';				
			}
			//sin
			else {			
				std::string arg = expression.substr(4, expression.npos());				
				type = '7';
			}
			
			connectedNodes = new Math::Function[1];
			connectedNodes[0] = new Math::Function(arg);
			
			return;
		}
		else {
			std::string arg = expression.substr(5, expression.npos());
			
			type = '9';
			connectedNodes = new Math::Function[1];
			connectedNodes[0] = new Math::Function(arg);
			
			return;
		}
	}
	
	children = 0;

	if (expression[0] == 'x') {
		type = 'c';
		animated = false;
		
		return;
	}

	type = 'a';
	if (expression[0] == 'e')
		value = E;
	else
		value = std::stod(expression);
	
	animated = false;
}

std::string Math::Function::prepare_for_convolution() {
	int x = std::count(expression.begin(), expression.end(), 'x');
	int a = std::count(expression.begin(), expression.end(), 'a');
	
	if (a < x) {
		int len = expression.size() + x*5;
		std::string c ("");
		int i;
		
		for (i = 0; i < expression.size(); i++) {
			if (expression[i] == 'x')
				c += "(-x+a)";
			else
				c += expression[i];
		}
		
		return c;
	}

	return expression;
}

bool verify_str_par() {
	int control = 0, i;

	for (i = 0; i < expression.size(); i++) {
		if (expression[i] == '(')
			control++;
		else if (expression[i] == ')') {
			if (control > 0)
				control--;
			else
				return false;
		}
	}

	return control==0;
}

void remove_par() {
	if (expression[0] == '(' && expression[expression.size()-1] == ')') {
		std::string clean = expression.substring(1, expression.size()-2);
		
		if (verify_str_par(clean))
			this->expression = clean;
	}
}

void clean() {
	int i = std::count(expression.begin(), expression.end(), ' ');
	
	if (expression[0] == '-')
		expression.insert(0, '0');
	else {
		std::string c ("");
		for (i = 0; i < expression.size(); i++)
			if (expression[i] != ' ')
				c += expression[i];
		this->expression = c;
		remove_par();
	}
}

double Compute(Math::Function f, double x, double parameter) {
	switch (f->type) {
		case '1': //Sum
			return (Compute(connectedNodes[0], x, parameter)+Compute(connectedNodes[1], x, parameter));
		case '2': //Product
			return (Compute(connectedNodes[0], x, parameter)*Compute(connectedNodes[1], x, parameter));
		case '3': //Substraction
			return (Compute(connectedNodes[0], x, parameter)-Compute(connectedNodes[1], x, parameter));
		case '4': //Division
			return (Compute(connectedNodes[0], x, parameter)/Compute(connectedNodes[1], x, parameter));
		case '5': //Power
			return pow(Compute(connectedNodes[0], x, parameter), Compute(connectedNodes[1], x, parameter));
		case '6': //Natural logarithm
			return log(Compute(connectedNodes[0], x, parameter));
		case '7': //Sine
			return sin(Compute(connectedNodes[0], x, parameter));
		case '8': //Cosine
			return cos(Compute(connectedNodes[0], x, parameter));
		case '9': //Square root
			return sqrt(Compute(connectedNodes[0], x, parameter));
		case 'a': //Constant
			return value;
		case 'b': //Sinc
			return Math::Support::sinc(Compute(connectedNodes[0], x, parameter));
		case 'c': //x
			return x;
		case 'd': //Rect
			return Math::Support::Rect(Compute(connectedNodes[0], x, parameter));
		case 'e': //Delta
			return Math::Support::delta(Compute(connectedNodes[0], x, parameter));
		case 'f': //Abs
			return abs(Compute(connectedNodes[0], x, parameter));
		case 'g': //Tri
			return Math::Support::(f->value, Compute(connectedNodes[0], x, parameter));
		case 'h': //Parameter
			return parameter;
		default: return 0;
	}
}
