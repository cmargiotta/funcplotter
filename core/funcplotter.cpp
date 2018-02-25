#include <iostream>
#include <QDebug>
#include <QGraphicsView>
#include <vector>

#include "funcplotter.h"
#include "ui_funcplotter.h"

#include "math/math.h"
#include "math/support.h"

using namespace Math;

funcplotter::funcplotter(QWidget *parent) :
    QMainWindow(parent), params(0,0,0,0),
    ui(new Ui::funcplotter) {
        ui->setupUi(this);
        ui->functionView->show();

        params.setXAxis(10);
        params.setYAxis(10);
        params.setHeight(ui->functionView->geometry().width());
        params.setWidth(ui->functionView->geometry().height());

        //connecting signal handlers
        connect(ui->fInput, &QLineEdit::returnPressed, this, &funcplotter::onFFunctionReturn);
        connect(ui->gInput, &QLineEdit::returnPressed, this, &funcplotter::onGFunctionReturn);
        connect(ui->hInput, &QLineEdit::returnPressed, this, &funcplotter::onHFunctionReturn);
    }

funcplotter::~funcplotter() {
    delete ui;
}

void funcplotter::onFFunctionReturn() {
    params.setXAxis(10);
    params.setYAxis(10);
    params.setHeight(ui->functionView->geometry().width());
    params.setWidth(ui->functionView->geometry().height());

    f = new Function(new QString(ui->fInput->text()), &params);
}

void funcplotter::onGFunctionReturn() {
    g = new Function(new QString(ui->gInput->text()), &params);
}

void funcplotter::onHFunctionReturn() {
    h = new Function(new QString(ui->hInput->text()), &params);
}
