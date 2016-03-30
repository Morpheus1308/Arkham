#ifndef PRIVILEGEFILTERPROXYMODEL_H
#define PRIVILEGEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class PrivilegeFilterProxyModel : public QSortFilterProxyModel
{

public:

    PrivilegeFilterProxyModel();
    ~PrivilegeFilterProxyModel();

    void setViewingResident(class Resident *r);

    void setSourceModel(class Model *model);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    Q_DISABLE_COPY(PrivilegeFilterProxyModel)
    friend class PrivilegeFilterProxyModelPrivate;
    class PrivilegeFilterProxyModelPrivate *d;
};

#endif // PRIVILEGEFILTERPROXYMODEL_H

