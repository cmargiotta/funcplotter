#include <cmath>

#include "math.h"
#include "../globals.h"

double Math::Support::distance(double x1, double x2, double y1, double y1) {
	return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

double Math::Support::area(double incr, double y1, double y2) {
	double area;
	
	//area would be too small, returns 0
	if ((y1 > -incr && y1 < incr) || (y2 > -incr && y2 < incr))
		return 0;
		
	/*
	calculates the area of a rectangle having incr as base and min(y1,y2) as summit,
	then calculates the area of the remaining triangle.
	*/
	if (y1 <= y2) {
		area = incr*y1;
		if (abs(y2) > abs(y1)+0.001)
			area += incr*(y2-y1)/2;
	}
	else {
		area = incr*y2;
		if (abs(y1) > abs(y2)+0.001)
			area += incr*(y1-y2)/2;
	}

	return area;
}

double Math::Support::integral(double *points1, double *points2, double incr) {
	int width;
	int height;
	int i;
	double traitarea;
	double a = 0;
	//the value of a pixel
	double k = height/(2*y);

	for (i = 1; i < width; i++) {
		traitarea = k*area(incr, points1[i-1]/k, points1[i]/k);
		traitarea *= k*area(incr, points2[i-1]/k, points2[i]/k);
		a += traitarea;
	}

	return a;
}
