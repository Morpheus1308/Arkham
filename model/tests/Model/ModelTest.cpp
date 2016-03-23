#include <QtTest/QtTest>


class ModelTest: public QObject
{
    Q_OBJECT
private slots:

    void testToUpper()
    {
        QString str = "Hello";
        QVERIFY(str.toUpper() == "HELLO");
    }


};

QTEST_GUILESS_MAIN(ModelTest)

#include "ModelTest.moc"

