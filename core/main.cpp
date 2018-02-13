#include "funcplotter.h"
#include <QApplication>

#include "math/globals.h"

//global variables
int xAxis, yAxis;
int viewWidth, viewHeight;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    funcplotter w;
    w.show();

    return a.exec();
}
