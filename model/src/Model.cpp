#include "Model.h"

#include "Resident.h"
#include <QDataStream>

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
};

Model::Model()
    : d(new ModelPrivate(this))
{

}


Model::~Model()
{
    delete d;
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
        d->nextid = r->id() > d->nextid ? r->id() : d->nextid;
        d->residents << r;
    }
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
