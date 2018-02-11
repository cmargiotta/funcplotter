#include "funcplotter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    funcplotter w;
    w.show();

    return a.exec();
}
