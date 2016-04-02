#include <QtTest/QtTest>

#include <functional>
#include "../MockResident.h"
#include <QDebug>
#include <QMetaObject>

#include <Guard.h>
#include <MedicalStaff.h>
#include <Patient.h>
#include <Alchemist.h>


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

        bool signalled = false;
        connect(&mr, &Resident::updated, [&]()
        {
            signalled = true;
        });

        QString value;
        value = original_value + "Some new value";
        std::function<void(QString)> set = std::bind(setter, &mr, value);
        set(value);
        QVERIFY(signalled);
        QCOMPARE(original_value + "Some new value", get());
    }

    void testIntGettersAndSetters_data()
    {
        QTest::addColumn<setIntPtr>("setter");
        QTest::addColumn<getIntPtr>("getter");

        QTest::newRow("sanity") << &Resident::setSanity << &Resident::sanity;
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

        //We want to assure, that an updated signal is emitted whenever an int is changed.
        bool signalled = false;
        connect(&mr, &Resident::updated, [&]()
        {
            signalled = true;
        });

        std::function<void(int)> set = std::bind(setter, &mr, value);
        set(value);

        QCOMPARE(original_value + 42, get());
        QVERIFY(signalled);
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


    // Yes! I leak memory galore here, but for a unit test I really don't care.
    //Not for this assignment anyway.
    #define STRINGIFY(x) #x
    #define TOSTRING(x) STRINGIFY(x)

    #define ADDROW(examinerclass, mayread, maywrite, subjectclass) \
    QTest::newRow(STRINGIFY(examinerclass) " on " STRINGIFY(subjectclass)) << (Resident*)(new examinerclass()) << (Resident*)(new subjectclass()) << (mayread) << (maywrite)

    #define ADDSELF(examinerclass, mayread, maywrite) \
    { \
    Resident *self = new examinerclass; \
    QTest::newRow(STRINGIFY(examinerclass)" on self") << self << self << (mayread) << (maywrite); \
    }
    #define MayRead true
    #define MayWrite true
    #define MayNotRead false
    #define MayNotWrite false

    void testPrivileges_data()
    {
        QTest::addColumn<Resident*>("examiner");
        QTest::addColumn<Resident*>("subject");
        QTest::addColumn<bool>("may_read");
        QTest::addColumn<bool>("may_write");

        ADDSELF(Patient,    MayNotRead,    MayNotWrite);
        ADDROW (Patient,    MayNotRead,    MayNotWrite,    Patient);
        ADDROW (Patient,    MayNotRead,    MayNotWrite,    Guard);
        ADDROW (Patient,    MayNotRead,    MayNotWrite,    MedicalStaff);
        ADDROW (Patient,    MayNotRead,    MayNotWrite,    Alchemist);

        ADDSELF(Guard,    MayRead,    MayWrite);
        ADDROW (Guard,    MayRead,    MayNotWrite,    Patient);
        ADDROW (Guard,    MayRead,    MayNotWrite,    Guard);
        ADDROW (Guard,    MayNotRead, MayNotWrite,    MedicalStaff);
        ADDROW (Guard,    MayNotRead, MayNotWrite,    Alchemist);

        ADDSELF(MedicalStaff,    MayRead,    MayWrite);
        ADDROW (MedicalStaff,    MayRead,    MayWrite,     Patient);
        ADDROW (MedicalStaff,    MayRead,    MayNotWrite,  Guard);
        ADDROW (MedicalStaff,    MayRead,    MayNotWrite,  MedicalStaff);
        ADDROW (MedicalStaff,    MayNotRead, MayNotWrite,  Alchemist);

        ADDSELF(Alchemist,    MayRead,    MayWrite);
        ADDROW (Alchemist,    MayRead,    MayWrite,  Patient);
        ADDROW (Alchemist,    MayRead,    MayWrite,  Guard);

        ADDROW (Alchemist,    MayRead,    MayWrite,  MedicalStaff);
        ADDROW (Alchemist,    MayRead,    MayWrite,  Alchemist);

    }

    void testPrivileges()
    {
        QFETCH(Resident *, examiner);
        QFETCH(Resident *, subject);
        QFETCH(bool, may_read);
        QFETCH(bool, may_write);

        QCOMPARE(may_read, subject->mayBeReadBy(examiner));
        QCOMPARE(may_write, subject->mayBeWrittenBy(examiner));

    }

};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    RegisterResidentClass(MockResident);

    RegisterResidentClass(Patient);
    RegisterResidentClass(Guard);
    RegisterResidentClass(MedicalStaff);
    RegisterResidentClass(Alchemist);


    ResidentTest class_under_test;
    return QTest::qExec(&class_under_test, argc, argv);
}

#include "ResidentTest.moc"

