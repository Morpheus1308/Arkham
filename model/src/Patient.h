#ifndef PATIENT_H
#define PATIENT_H

#include "Resident.h"

class Patient : public Resident
{

public:

    Patient();
    Patient(const Patient &other);
    Patient& operator=(Patient &rhs);
    ~Patient();

    //Patients may only be viewed by privileged staff - Not even by them self.
    //"Aktindsigt" is a town in Denmark!
    bool mayBeReadBy(Resident const * const resident) const;
    bool mayBeWrittenBy(Resident const * const resident) const;
    QString className() const;

private:
    friend class PatientPrivate;
    class PatientPrivate *d;
};

#endif // PATIENT_H

