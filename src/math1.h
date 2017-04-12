#ifndef MATH1H_
#define MATH1H_

/**
*Triangular impulse with base b
*@ret y coordinate corresponding to the provided x
*@pre base != 0
*/
double Tri(double b, double x);

/**
*Dirac delta
*@ret y coordinate corresponding to the provided x
*/
double delta(double x1);

/**
*Sinc function (sin(arg)/arg)
*@ret y coordinate corresponding to the provided x
*/
double sinc(double x);

/**
*Step function, starting in center and tall h
*@ret y coordinate corresponding to the provided x
*/
double step(double center, double x, double h);

/**
*Rectangular impulse
*@ret y coordinate corresponding to the provided x
*/
double Rect(double t);

/**
*Module function
*@ret module of b
*/
double module(double b);

#endif
