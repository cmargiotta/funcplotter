#include <iostream>

#include "funcplotter.h"
#include "ui_funcplotter.h"
#include "src/globals.h"
#include "src/math/math.h"

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
    f = new Math::Function(new QString(ui->fInput->text()));
}

void funcplotter::onGFunctionReturn() {
    g = new Math::Function(new QString(ui->gInput->text()));
}

void funcplotter::onHFunctionReturn() {
    h = new Math::Function(new QString(ui->hInput->text()));
}
