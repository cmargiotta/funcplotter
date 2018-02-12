#include <QString>
#include <QtTest>

class FuncplotterTestTest : public QObject
{
    Q_OBJECT

public:
    FuncplotterTestTest();

private Q_SLOTS:
    void testCase1();
};

FuncplotterTestTest::FuncplotterTestTest()
{
}

void FuncplotterTestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(FuncplotterTestTest)

#include "tst_funcplottertesttest.moc"
