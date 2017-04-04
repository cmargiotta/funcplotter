#ifndef _MATH1H_
#define _MATH1H_

#include <stdio.h>
#include <math.h>

#define pi 3.141593

int x, y;

//Triangular signal
double Tri(double base, double x) {
	if (x > -base && x <= 0) {
		return 1 + x/base;
	}
	if (x < base && x > 0) {
		return 1 - x/base;
	}

	return 0;
}

//Dirac's delta
double delta(double x1) {
	double incr = (2*x)/850.0;
	if (x1 < incr && x1 > -incr) {
		return 1;
	}
	return 0;
}

double sinc(double x) {
	if (x > (-0.001) && x < (0.001)) {
		return 1;
	}
	double y = sin(pi*x);
	y /= pi*x;
	return y;
}


double step(double center, double t, double h) {
	if (t >= center) {
		return h;
	}
	else {
		return 0;
	}
}

//Rectangular signal
double Rect(double t) {
	if (t > (-1/2.0) && t < (1/2.0)) {
		return 1.0;
	}
	return 0.0;
}

double absol(double b) {
	if (b >= 0) {
		return b;
	}
	else {
		return -b;
	}
}

#endif
