#include "funcplotter.h"
#include "ui_funcplotter.h"

funcplotter::funcplotter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::funcplotter)
    {
        ui->setupUi(this);
    }

funcplotter::~funcplotter() {
    delete ui;
}
