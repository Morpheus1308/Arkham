#include "Model.h"

#include "Resident.h"
#include <QDataStream>
#include <QFile>
#include "Patient.h"

class ModelPrivate
{
private:
    Model *owner;

public:
    ModelPrivate(Model *owner)
    {
        this->owner = owner;
    }

    QList<Resident*> residents;
    int nextid;
    QString filename;

    QString genderAsString(Resident::Gender gender)
    {
        switch(gender)
        {
        case Resident::Male: return QObject::tr("Male");
        case Resident::Female: return QObject::tr("Femail");
        case Resident::Hermaphrodite: return QObject::tr("Hermaphrodite");

        default: break;
        }
        return QObject::tr("Not Quite Sure");
    }

    void createInitialDatabase()
    {

        Patient *r = new Patient();
        r->setEmail("a@a.aa");
        r->setGender(Resident::NotSure);
        r->setName("Aaaaa");
        r->setTitle("Mr.");
        r->setSanity(100);
        r->setPassword("aaa");
        r->setBirthDate(QDate(2000, 1, 1));
        owner->addResident(r);

        r = new Patient();
        r->setEmail("b@b.bb");
        r->setGender(Resident::Male);
        r->setName("Bbbbb");
        r->setTitle("Ms.");
        r->setSanity(80);
        r->setPassword("bbb");
        r->setBirthDate(QDate(2000, 2, 2));
        owner->addResident(r);

        r = new Patient();
        r->setEmail("c@c.cc");
        r->setGender(Resident::Hermaphrodite);
        r->setName("Ccccc");
        r->setTitle("Mrs.");
        r->setSanity(70);
        r->setPassword("ccc");
        r->setBirthDate(QDate(2000, 3,3));
        owner->addResident(r);

    }
};

Model::Model()
    : d(new ModelPrivate(this))
{

}


Model::~Model()
{
    delete d;
}

void Model::setFileName(const QString &filename)
{
    d->filename = filename;
}

void Model::loadFromFileOrCreate()
{
    if ( QFile::exists(d->filename) )
    {
        QFile f(d->filename);
        f.open(QIODevice::ReadOnly);
        this->load(&f);
        f.close();
    }
    else
    {
        d->createInitialDatabase();
    }

}

void Model::saveToFile()
{

}

bool Model::save(QIODevice *out) const
{
    QDataStream os(out);
    os.setVersion(QDataStream::Qt_5_4);
    os << d->residents.size();
    foreach(Resident *resident, d->residents)
    {
        resident->streamTo(os);
    }
    return true;
}

bool Model::load(QIODevice *in)
{
    QDataStream is(in);
    is.setVersion(QDataStream::Qt_5_4);
    int size;
    is >> size;
    d->nextid = 0;
    for(int i = 0; i < size; i++)
    {
        Resident *r = Resident::streamNewResidentFrom(is);
        d->nextid = qMax<int>(r->id(),  d->nextid);
        d->residents << r;
    }
    //We increment 'nextid' to actually contain the next id avaliable for use.
    d->nextid++;
    return true;

}

void Model::addResident(Resident *resident)
{
    d->residents << resident;
}

void Model::removeResident(Resident *resident)
{

}

QList<Resident *> Model::residents() const
{
    return d->residents;
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid()) return QModelIndex();
    return createIndex(row, column);
}

QModelIndex Model::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int Model::rowCount(const QModelIndex &index) const
{
    if(index.isValid()) return 0;
    return d->residents.count();
}

int Model::columnCount(const QModelIndex &index) const
{
    if(index.isValid()) return 0;
    return 6;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }
    Resident *r = d->residents[index.row()];
    switch(index.column())
    {
    case 0: return r->title();
    case 1: return r->name();
    case 2: return d->genderAsString(r->gender());
    case 3: return r->sanity();
    case 4: return r->birthDate();
    case 5: return r->email();
    default: break;
    }
    return QVariant();

}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Vertical) return QVariant();
 if(role != Qt::DisplayRole) return QVariant();
 switch(section)
 {
 case 0: return tr("Title");
 case 1: return tr("Name");
 case 2: return tr("Gender");
 case 3: return tr("Sanity");
 case 4: return tr("Birth Date");
 case 5: return tr("E-mail");
 default: break;
 }
 return QVariant();
}
