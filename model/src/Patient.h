#ifndef PATIENT_H
#define PATIENT_H

#include "Resident.h"

class Patient : public Resident
{

    Q_OBJECT

public:

    Patient();
    ~Patient();

    //Patients may only be viewed by privileged staff - Not even by them self.
    //"Aktindsigt" is a town in Denmark!
    bool mayBeReadBy(Resident const * const resident) const;
    bool mayBeWrittenBy(Resident const * const resident) const;
    QString className() const;
};

#endif // PATIENT_H

