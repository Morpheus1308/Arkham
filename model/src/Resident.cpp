#include "Resident.h"
#include <QCryptographicHash>

class ResidentPrivate
{
    Resident *owner;

public:

    QString name;
    int sanity;
    QDate birthdate;
    QString title;
    int privileges;
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
          privileges(Resident::MayReadSelf),
          gender(Resident::NotSure),
          id(0),
          email(""),
          password("")
    {
    }

    void copyFrom(ResidentPrivate *other)
    {
        name = other->name;
        sanity = other->sanity;
        birthdate = other->birthdate;
        title = other->title;
        privileges = other->privileges;
        id = other->id;
        email = other->email;
        password = other->password;
    }

    QString hashPassword(const QString &password)
    {
        QCryptographicHash hash(QCryptographicHash::Sha512);
        hash.addData(password.toUtf8());
        return hash.result().toHex();
    }
};

Resident::Resident()
{
    d = new ResidentPrivate(this);
}

Resident::Resident(const Resident &other)
{
    d = new ResidentPrivate(this);
    if(this == &other) return;
    d->copyFrom(other.d);
}

Resident &Resident::operator=(Resident &rhs)
{
    if(this == &rhs) return *this;
    d->copyFrom(rhs.d);
    return *this;
}

Resident::~Resident()
{
    delete d;
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
}

QString Resident::title() const
{
    return d->title;
}

void Resident::setTitle(const QString &title)
{
    d->title = title;
}

int Resident::sanity() const
{
    return d->sanity;
}

void Resident::setSanity(int sanity)
{
    d->sanity = sanity;
}

QDate Resident::birthDate() const
{
    return d->birthdate;
}

void Resident::setBirthDate(const QDate &birthdate)
{
    d->birthdate = birthdate;
}

Resident::Gender Resident::gender() const
{
    return d->gender;
}

void Resident::setGender(Resident::Gender gender)
{
    d->gender = gender;
}

int Resident::privileges() const
{
    return d->privileges;
}

void Resident::setPrivileges(int privileges)
{
    d->privileges = privileges;
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
}

bool Resident::matchesPassword(const QString &password) const
{
    return d->hashPassword(password) == d->password;
}
