#include "PrivilegeFilterProxyModel.h"
#include "Resident.h"
#include "Model.h"
#include <QDebug>

class PrivilegeFilterProxyModelPrivate
{
    PrivilegeFilterProxyModel *owner;

public:

    Model *model;
    Resident *viewing_resident = 0;

    PrivilegeFilterProxyModelPrivate(PrivilegeFilterProxyModel *o)
        : owner(o)
    {
    }

};

PrivilegeFilterProxyModel::PrivilegeFilterProxyModel()
{
    d = new PrivilegeFilterProxyModelPrivate(this);
}
PrivilegeFilterProxyModel::~PrivilegeFilterProxyModel()
{
    delete d;
}

void PrivilegeFilterProxyModel::setViewingResident(Resident *r)
{
    d->viewing_resident = r;
    invalidate();
}

void PrivilegeFilterProxyModel::setSourceModel(Model *model)
{
    QSortFilterProxyModel::setSourceModel(model);
    d->model = model;
}

Model *PrivilegeFilterProxyModel::model() const
{
    return d->model;
}

bool PrivilegeFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &) const
{
    if( ! d->viewing_resident ) return false;
    Resident *r = d->model->residents()[sourceRow];
    return r->mayBeReadBy(d->viewing_resident) || r->mayBeWrittenBy(d->viewing_resident);
}
