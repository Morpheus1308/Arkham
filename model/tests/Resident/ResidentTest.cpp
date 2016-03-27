#include <QtTest/QtTest>

#include <functional>
#include "Resident.h"
#include <QDebug>


//For batch testing of string getters and setters.
typedef void(Resident::*setStringPtr)(const QString &val);
typedef QString(Resident::*getStringPtr)() const;
Q_DECLARE_METATYPE(setStringPtr)
Q_DECLARE_METATYPE(getStringPtr)

//For batch testing of int getters and setters.
typedef void(Resident::*setIntPtr)(int);
typedef int(Resident::*getIntPtr)() const;
Q_DECLARE_METATYPE(setIntPtr)
Q_DECLARE_METATYPE(getIntPtr)


//For passing lambdas as data in data driven tests of == and != operators
typedef std::function<void(Resident*const)> manipulator;
Q_DECLARE_METATYPE(manipulator)

class MockResident : public Resident
{
public:
    MockResident() : Resident()
    {
    }
    bool mayBeReadBy(Resident const * const ) const
    {
        return false;
    }

    bool mayBeWrittenBy(Resident const * const ) const
    {
        return true;
    }

};

class ResidentTest: public QObject
{
    Q_OBJECT
private slots:

    void testPassword()
    {
        MockResident mr;
        mr.setPassword("Secret");
        QVERIFY(mr.matchesPassword("Secret"));
        QVERIFY( ! mr.matchesPassword("Chewbacca"));
    }

    void testStringGettersAndSetters_data()
    {
        QTest::addColumn<setStringPtr>("setter");
        QTest::addColumn<getStringPtr>("getter");

        QTest::newRow("name") << &Resident::setName << &Resident::name;
        QTest::newRow("title") << &Resident::setTitle << &Resident::title;
        QTest::newRow("email") << &Resident::setEmail << &Resident::email;
    }

    void testStringGettersAndSetters()
    {
        MockResident mr;

        QFETCH(setStringPtr, setter);
        QFETCH(getStringPtr, getter);
        std::function<QString()> get = std::bind(getter, &mr);

        QString original_value = get();

        QString value;
        value = original_value + "Some new value";
        std::function<void(QString)> set = std::bind(setter, &mr, value);
        set(value);

        QCOMPARE(original_value + "Some new value", get());
    }

    void testIntGettersAndSetters_data()
    {
        QTest::addColumn<setIntPtr>("setter");
        QTest::addColumn<getIntPtr>("getter");

        QTest::newRow("sanity") << &Resident::setSanity << &Resident::sanity;
        QTest::newRow("privileges") << &Resident::setPrivileges << &Resident::privileges;
    }

    void testIntGettersAndSetters()
    {
        MockResident mr;

        QFETCH(setIntPtr, setter);
        QFETCH(getIntPtr, getter);
        std::function<int()> get = std::bind(getter, &mr);

        int original_value = get();

        int value;
        value = original_value + 42;
        std::function<void(int)> set = std::bind(setter, &mr, value);
        set(value);

        QCOMPARE(original_value + 42, get());
    }

    void testBirthDate()
    {
        //Here is only one field, and it does not seem plausible that
        //more will come, so I just hardcode this one test.
        MockResident mr;
        QVERIFY(QDate(1976,12,4) != mr.birthDate());
        mr.setBirthDate(QDate(1976,12,4));
        QCOMPARE(QDate(1976,12,4), mr.birthDate());
    }

    void testGender()
    {
        //Here is only one field, and it does not seem plausible that
        //more will come, so I just hardcode this one test.
        MockResident mr;
        QVERIFY(Resident::Male != mr.gender());
        mr.setGender(Resident::Male);
        QCOMPARE(Resident::Male, mr.gender());
    }

    void testDefaults()
    {
        MockResident mr;
        QCOMPARE(0, mr.id());
        QCOMPARE(QString(""), mr.name());
        QCOMPARE(100, mr.sanity());
        QCOMPARE(QDate(1890, 8, 20), mr.birthDate());
        QCOMPARE(QString("Sir"), mr.title());
        QVERIFY (Resident::MayReadSelf == mr.privileges());
        QCOMPARE(Resident::NotSure, mr.gender());
        QCOMPARE(QString(""), mr.email());
    }

    void testEqualsOperator_data()
    {

        QTest::addColumn<manipulator>("manipulate");
        QTest::newRow("name") << manipulator([](Resident*const r){ r->setName(r->name()+"Naah..");});
        QTest::newRow("sanity") << manipulator([](Resident*const r){ r->setSanity(r->sanity()+11);});
        QTest::newRow("title") << manipulator([](Resident*const r){ r->setTitle(r->title()+"Naah..");});
        QTest::newRow("email") << manipulator([](Resident*const r){ r->setEmail(r->email()+"Naah..");});

    }


    void testEqualsOperator()
    {
        MockResident mr1;
        MockResident mr2;

        QFETCH(manipulator, manipulate);

        QCOMPARE(mr1, mr2);
        QVERIFY( ! (mr1 != mr2) );

        manipulate(&mr1);

        QVERIFY( ! (mr1 == mr2) );
        QVERIFY(   (mr1 != mr2) );


    }

};

QTEST_GUILESS_MAIN(ResidentTest)

#include "ResidentTest.moc"

