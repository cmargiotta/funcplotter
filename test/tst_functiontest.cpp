#include <QtTest>
#include <cmath>

#include "../core/math.h"

using namespace Math;

int y;
int x;

class functionTest : public QObject
{
    Q_OBJECT

public:
    functionTest();
    ~functionTest();

private slots:
    void simpleExpressions();
    void notSoSimpleExpressions();
};

functionTest::functionTest() {

}

functionTest::~functionTest() {

}

void functionTest::simpleExpressions() {
    QString sum  ("1+x");
    QString mult ("2*x");
    QString div  ("x/2");
    QString sub  ("x-1");
    QString sine ("sin(x)");
    QString x    ("x");

    Math::plotterParameters a (0,0,0,0);

    Function* f;

    f = new Function(&sum, &a);
    QCOMPARE(f->Compute(3, 0), 4);
    delete f;

    f = new Function(&mult, &a);
    QCOMPARE(f->Compute(3,0), 6);
    delete f;

    f = new Function(&div, &a);
    QCOMPARE(f->Compute(4,0), 2);
    delete f;

    f = new Function(&sub, &a);
    QCOMPARE(f->Compute(3,0), 2);
    delete f;

    f = new Function(&x, &a);
    QCOMPARE(f->Compute(3,0), 3);
    delete f;

    f = new Function(&sine, &a);
    QCOMPARE(f->Compute(3,0), sin(3));
    delete f;
}

void functionTest::notSoSimpleExpressions() {
    QString sumOfFuncs ("sin(x)+cos(x)");
    QString tripleSum  ("1+2+x");
    QString opOrder    ("x+4/2");
    QString compositeF ("sin(cos(x))");

    Math::plotterParameters a (0,0,0,0);

    Function* f;

    f = new Function(&sumOfFuncs, &a);
    QCOMPARE(f->Compute(3,0), sin(3)+cos(3));
    delete f;

    f = new Function(&tripleSum, &a);
    QCOMPARE(f->Compute(3,0), 6);
    delete f;

    f = new Function(&opOrder, &a);
    QCOMPARE(f->Compute(3,0), 5);
    delete f;

    f = new Function(&compositeF, &a);
    QCOMPARE(f->Compute(3,0), sin(cos(3)));
    delete f;
}

QTEST_APPLESS_MAIN(functionTest)

#include "tst_functiontest.moc"
