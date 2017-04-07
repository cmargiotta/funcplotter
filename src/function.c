#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "math1.h"
#include "stringutils.h"
#include "extvar.h"
#include "function.h"

#define pi 3.141593
#define e 2.718282

double distance(double x1, double x2, double y1, double y2) {
	double dist = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
	return dist;
}

double area(double incr, double y1, double y2) {
	double area;
	//area would be too small, returns 0
	if ((y1 > -incr && y1 < incr) || (y2 > -incr && y2 < incr)) {
		return 0;
	}
	/*
	calculates the area of a rectangle having incr as base and min(y1,y2) as summit,
	then calculates the area of the remaining triangle.
	*/
	if (y1 <= y2) {
		area = incr*y1;
		if (module(y2) > module(y1)+0.001) {
			area += incr*(y2-y1)/2;
		}
	}
	else {
		area = incr*y2;
		if (module(y1) > module(y2)+0.001) {
			area += incr*(y1-y2)/2;
		}
	}

	return area;
}


double integral(double *points1, double *points2, double incr) {
	int i;
	double traitarea;
	double a = 0;
	//the value of a pixel
	double k = 644.0/(2*y);

	for (i = 1; i < 840; i++) {
		traitarea = k*area(incr, points1[i-1]/k, points1[i]/k);
		traitarea *= k*area(incr, points2[i-1]/k, points2[i]/k);
		a += traitarea;
	}

	return a;
}

string prepare_for_convolution(string s) {
	int x = num_char(s, 'x');
	int a = num_char(s, 'a');
	if (a < x) {
		int len = s.len + x*5;
		char *c = (char *) malloc(len+1);
		int d=0, i;
		for (i = 0; i < s.len; i++) {
			if (s.str[i] == 'x') {
				c[d] = '(';
				d++;
				c[d] = '-';
				d++;
				c[d] = s.str[i];
				d++;
				c[d] = '+';
				d++;
				c[d] = 'a';
				d++;
				c[d] = ')';
				d++;
			}
			else {
				c[d] = s.str[i];
				d++;
			}
		}
		c[d] = '\0';
		string result = {len, c};
		return result;
	}

	return s;
}

int verify_str_par(string s) {
	int control = 0, i;

	for (i = 0; i < s.len; i++) {
		if (s.str[i] == '(') {
			control++;
		}
		if (s.str[i] == ')') {
			if (control > 0) {
				control--;
			}
			else {
				return 0;
			}
		}
	}

	if (control == 0) {
		return 1;
	}
	return 0;
}

string remove_par(string s) {
	if (s.str[0] == '(' && s.str[s.len-1] == ')') {
		char *c = (char *) malloc(s.len-1);
		int i, j=0;
		for (i = 1; i < s.len-1; i++) {
			c[j] = s.str[i];
			j++;
		}
		c[j] = '\0';
		string clean = new_string(c);
		if (verify_str_par(clean)) {
			return clean;
		}
		free(c);
	}
	return s;
}

string clean(string s) {
	int i = num_char(s, ' '), j = 0;
	char *c;
	if (s.str[0] == '-') {
		j++;
		c = (char *) malloc(s.len-i+2);
		c[0] = '0';
		for (i = 1; i < s.len+1; i++) {
			if (s.str[i-1] != ' ') {
				c[j] = s.str[i-1];
				j++;
			}
		}
	}
	else {
		c = (char *) malloc(s.len-i+1);
		for (i = 0; i < s.len; i++) {
			if (s.str[i] != ' ') {
				c[j] = s.str[i];
				j++;
			}
		}
	}
	c[j] = '\0';
	string str = new_string(c);
	str = remove_par(str);
	return str;
}

function new_function(string s) {
	s = clean(s);
	function f = (element *) malloc(sizeof(element));
	string *parts;
	int i, j;
	int num;
	char c[5] = {'+','*','-','/','^'};
	char t[5] = {'1','2','3','4','5'};

	//if +, *, -, / or ^
	for (i = 0; i < 5; i++) {
		num = num_char(s, c[i]);
		j = 1;
		if (num >= 1) {
			if (i == 2) {
				parts = divide(c[i], s, num);
				while (!(parts[1].len > 0 && verify_str_par(parts[0])) && j > 0) {
					j--;
					parts = divide(c[i], s, j);
				}
			}
			else {
				parts = divide(c[i], s, 1);
				while (!(parts[1].len > 0 && verify_str_par(parts[0])) && j <= num) {
					j++;
					parts = divide(c[i], s, j);
				}
			}
			if (parts[1].len > 0 && verify_str_par(parts[0])) {
				f->type = t[i];
				f->prev = new_function(parts[0]);
				f->argument = new_function(parts[1]);
				if (num_char(s,'a') > 0) {
					f->animated = 1;
				}
				else {
					f->animated = 0;
				}
				return f;
			}
		}
	}

	//if there's a parameter
	if (s.str[0] == 'a' && s.len == 1) {
		f->type = 'h';
		f->animated = 1;
		return f;
	}

	char c1[5] = {'l','c','r','a','d'};
	char id[5] = {'6','8','d','f','e'};
	int l[5] = {4,4,5,4,6};

	for (i = 0; i < 6; i++) {
		if (s.str[0] == c1[i]) {
			char *argument = (char *) malloc(s.len-l[i]);
			for (j = 0; j < s.len-l[i]; j++) {
				argument[j] = s.str[j+l[i]];
				if (j == s.len-l[i]-1) {
					argument[j] = '\0';
				}
			}
			string arg = {s.len-l[i], argument};
			f->type = id[i];
			f->argument = new_function(arg);
			f->prev = NULL;
			if (num_char(s,'a') > 0) {
				f->animated = 1;
			}
			else {
				f->animated = 0;
			}
			return f;
		}
	}

	if (s.str[0] == 't') {
		char *argument = (char *) malloc(s.len-4);
		for (i = 0; i <= s.len-5; i++) {
			argument[i] = s.str[i+4];
			if (i == s.len-5) {
				argument[i] = '\0';
			}
		}
		string arg = {s.len-4, argument};
		f->type = 'g';
		f->value = argum(arg,0)->value;
		f->argument = argum(arg,1);
		f->prev = NULL;
		if (num_char(s,'a') > 0) {
			f->animated = 1;
		}
		else {
			f->animated = 0;
		}
		return f;
	}

	if (s.str[0] == 's') {
		if (s.str[1] == 'i') {
			if (s.str[3] == 'c') {
				char *argument = (char *) malloc(s.len-5);
				for (i = 0; i <= s.len-6; i++) {
					argument[i] = s.str[i+5];
					if (i == s.len-6) {
						argument[i] = '\0';
					}
				}
				string arg = {s.len-5, argument};
				f->type = 'b';
				f->argument = new_function(arg);
				f->prev = NULL;
				if (num_char(s,'a') > 0) {
					f->animated = 1;
				}
				else {
					f->animated = 0;
				}
				return f;
			}
			char *argument = (char *) malloc(s.len-4);
			for (i = 0; i <= s.len-5; i++) {
				argument[i] = s.str[i+4];
				if (i == s.len-5) {
					argument[i] = '\0';
				}
			}
			string arg = {s.len-4, argument};
			f->type = '7';
			f->argument = new_function(arg);
			f->prev = NULL;
			if (num_char(s,'a') > 0) {
				f->animated = 1;
			}
			else {
				f->animated = 0;
			}
			return f;
		}
		else {
			char *argument = (char *) malloc(s.len-5);
			for (i = 0; i <= s.len-6; i++) {
				argument[i] = s.str[i+5];
				if (i == s.len-6) {
					argument[i] = '\0';
				}
			}
			string arg = {s.len-5, argument};
			f->type = '9';
			f->argument = new_function(arg);
			f->prev = NULL;
			if (num_char(s,'a') > 0) {
				f->animated = 1;
			}
			else {
				f->animated = 0;
			}
			return f;
		}
	}

	if (s.str[0] == 'x') {
		f->type = 'c';
		f->animated = 0;
		f->argument = NULL;
		f->prev = NULL;
		return f;
	}

	f->type = 'a';
	if (s.str[0] == 'e') {
		f->value = e;
		f->argument = NULL;
		f->prev = NULL;
	}
	else {
		f->value = valueOf(s);
		f->argument = NULL;
		f->prev = NULL;
	}
	f->animated = 0;
	return f;
}

function argum(string s, int i) {
	string *parts;
	parts = divide(',', s, 0);

	function r = new_function(parts[i]);

	return r;
}

void free_function(element *el) {
	if (el != NULL) {
		element *a = el->prev;
		element *b = el->argument;
		free(el);
		free_function(a);
		free_function(b);
	}
}

double Compute(function f, double x, double parameter) {
	switch (f->type) {
		case '1': //Sum
			return (Compute(f->prev, x, parameter)+Compute(f->argument, x, parameter));
		case '2': //Product
			return (Compute(f->prev, x, parameter)*Compute(f->argument, x, parameter));
		case '3': //Substraction
			return (Compute(f->prev, x, parameter)-Compute(f->argument, x, parameter));
		case '4': //Division
			return (Compute(f->prev, x, parameter)/Compute(f->argument, x, parameter));
		case '5': //Power
			return pow(Compute(f->prev, x, parameter), Compute(f->argument, x, parameter));
		case '6': //Natural logarithm
			return log(Compute(f->argument, x, parameter));
		case '7': //Sine
			return sin(Compute(f->argument, x, parameter));
		case '8': //Cosine
			return cos(Compute(f->argument, x, parameter));
		case '9': //Square root
			return sqrt(Compute(f->argument, x, parameter));
		case 'a': //Constant
			return f->value;
		case 'b': //Sinc
			return sinc(Compute(f->argument, x, parameter));
		case 'c': //x
			return x;
		case 'd': //Rect
			return Rect(Compute(f->argument, x, parameter));
		case 'e': //Delta
			return delta(Compute(f->argument, x, parameter));
		case 'f': //Abs
			return module(Compute(f->argument, x, parameter));
		case 'g': //Tri
			return Tri(f->value, Compute(f->argument, x, parameter));
		case 'h': //Parameter
			return parameter;
		default: return 0;
	}
}
