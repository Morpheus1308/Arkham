#include "Resident.h"
#include <QCryptographicHash>
#include "Patient.h"
#include <typeinfo>
#include <QString>
#include <QMap>
#include <assert.h>
#include <QDebug>

static QMap<QString, std::function<Resident*()> > factoryFunctions;

class ResidentPrivate
{
    Resident *owner;

public:

    QString name;
    int sanity;
    QDate birthdate;
    QString title;

    Resident::Gender gender;
    int id;
    QString email;
    QString password;

    ResidentPrivate(Resident *o)
        : owner(o),
          name(""),
          sanity(100),
          birthdate(QDate(1890, 8, 20)),
          title("Sir"),
          gender(Resident::NotSure),
          id(0),
          email(""),
          password("")
    {
    }

    void streamTo(QDataStream &out)
    {
        out << name << email  << birthdate << title << password;
        out << qint64(id);
        out << qint64(sanity);
        out << qint64(gender);


    }


    void streamFrom(QDataStream &in)
    {
        in >> name >> email  >> birthdate >> title >> password;
        qint64 in64;
        in >> in64;  id = in64;
        in >> in64;  sanity = in64;
        in >> in64;  gender = (Resident::Gender)in64;

    }

    QString hashPassword(const QString &password)
    {
        QCryptographicHash hash(QCryptographicHash::Sha512);
        hash.addData(password.toUtf8());
        return hash.result().toHex();
    }
};

Resident::Resident()
    : QObject()
{
    d = new ResidentPrivate(this);
}

Resident::~Resident()
{
    delete d;
}

bool Resident::operator==(const Resident &other) const
{
    return
            d->id == other.d->id &&
            d->name == other.d->name &&
            d->title == other.d->title &&
            d->sanity == other.d->sanity &&
            d->birthdate == other.d->birthdate &&
            d->gender == other.d->gender &&
            d->password == other.d->password &&
            d->email == other.d->email;
}

bool Resident::operator!=(const Resident &other) const
{
    return ! (*this == other);
}

Resident* Resident::streamNewResidentFrom(QDataStream &in)
{
    QString classname;
    in >> classname;
    if( ! factoryFunctions.contains(classname))
    {
        qDebug("There are no creator for %s", qPrintable(classname));
        assert(false);
    }
    Resident *r = factoryFunctions[classname]();
    r->d->streamFrom(in);
    return r;
}


void Resident::streamTo(QDataStream &out)
{
    out << this->className();
    d->streamTo(out);
}
int Resident::id() const
{
    return d->id;
}

QString Resident::name() const
{
    return d->name;
}

void Resident::setName(const QString &name)
{
    d->name = name;
    emit updated(this);
}

QString Resident::title() const
{
    return d->title;
}

void Resident::setTitle(const QString &title)
{
    d->title = title;
    emit updated(this);

}

int Resident::sanity() const
{
    return d->sanity;
}

void Resident::setSanity(int sanity)
{
    d->sanity = sanity;
    emit updated(this);
}


QDate Resident::birthDate() const
{
    return d->birthdate;
}

void Resident::setBirthDate(const QDate &birthdate)
{
    d->birthdate = birthdate;
    emit updated(this);
}

Resident::Gender Resident::gender() const
{
    return d->gender;
}

void Resident::setGender(Resident::Gender gender)
{
    d->gender = gender;
    emit updated(this);
}


void Resident::setPassword(const QString &password)
{
    d->password = d->hashPassword(password);
}

QString Resident::email() const
{
    return d->email;
}

void Resident::setEmail(const QString &email)
{
    d->email = email;
    emit updated(this);
}

bool Resident::matchesPassword(const QString &password) const
{
    return d->hashPassword(password) == d->password;
}

void Resident::registerResidentType(const QString &name, std::function<Resident*()> creator)
{
    factoryFunctions[name] = creator;
}

QMap<QString, std::function<Resident *()> > Resident::registeredCreators()
{
    return factoryFunctions;
}



// The methods below should, in an ideal world, be pure virtual, but since Qt will not register classes
// with pure virtual methods for QML usage, we have to do this nasty trick below.

int Resident::privileges() const
{
    qDebug() << "privileges() called on Resident";
    assert(false);
    return 1;
}

bool Resident::mayBeReadBy(const Resident * const resident) const
{
    qDebug() << "mayBeReadBy() called on Resident";
    assert(false);
    return true;
}

bool Resident::mayBeWrittenBy(const Resident * const resident) const
{
    qDebug() << "mayBeWrittenBy() called on Resident";
    assert(false);
    return true;
}

QString Resident::className() const
{
    qDebug() << "className() called on Resident";
    assert(false);
    return "";
}

