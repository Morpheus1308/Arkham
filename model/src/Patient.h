#ifndef PATIENT_H
#define PATIENT_H

#include "Resident.h"

class Patient : public Resident
{

    Q_OBJECT

public:

    Patient();
    ~Patient();

    bool mayBeWrittenBy(Resident const * const resident) const;
    bool mayBeReadBy(Resident const * const resident) const;

    //Patients may only be viewed by privileged staff - Not even by them self.
    //"Aktindsigt" is a town in Denmark!
    int privileges() const;

    QString className() const;
};

#endif // PATIENT_H

