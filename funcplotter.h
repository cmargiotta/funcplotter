#ifndef FUNCPLOTTER_H
#define FUNCPLOTTER_H

#include <QMainWindow>

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
};

#endif // FUNCPLOTTER_H
