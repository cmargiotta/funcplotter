#ifndef FUNCPLOTTER_H
#define FUNCPLOTTER_H

#include <QMainWindow>
#include <QString>
#include <vector>

#include "math.h"

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
        Math::plotterParameters params;

        void onFFunctionReturn();
        void onGFunctionReturn();
        void onHFunctionReturn();
};

#endif // FUNCPLOTTER_H
