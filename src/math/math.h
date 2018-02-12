#ifndef MATH1_H
#define MATH1_H

#include <QString>

namespace Math {
    class Function;

    /**
     * Distance between P1(x1, y1) and P2(x2, y2)
     **/
    double distance(double x1, double x2, double y1, double y2);
    /**
     * Area of a quadrilateral formed by y1,
     * y2 and their projections on x axis.
     * incr is its base.
     **/
    double area(double incr, double y1, double y2);
    /**
     * Computes the definite integral of a function between -X_axis and +X_axis
     **/
    double integral(double *points1, double *points2, double incr);
    /**
     * Triangular impulse with base b
     **/
    double Tri(double b, double x);
    /**
     *Dirac delta
     **/
    double delta(double x1);
    /**
     *Sinc function (sin(arg)/arg)
     **/
    double sinc(double x);
    /**
     *Step function, starting in center and tall h
     **/
    double step(double center, double x, double h);
    /**
     *Rectangular impulse
     **/
    double Rect(double t);
    /**
     * Splits a string in function of c, skipping 'skip' parts:
     * string str = new_string("a.b.c");
     * string *divided = divide('.', str, 1);
     *
     * divided[0] will be "a.b" and divided[1] will be "c"
     **/
    QString** divide(char c, QString* str, int skip);
}

class Math::Function {
	public:
		//constructor
        Function(QString* expression);
		//destructor
		~Function();
		
		/**
		 * Computes the numerical value of a function f(x) with a specified x
		 **/
        double Compute(double x, double parameter);

	private:
		//number of children
		int children;
        QString* expression;
		/**************************
		 * Possible "type" values:
		 * 1. Sum
		 * 2. Product
		 * 3. Substraction
		 * 4. Division
		 * 5. Power
		 * 6. Natural logarithm
		 * 7. Sine
		 * 8. Cosine
		 * 9. Square root
		 * a. Constant
		 * b. Sinc
		 * c. x
		 * d. Rect
		 * e. Delta
		 * f. Abs
		 * g. Tri
		 * h. Parameter
		************************/
		char 	type;
		//if type is a, value is the value of the node
		double 	value;
		//true if the function contains a parameter
		bool	isAnimated;
		/*****
		 * The whole function is a binary tree:
		 * sin(12+x)
		 * 				sin
		 * 				 |
		 * 				 +
		 * 				/ \
		 * 			   12  x
		 * 
		 * connectedNodes[0] -> first son
		 * ...[1] -> second son
		*****/ 
        Math::Function** connectedNodes;
		
		/**
		 * Used in convolution, it replaces every x with (-x+a)
		 **/
        QString* prepare_for_convolution();
		/**
		 * Verifies if every ( is closed by a )
		 **/
        bool verify_str_par(QString* s = nullptr);
		/**
		 * Removes excessing parenthesis: (sin(x)) -> sin(x)
		 **/
		void remove_par();
		/**
		 * Removes spaces and replaces every '-' without a prev element 
		 * with '0-'
		 **/
		void clear();
		/**
		 * Used for Triangular signals: Tri(a,b)
		 * returns a if i = 0, else b
		 **/
        Math::Function* argum(QString* s, int i);
};

#endif
