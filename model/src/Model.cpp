#include "Model.h"

#include "Resident.h"
#include <QDataStream>
#include <QFile>
#include "Patient.h"
#include "Guard.h"
#include "MedicalStaff.h"
#include "Alchemist.h"
#include <QDebug>

class ModelPrivate
{
private:
    Model *owner;

public:
    ModelPrivate(Model *owner)
        : owner(owner),
          number_of_dimensions(1)
    {
        this->owner = owner;
    }

    QList<Resident*> residents;
    int next_id;
    QString filename;
    int number_of_dimensions;

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

        Resident *r = new Patient();
        r->setEmail("p@p.p");
        r->setGender(Resident::Hermaphrodite);
        r->setName("Whacko");
        r->setTitle("Mr.");
        r->setSanity(100);
        r->setPassword("ppp");
        r->setBirthDate(QDate(2000, 1, 1));
        owner->addResident(r);

        r = new Guard();
        r->setEmail("g@g.g");
        r->setGender(Resident::Male);
        r->setName("Restrain Jacket");
        r->setTitle("Sir.");
        r->setSanity(100);
        r->setPassword("ggg");
        r->setBirthDate(QDate(2000, 1, 1));
        owner->addResident(r);

        r = new MedicalStaff();
        r->setEmail("m@m.m");
        r->setGender(Resident::Female);
        r->setName("Nurse");
        r->setTitle("Ms.");
        r->setSanity(100);
        r->setPassword("mmm");
        r->setBirthDate(QDate(2000, 1, 1));
        owner->addResident(r);

        r = new Alchemist();
        r->setEmail("a@a.a");
        r->setGender(Resident::NotSure);
        r->setName("Howard");
        r->setTitle("Dr.");
        r->setSanity(100);
        r->setPassword("aaa");
        r->setBirthDate(QDate(2000, 1, 1));
        owner->addResident(r);

    }
};

Model::Model() :
    QAbstractItemModel(),
    d(new ModelPrivate(this))
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
        this->saveToFile();
    }

}

void Model::saveToFile()
{
    QFile f(d->filename);
    f.open(QIODevice::WriteOnly);
    this->save(&f);
    f.close();
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
    d->next_id = 0;
    for(int i = 0; i < size; i++)
    {
        Resident *r = Resident::streamNewResidentFrom(is);
        d->next_id = qMax<int>(r->id(),  d->next_id);
        d->residents << r;
    }
    //We increment 'nextid' to actually contain the next id avaliable for use.
    d->next_id++;
    return true;

}

void Model::addResident(Resident *resident)
{
    beginInsertRows(QModelIndex(), d->residents.count()-1, d->residents.count());
    d->residents << resident;
    endInsertRows();
    qDebug() << "Has inserted row.";

}

void Model::removeResident(Resident *resident)
{

}

Resident *Model::getResidentByEmail(const QString &email) const
{
    foreach(Resident *r, d->residents)
    {
        if(r->email() == email)
        {
            return r;
        }
    }
    return 0;
}

bool Model::createNewPasswordFor(const QString &email)
{
    Resident *r = getResidentByEmail(email);
    if(r)
    {
        r->setPassword("SuperSecretRandomPassword");
        return true;
    }
    return false;
}

void Model::createNewGuard(const QString &email)
{
    Guard *guard = new Guard();
    guard->setEmail(email);
    guard->setPassword("ssrp");
    addResident(guard);
    this->saveToFile();
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
    if(d->number_of_dimensions == 1)
    {
        return 1;
    }

    return 6;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    Resident *r = d->residents[index.row()];

    //If I am a one-dimensional model for QML.
    if(d->number_of_dimensions == 1)
    {
        if (role == NameRole)
            return r->name();
        else if (role == TitleRole)
            return r->title();
        else if (role == SanityRole)
            return r->sanity();
        return QVariant();
    }

    //If I am a two-dimensional model for a grid.
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }
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

void Model::makeTableModel()
{
    d->number_of_dimensions = 2;
}

void Model::makeListModel()
{
    d->number_of_dimensions = 1;
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[TitleRole] = "title";
    roles[SanityRole] = "sanity";

    return roles;
}
