#include <iostream>
#include <QDebug>
#include <QGraphicsView>

#include "funcplotter.h"
#include "ui_funcplotter.h"

#include "math/globals.h"
#include "math/core/math.h"

using namespace Math;

int xAxis, yAxis;
int width, height;

void funcplotter::computeFunction(Math::Function f, double** array) {

}

funcplotter::funcplotter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::funcplotter) {
        ui->setupUi(this);

        xAxis = 10;
        yAxis = 10;
        viewWidth = ui->functionView->width();
        viewHeight = ui->functionView->height();

        //connecting signal handlers
        connect(ui->fInput, &QLineEdit::returnPressed, this, &funcplotter::onFFunctionReturn);
        connect(ui->gInput, &QLineEdit::returnPressed, this, &funcplotter::onGFunctionReturn);
        connect(ui->hInput, &QLineEdit::returnPressed, this, &funcplotter::onHFunctionReturn);

        connect(ui->functionView, &QWidget::resizeEvent, this, &funcplotter::viewResized);
    }

funcplotter::~funcplotter() {
    delete ui;
}

void funcplotter::viewResized() {
    width = ui->functionView->width();
    height = ui->functionView->height();

    qInfo()<<"WOOW";
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
