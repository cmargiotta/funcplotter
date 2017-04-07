#include <stdio.h>
#include <math.h>

#include "math1.h"
#include "extvar.h"

#define pi 3.141593
int x, y;

double Tri(double b, double x) {
	if (x > -b && x <= 0) {
		return 1 + x/b;
	}

	if (x < b && x > 0) {
		return 1 - x/b;
	}

	return 0;
}

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


double step(double center, double x, double h) {
	if (x >= center) {
		return h;
	}

	return 0;
}

double Rect(double x) {
	if (x > (-1/2.0) && x < (1/2.0)) {
		return 1;
	}

	return 0;
}

double module(double b) {
	if (b >= 0) {
		return b;
	}

	return -b;
}
