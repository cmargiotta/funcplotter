#ifndef SUPPORT_H
#define SUPPORT_H

#include <QString>

#ifndef E
#define E 2.71828
#endif

#ifndef PI
#define PI 3.14159
#endif

namespace Support {
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
    double integral(double *points1, double *points2, double incr, int viewHeight, int viewWidth, int yAxis);
    /**
     * Triangular impulse with base b
     **/
    double Tri(double b, double x);
    /**
     *Dirac delta
     **/
    double delta(double x1, int viewWidth, int xAxis);
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

#endif // SUPPORT_H
