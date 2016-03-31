#ifndef PRIVILEGEFILTERPROXYMODEL_H
#define PRIVILEGEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class PrivilegeFilterProxyModel : public QSortFilterProxyModel
{

    Q_OBJECT

public:

    PrivilegeFilterProxyModel();
    ~PrivilegeFilterProxyModel();

    Q_INVOKABLE void setViewingResident(class Resident *r);

    void setSourceModel(class Model *model);
    Q_INVOKABLE class Model *model() const;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    Q_DISABLE_COPY(PrivilegeFilterProxyModel)
    friend class PrivilegeFilterProxyModelPrivate;
    class PrivilegeFilterProxyModelPrivate *d;
};

#endif // PRIVILEGEFILTERPROXYMODEL_H

