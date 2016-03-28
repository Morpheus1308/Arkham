#include "Patient.h"

class PatientPrivate
{
    Patient *owner;

public:

    PatientPrivate(Patient *o)
        : owner(o)
    {
    }

    void copyFrom(PatientPrivate *other)
    {
    }
};

Patient::Patient()
{
    d = new PatientPrivate(this);
}


Patient::~Patient()
{
    delete d;
}

bool Patient::mayBeReadBy(const Resident * const resident) const
{
    return resident->privileges() && Resident::MayReadPatients;
}

bool Patient::mayBeWrittenBy(const Resident * const resident) const
{
    return resident->privileges() && Resident::MayWritePatients;
}

QString Patient::className() const
{
    return this->staticMetaObject.className();
}
