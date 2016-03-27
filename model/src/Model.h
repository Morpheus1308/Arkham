#ifndef MODEL_H
#define MODEL_H

#include <QIODevice>
#include <QAbstractItemModel>

class Resident;


class Model /*: public QAbstractItemModel*/
{

public:
	Model();
	~Model();

    bool save(QIODevice *out) const;
    bool load(QIODevice *in);

    void addResident(Resident *resident);
    void removeResident(Resident *resident);

    QList<Resident*> residents() const;
private:
    Model(const Model &other);
    Model &operator=(const Model &rhs);
    class ModelPrivate *d;
};

#endif /* MODEL_H */
