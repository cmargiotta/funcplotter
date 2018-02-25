#include <cmath>
#include <QString>

#include "support.h"

double Support::distance(double x1, double x2, double y1, double y2) {
	return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

double Support::area(double incr, double y1, double y2) {
	double area;
	
	//area would be too small, returns 0
	if ((y1 > -incr && y1 < incr) || (y2 > -incr && y2 < incr))
		return 0;
		
	/*
	calculates the area of a rectangle having incr as base and min(y1,y2) 
	as summit, then calculates the area of the remaining triangle.
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

double Support::integral(double *points1, double *points2, double incr, int viewHeight, int viewWidth, int yAxis) {
	int i;
	double traitarea;
	double a = 0;
	//the value of a pixel
        double k = viewHeight/(2*yAxis);

        for (i = 1; i < viewWidth; i++) {
		traitarea = k*area(incr, points1[i-1]/k, points1[i]/k);
		traitarea *= k*area(incr, points2[i-1]/k, points2[i]/k);
		a += traitarea;
	}

	return a;
}

double Support::Tri(double b, double x) {
	if (x > -b && x <= 0) {
		return 1 + x/b;
	}

	if (x < b && x > 0) {
		return 1 - x/b;
	}

	return 0;
}

double Support::delta(double x1, int viewWidth, int xAxis) {
    double incr = (2*xAxis)/viewWidth;

	if (x1 < incr && x1 > -incr) {
		return 1;
	}

	return 0;
}

double Support::sinc(double x) {
    if (x > (-0.001) && x < (0.001)) {
        return 1;
    }

    double y = sin(PI*x);
    y /= PI*x;

    return y;
}

double Support::step(double center, double x, double h) {
	if (x >= center)
		return h;

	return 0;
}

double Support::Rect(double x) {
	if (x > (-1/2.0) && x < (1/2.0))
		return 1;

	return 0;
}

QString** Support::divide(char c, QString* str, int skip) {
    QString **result = new QString*[2];
    QChar* strData = str->data();

	int i;
	bool found = false;

    result[0] = new QString("");
    result[1] = new QString("");
	
    for (i = 0; i < str->size(); i++) {
        if (strData[i] == c && !found) {
			if (skip > 1) {
				skip--;
                *result[0] += strData[i];
			}
			else
				found = true;
		}
		else {
			if (found) {
                *result[1] += strData[i];
			}
			else {
                *result[0] += strData[i];
			}
		}
    }

	return result;
}
