#ifndef ALCHEMIST_H
#define ALCHEMIST_H

#include "Resident.h"

class Alchemist : public Resident
{

    Q_OBJECT

public:

    Alchemist();
    ~Alchemist();

    bool mayBeReadBy(Resident const * const resident) const;
    bool mayBeWrittenBy(Resident const * const resident) const;
    int privileges() const;
    QString className() const;

};

#endif // ALCHEMIST_H

