#include <QString>
#include <QDebug>
#include <algorithm>
#include <cmath>
#include <vector>

#include "math.h"

const char  c[]  = {'+','*','-','/','^'};
const char  t[]  = {'1','2','3','4','5'};
const char  c1[] = {'l','c','r','e','d'};
const char  id[] = {'6','8','d','f','e'};
const int   l[]  = {4,4,5,4,6};

Math::Function* Math::Function::argum(QString* s, int i) {
    QString **parts;
    parts = Math::divide(',', s, 0);

    return new Math::Function(parts[i], params);
}

void Math::Function::fillArray() {
    double incr;
    int parameters;

    incr = ((double) 2*params->getXAxis())/params->getWidth();

    //assuming vec[0] exists
    if (isAnimated) {
        parameters = (int) params->getWidth()/(16*incr);

        for (int i=0; i<parameters; i++)
            vec.push_back(new std::vector <double> ());
    }

    for (double i=-params->getXAxis(); i<params->getXAxis(); i+=incr) {
        if (!isAnimated)
            vec[0]->push_back(Compute(i, 0));
        else {
            for (int c=0; c<parameters; c++)
                vec[c]->push_back(Compute(i, params->getXAxis()*2*c/(double) parameters));
        }
    }
}

void Math::Function::debugPrint() {
    int children;

    qInfo()<<*expression<<endl;

    if (std::find(t, t+5, type) != t+5)
        children = 2;
    else children = 1;

    if (type != 'a' && type != 'c') {
        for (int i = 0; i < children; i++)
            connectedNodes[i]->debugPrint();
    }
}

Math::Function::~Function() {
    int children;

    if (std::find(t, t+5, type) != t+5)
        children = 2;
    else children = 1;

    delete expression;

    if (type != 'a' && type != 'c') {
        for (int i = 0; i < children; i++)
            delete connectedNodes[i];

        delete[] connectedNodes;
    }
}

Math::Function::Function(QString* expr, Math::plotterParameters* params, bool first) {
    if (first) {
        isAnimated = expr->count(QChar('a')) > 0;
        vec.push_back(new std::vector <double> ()); //vec[0]
    }

    this->params = params;
    expression = new QString(*expr);
    clear();

    QString** parts;
    int num, j, i;

    //if +, *, -, / or ^
    for(i=0; i<5; i++) {
        num = expression->count(QChar(c[i]));
        j = 1;
        if (num >= 1) {
            if (i == 2) {
                parts = Math::divide(c[i], expression, num);
                while (!(parts[1]->length() > 0 && verify_str_par(parts[0])) && j > 0) {
                    j--;
                    parts = Math::divide(c[i], expression, j);
                }
            }
            else {
                parts = Math::divide(c[i], expression, 1);
                while (!(parts[1]->length() > 0 && verify_str_par(parts[0])) && j <= num) {
                    j++;
                    parts = Math::divide(c[i], expression, j);
                }
            }
            if (parts[1]->length() > 0 && verify_str_par(parts[0])) {
                type = t[i];
                connectedNodes = new Math::Function*[2];
                connectedNodes[0] = new Math::Function(parts[0], params, false);
                connectedNodes[1] = new Math::Function(parts[1], params, false);

                if(first) fillArray();
                return;
            }
        }
    }

    //if expr is a parameter 'a'
    if ((*expression)[0] == QChar('a') && expression->length() == 1) {
        type = 'h';
        this->isAnimated = true;

        if(first) fillArray();
        return;
    }

    for(i=0; i<5; i++) {
        if ((*expression)[0] == QChar(c1[i])) {
            QString arg = expression->mid(l[i]);

            type = id[i];
            connectedNodes = new Math::Function*[1];
            connectedNodes[0] = new Math::Function(&arg, params, false);

            if(first) fillArray();
            return;
        }
    }

    //WTF?
    /*
    if ((*expression)[0] == QChar('t')) {
        QString arg = expression->mid(5);

        type = 'g';
        value = argum(&arg, 0)->value;
        connectedNodes = new Math::Function*[1];
        connectedNodes[0] = argum(&arg, 1);

        return;
    }
    */

    if ((*expression)[0] == QChar('s')) {
        if ((*expression)[1] == QChar('i')) {
            //sinc
            QString arg;
            if ((*expression)[3] == QChar('c')) {
                arg = expression->mid(5);
                type = 'b';
            }
            //sin
            else {
                arg = expression->mid(4);
                type = '7';
            }

            arg.truncate(arg.length()-1);
            qInfo()<<arg;
            connectedNodes = new Math::Function*[1];
            connectedNodes[0] = new Math::Function(&arg, params, false);

            if(first) fillArray();
            return;
        }
        else {
            QString arg = expression->mid(5);

            arg.truncate(arg.length()-1);
            type = '9';
            connectedNodes = new Math::Function*[1];
            connectedNodes[0] = new Math::Function(&arg, params, false);

            if(first) fillArray();
            return;
        }
    }

    if ((*expression)[0] == QChar('x')) {
        type = 'c';
        this->isAnimated = false;

        if(first) fillArray();
        return;
    }

    type = 'a';
    if ((*expression)[0] == QChar('e'))
        value = E;
    else
        value = expression->toDouble();

    if(first) fillArray();
}

QString* Math::Function::prepare_for_convolution() {
    int x = std::count(expression->begin(), expression->end(), QChar('x'));
    int a = std::count(expression->begin(), expression->end(), QChar('e'));

    if (a < x) {
        QString *c = new QString("");
        int i;

        for (i = 0; i < expression->length(); i++) {
            if ((*expression)[i] == QChar('x'))
                *c += "(-x+a)";
            else
                *c += (*expression)[i];
        }

        return c;
    }

    return expression;
}

bool Math::Function::verify_str_par(QString* s) {
    QString* expr;

    if (s==nullptr) expr = expression;
    else expr = s;

    int control = 0, i;

    for (i = 0; i < expr->length(); i++) {
        if ((*expr)[i] == QChar('('))
            control++;
        else if ((*expr)[i] == QChar(')')) {
            if (control > 0)
                control--;
            else
                return false;
        }
    }

    return control==0;
}

void Math::Function::remove_par() {
    if ((*expression)[0] == QChar('(') && (*expression)[expression->length()-1] == QChar(')')) {
        QString clean = expression->mid(1, expression->length()-2);

        if (verify_str_par(&clean))
            this->expression = &clean;
    }
}

void Math::Function::clear() {
    if ((*expression)[0] == '-')
        expression->insert(0, '0');
    else {
        expression->remove(QChar(' '), Qt::CaseInsensitive);
        remove_par();
    }
}

double Math::Function::Compute(double x, double parameter) {
    switch (type) {
        case '1': //Sum
            return (connectedNodes[0]->Compute(x, parameter)+connectedNodes[1]->Compute(x, parameter));
        case '2': //Product
            return (connectedNodes[0]->Compute(x, parameter)*connectedNodes[1]->Compute(x, parameter));
        case '3': //Substraction
            return (connectedNodes[0]->Compute(x, parameter)-connectedNodes[1]->Compute(x, parameter));
        case '4': //Division
            return (connectedNodes[0]->Compute(x, parameter)/connectedNodes[1]->Compute(x, parameter));
        case '5': //Power
            return pow(connectedNodes[0]->Compute(x, parameter), connectedNodes[1]->Compute(x, parameter));
        case '6': //Natural logarithm
            return log(connectedNodes[0]->Compute(x, parameter));
        case '7': //Sine
            return sin(connectedNodes[0]->Compute(x, parameter));
        case '8': //Cosine
            return cos(connectedNodes[0]->Compute(x, parameter));
        case '9': //Square root
            return sqrt(connectedNodes[0]->Compute(x, parameter));
        case 'a': //Constant
            return value;
        case 'b': //Sinc
            return Math::sinc(connectedNodes[0]->Compute(x, parameter));
        case 'c': //x
            return x;
        case 'd': //Rect
            return Math::Rect(connectedNodes[0]->Compute(x, parameter));
        case 'e': //Delta
            return Math::delta(connectedNodes[0]->Compute(x, parameter), params->getWidth(), params->getXAxis());
        case 'f': //Abs
            return abs(connectedNodes[0]->Compute(x, parameter));
        case 'g': //Tri
            return Math::Tri(value, connectedNodes[0]->Compute(x, parameter));
        case 'h': //Parameter
            return parameter;
        default: return 0;
    }
}
