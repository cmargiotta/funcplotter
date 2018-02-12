#include <QtTest>
#include <cmath>

#include "../core/math/core/math.h"

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

    Function* f;

    f = new Function(&sum);
    QCOMPARE(f->Compute(3, 0), 4);
    delete f;

    f = new Function(&mult);
    QCOMPARE(f->Compute(3,0), 6);
    delete f;

    f = new Function(&div);
    QCOMPARE(f->Compute(4,0), 2);
    delete f;

    f = new Function(&sub);
    QCOMPARE(f->Compute(3,0), 2);
    delete f;

    f = new Function(&x);
    QCOMPARE(f->Compute(3,0), 3);
    delete f;

    f = new Function(&sine);
    QCOMPARE(f->Compute(3,0), sin(3));
    delete f;
}

void functionTest::notSoSimpleExpressions() {
    QString sumOfFuncs ("sin(x)+cos(x)");
    QString tripleSum  ("1+2+x");
    QString opOrder    ("x+4/2");

    Function* f;

    f = new Function(&sumOfFuncs);
    QCOMPARE(f->Compute(3,0), sin(3)+cos(3));
    delete f;

    f = new Function(&tripleSum);
    QCOMPARE(f->Compute(3,0), 6);
    delete f;

    f = new Function(&opOrder);
    QCOMPARE(f->Compute(3,0), 5);
    delete f;
}

QTEST_APPLESS_MAIN(functionTest)

#include "tst_functiontest.moc"
