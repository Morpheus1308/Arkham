#include <QtTest/QtTest>
#include "Model.h"
#include "Resident.h"

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


class ModelTest: public QObject
{
    Q_OBJECT
private slots:

    Model* buildModelForTest()
    {
        Model* model = new Model();

        Resident *r = new MockResident();
        r->setEmail("a@a.aa");
        r->setGender(Resident::NotSure);
        r->setName("Aaaaa");
        r->setTitle("Mr.");
        r->setSanity(100);
        r->setPassword("aaa");
        r->setBirthDate(QDate(2000, 1, 1));
        model->addResident(r);


        r = new MockResident();
        r->setEmail("b@b.bb");
        r->setGender(Resident::Male);
        r->setName("Bbbbb");
        r->setTitle("Ms.");
        r->setSanity(80);
        r->setPassword("bbb");
        r->setBirthDate(QDate(2000, 2, 2));
        model->addResident(r);


        r = new MockResident();
        r->setEmail("c@c.cc");
        r->setGender(Resident::Hermaphrodite);
        r->setName("Ccccc");
        r->setTitle("Mrs.");
        r->setSanity(70);
        r->setPassword("ccc");
        r->setBirthDate(QDate(2000, 3,3));
        model->addResident(r);

        return model;
    }

    bool compareModels(Model * lhs, Model * rhs)
    {
        QList<Resident*> lefts = lhs->residents();
        QList<Resident*> rights = rhs->residents();

        if(lefts.size() != rights.size() )
        {
            return false;
        }

        for (int i = 0; i < lefts.size(); i++)
        {
            if( *lefts[i] != *rights[i] )
            {
                return false;
            }
        }
        return true;

    }

    void testLoadAndSave()
    {
        Model *original = this->buildModelForTest();
        QByteArray data;
        QBuffer out(&data);
        out.open(QIODevice::WriteOnly);
        original->save(&out);
        out.close();

        QBuffer in(&data);
        in.open(QIODevice::ReadOnly);
        Model loaded;
        QVERIFY( loaded.load(&in) );
        in.close();
        QVERIFY( compareModels(&loaded, original));
    }

};

QTEST_GUILESS_MAIN(ModelTest)

#include "ModelTest.moc"

