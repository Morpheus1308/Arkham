#ifndef MEDICAL_STAFF_H
#define MEDICAL_STAFF_H

#include "Resident.h"

class MedicalStaff : public Resident
{

    Q_OBJECT

public:

    MedicalStaff();
    ~MedicalStaff();

    bool mayBeReadBy(Resident const * const resident) const;
    bool mayBeWrittenBy(Resident const * const resident) const;
    int privileges() const;
    QString className() const;

};

#endif // MEDICAL_STAFF_H

