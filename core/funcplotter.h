#ifndef FUNCPLOTTER_H
#define FUNCPLOTTER_H

#include <QMainWindow>
#include <QString>

#include "math/core/math.h"

namespace Ui {
    class funcplotter;
}

class funcplotter : public QMainWindow
{
    Q_OBJECT

    public:
        explicit funcplotter(QWidget *parent = 0);
        ~funcplotter();
    private:
        Ui::funcplotter *ui;
        Math::Function *f, *g, *h;

        void onFFunctionReturn();
        void onGFunctionReturn();
        void onHFunctionReturn();
        void computeFunction(Math::Function f, double** array);
        void viewResized();
};

#endif // FUNCPLOTTER_H
