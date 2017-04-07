#ifndef _FUNCTIONH_
#define _FUNCTIONH_

#include "stringutils.h"

typedef struct element{
	/*
	Possible "type" values:
	1. Sum
	2. Product
	3. Substraction
	4. Division
	5. Power
	6. Natural logarithm
	7. Sine
	8. Cosine
	9. Square root
	a. Constant
	b. Sinc
	c. x
	d. Rect
	e. Delta
	f. Abs
	g. Tri
	h. Parameter
	*/

	char type;
	//value of the function (if type is a, constant)
	double value;
	//argument can be 'x' in 'sin(x)' or 'b' in 'a+b'
	struct element* argument;
	//prev can be 'a' in 'a+b', not used in sine, cosine, etc
	struct element* prev;
	//animated != 0 if there is a parameter. Useful in the first node.
	int animated;
} element;

/*
It is a binary tree:
sin(12+x):
			sin
			/ \
		null	+
				/		\
			12			x
*/
typedef element* function;

/**
*Distance between P1(x1, y1) and P2(x2, y2)
*@ret distance
*/
double distance(double x1, double x2, double y1, double y2);

/*
*Considers a quadrilateral formed by y1,
*y2 and their proiection on x axis.
*incr is its base.
*@ret its area
*/
double area(double incr, double y1, double y2);

/**
*calculates the definite integral of a function between -X_axis and +X_axis
*(x and y in extvar.h)
*@ret the definite integral
*/
double integral(double *points1, double *points2, double incr);

/**
*used in convolution, it replaces every x with (-x+a)
*@ret the new funcion's string
*/
string prepare_for_convolution(string s);

/**
*verifies if every ( is closed by a )
*@ret 1 if they are ok, else 0
*/
int verify_str_par(string s);

/**
*removes excessing parenthesis: (sin(x)) -> sin(x)
*@ret the new string
*/
string remove_par(string s);

/**
*removes spaces and replaces every '-' without a prev element with '0-'
*@ret the new string
*/
string clean(string s);

/**
*Generates a function from a string
*@ret the function
*/
function new_function(string s);

/**
*used for Triangular signals: Tri(a,b)
*@ret a if i = 0, else b
*/
function argum(string s, int i);

/**
*frees memory used for a function linked structure
*/
void free_function(element *el);

/**
*Computes the numerical value of a function f(x) with a specified x
*@ret its value, y=f(x)
*/
double Compute(function f, double x, double parameter);

#endif
