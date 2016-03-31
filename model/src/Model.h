#ifndef MODEL_H
#define MODEL_H

#include <QIODevice>
#include <QAbstractItemModel>
#include <functional>

class Resident;


class Model : public QAbstractItemModel
{

    Q_OBJECT

public:
	Model();
	~Model();

    void setFileName( const QString &filename);
    void loadFromFileOrCreate();
    void saveToFile();

    bool save(QIODevice *out) const;
    bool load(QIODevice *in);

    bool addResident(Resident *resident);
    void removeResident(Resident *resident);
    Q_INVOKABLE Resident *getResidentByEmail(const QString &email) const;
    bool createNewPasswordFor(const QString &email);
    void createNewGuard(const QString &email);

    QList<Resident*> residents() const;

    //Methods from QAbstractItemModel
    QModelIndex index(int row, int column, const QModelIndex&parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount( const QModelIndex &index = QModelIndex()) const;
    int columnCount( const QModelIndex &index = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;


    void makeTableModel();
    void makeListModel();

    //Code for exposing model to QML land.
    enum ResidentRoles {
        NameRole = Qt::UserRole + 1,
        TitleRole,
        SanityRole
    };

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    Model(const Model &other);
    Model &operator=(const Model &rhs);
    class ModelPrivate *d;
};

#endif /* MODEL_H */
