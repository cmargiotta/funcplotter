#include <QString>
#include <QDebug>
#include <algorithm>
#include <cmath>

#include "math.h"
#include "../globals.h"

Math::Function* Math::Function::argum(QString* s, int i) {
    QString **parts;
    parts = Math::divide(',', s, 0);

    return new Math::Function(parts[i]);
}

Math::Function::~Function() {
	delete expression;
	
	for (int i = 0; i < children; i++)
		delete connectedNodes[i];
		
	delete connectedNodes;
}

Math::Function::Function(QString* expression) {
    qInfo()<<*expression<<'\n';
    this->expression = new QString(*expression);
    this->clear();
	
    if (std::count(expression->begin(), expression->end(), 'a') > 0)
        this->isAnimated = true;
	else
        this->isAnimated = false;
	
    QString** parts;
    int num, j;
	char c[5] = {'+','*','-','/','^'};
	char t[5] = {'1','2','3','4','5'};

	//if +, *, -, / or ^
    for (int i = 0; i < 5; i++) {
        num = expression->count(c[i]);
		j = 1;
		if (num >= 1) {
			if (i == 2) {
                parts = Math::divide(c[i], expression, num);
                while (!(parts[1]->length() > 0 && verify_str_par(parts[0])) && j > 0) {
					j--;
                    parts = Math::divide(c[i], expression, j);
				}
			}
			else {
                parts = Math::divide(c[i], expression, 1);
                while (!(parts[1]->length() > 0 && verify_str_par(parts[0])) && j <= num) {
					j++;
                    parts = Math::divide(c[i], expression, j);
				}
			}
            if (parts[1]->length() > 0 && verify_str_par(parts[0])) {
				type = t[i];
                connectedNodes = new Math::Function*[2];
                children = 2;
                connectedNodes[0] = new Math::Function(parts[0]);
                connectedNodes[1] = new Math::Function(parts[1]);
					
				return;
			}
		}
	}

	//if expr is a parameter 'a'
    if (expression[0] == 'a' && expression->length() == 1) {
		type = 'h';
        this->isAnimated = true;
		
		return;
	}

	char c1[5] = {'l','c','r','a','d'};
	char id[5] = {'6','8','d','f','e'};
	int l[5] = {4,4,5,4,6};
	
	children = 1;

    for (int i = 0; i < 6; i++) {
        if (expression[0] == c1[i]) {
            QString arg = expression->mid(l[i]);

            type = id[i];
            connectedNodes = new Math::Function*[1];
            connectedNodes[0] = new Math::Function(&arg);
			
			return;
		}
    }

	if (expression[0] == 't') {
        QString arg = expression->mid(5);
		
		type = 'g';
        value = argum(&arg, 0)->value;
        connectedNodes = new Math::Function*[1];
        connectedNodes[0] = argum(&arg, 1);
		
		return;
	}

	if (expression[0] == 's') {
		if (expression[1] == 'i') {
			//sinc
            QString arg;
			if (expression[3] == 'c') {
                arg = expression->mid(5);
				type = 'b';				
			}
			//sin
			else {			
                QString arg = expression->mid(4);
				type = '7';
			}
			
            connectedNodes = new Math::Function*[1];
            connectedNodes[0] = new Math::Function(&arg);
			
			return;
		}
		else {
            QString arg = expression->mid(5);
			
			type = '9';
            connectedNodes = new Math::Function*[1];
            connectedNodes[0] = new Math::Function(&arg);
			
			return;
		}
	}

	children = 0;

	if (expression[0] == 'x') {
		type = 'c';
        this->isAnimated = false;
		
		return;
	}
qInfo()<<"AAA"<<*expression;
	type = 'a';
	if (expression[0] == 'e')
		value = E;
	else
        value = expression->toDouble();
	
    this->isAnimated = false;
}

QString* Math::Function::prepare_for_convolution() {
    int x = std::count(expression->begin(), expression->end(), 'x');
    int a = std::count(expression->begin(), expression->end(), 'a');
	
    if (a < x) {
        QString *c = new QString("");
		int i;
		
        for (i = 0; i < expression->length(); i++) {
			if (expression[i] == 'x')
                *c += "(-x+a)";
			else
                *c += expression[i];
		}
		
		return c;
	}

	return expression;
}

bool Math::Function::verify_str_par(QString* s) {
    QString* expr;

    if (s==nullptr) expr = expression;
    else expr = s;

	int control = 0, i;

    for (i = 0; i < expr->length(); i++) {
        if (expr[i] == '(')
			control++;
        else if (expr[i] == ')') {
			if (control > 0)
				control--;
			else
				return false;
		}
	}

	return control==0;
}

void Math::Function::remove_par() {
    if (expression[0] == QChar('(') && expression[expression->length()-1] == QChar(')')) {
        QString clean = expression->mid(1, expression->length()-2);
		
        if (verify_str_par(&clean))
            this->expression = &clean;
	}
}

void Math::Function::clear() {
    if (expression[0] == '-')
        expression->insert(0, '0');
    else {
        expression->remove(QChar(' '), Qt::CaseInsensitive);
		remove_par();
	}
}

double Math::Function::Compute(double x, double parameter) {
    switch (type) {
		case '1': //Sum
            return (connectedNodes[0]->Compute(x, parameter)+connectedNodes[1]->Compute(x, parameter));
		case '2': //Product
            return (connectedNodes[0]->Compute(x, parameter)*connectedNodes[1]->Compute(x, parameter));
		case '3': //Substraction
            return (connectedNodes[0]->Compute(x, parameter)-connectedNodes[1]->Compute(x, parameter));
		case '4': //Division
            return (connectedNodes[0]->Compute(x, parameter)/connectedNodes[1]->Compute(x, parameter));
		case '5': //Power
            return pow(connectedNodes[0]->Compute(x, parameter), connectedNodes[1]->Compute(x, parameter));
		case '6': //Natural logarithm
            return log(connectedNodes[0]->Compute(x, parameter));
		case '7': //Sine
            return sin(connectedNodes[0]->Compute(x, parameter));
		case '8': //Cosine
            return cos(connectedNodes[0]->Compute(x, parameter));
		case '9': //Square root
            return sqrt(connectedNodes[0]->Compute(x, parameter));
		case 'a': //Constant
			return value;
		case 'b': //Sinc
            return Math::sinc(connectedNodes[0]->Compute(x, parameter));
		case 'c': //x
			return x;
		case 'd': //Rect
            return Math::Rect(connectedNodes[0]->Compute(x, parameter));
		case 'e': //Delta
            return Math::delta(connectedNodes[0]->Compute(x, parameter));
		case 'f': //Abs
            return abs(connectedNodes[0]->Compute(x, parameter));
		case 'g': //Tri
            return Math::Tri(value, connectedNodes[0]->Compute(x, parameter));
		case 'h': //Parameter
			return parameter;
		default: return 0;
	}
}
