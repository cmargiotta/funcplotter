#ifndef MATH1_H
#define MATH1_H

/*!
 *  \headerfile math *
 *  \brief The header math.h provides the namespace Math.
 */

#include <QString>
#include <vector>
#include "support.h"

/*!
 *  \namespace Math
 *  \brief Contains the class Function.
 */
namespace Math {
    /*!
     * \class Math::Function
     * \brief The Function class represents a function parsed from a string.
     * \since 0.0
     *
     * The class Math::Function implements a binary tree for representing
     * a function.
     *
     * For example the function "sin(12+3*x)" will be parsed in:
     *              sin
     *               |
     *               +
     *              / \
     *             12  *
     *                / \
     *               3   x
     */
    class Function;

    /*!
     * \class plotterParameters
     * \brief Simply a container for plotter options.
     *
     * Contained options are:
     *  * both axis length
     *  * resolution of the plot
     */
    class plotterParameters;
}

class Math::Function {
	public:
        /*!
         * \fn Function(QString* expression, Support::plotterParameters* params, bool first=true)
         * \brief Function constructor.
         * \param expression A string representing the desired function, e.g. "12+log(3*x)"
         * \param params Plotter parameters, like axis dimensions or resolution
         *               (see Support::plotterParameter for more informations)
         * \param first If \c true this is the binary tree root, then it is required a
         *              vector with values (vec).
         */
        Function(QString* expression, Math::plotterParameters* params, bool first=true);
		//destructor
		~Function();
		
        /*!
         * \fn double Compute(double x, double parameter)
         * \brief Evaluates the function f(x, a)
         * \param x The x value
         * \param parameter The a value
         * \return f(x, a)
         */
        double Compute(double x, double parameter);
        /*!
         * \fn fillArray()
         * \brief Fills the function's vector with all points from -XAxis to XAxis (see Support::plotterParameters)
         */
        void fillArray();
        void debugPrint();
    private:
        Math::plotterParameters* params;
        std::vector<std::vector<double>* > vec;
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

class Math::plotterParameters {
    public:
        plotterParameters(int width, int height, int xAxis, int yAxis) {
            this->width = width;
            this->height = height;
            this->xAxis = xAxis;
            this->yAxis = yAxis;
        }
        ~plotterParameters() {}
        int getXAxis() {return xAxis;}
        int getYAxis() {return yAxis;}
        int getWidth() {return width;}
        int getHeight() {return height;}
        void setXAxis(int x) {xAxis=x;}
        void setYAxis(int y) {yAxis=y;}
        void setWidth(int w) {width=w;}
        void setHeight(int h) {height=h;}
    private:
        int xAxis;
        int yAxis;
        int width;
        int height;
};

#endif
