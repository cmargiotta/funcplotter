#include "funcplotter.h"
#include <QApplication>

#include "src/globals.h"

//global variables
int x;
int y;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    funcplotter w;
    w.show();

    return a.exec();
}
