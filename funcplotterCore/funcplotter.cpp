#include <iostream>

#include "funcplotter.h"
#include "ui_funcplotter.h"

#include "math/globals.h"
#include "math/core/math.h"

using namespace Math;

funcplotter::funcplotter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::funcplotter) {
        ui->setupUi(this);

        //connecting signal handlers
        connect(ui->fInput, &QLineEdit::returnPressed, this, &funcplotter::onFFunctionReturn);
        connect(ui->gInput, &QLineEdit::returnPressed, this, &funcplotter::onGFunctionReturn);
        connect(ui->hInput, &QLineEdit::returnPressed, this, &funcplotter::onHFunctionReturn);
    }

funcplotter::~funcplotter() {
    delete ui;
}

void funcplotter::onFFunctionReturn() {
    f = new Function(new QString(ui->fInput->text()));
}

void funcplotter::onGFunctionReturn() {
    g = new Function(new QString(ui->gInput->text()));
}

void funcplotter::onHFunctionReturn() {
    h = new Function(new QString(ui->hInput->text()));
}
