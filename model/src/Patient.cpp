#include "Patient.h"

Patient::Patient() :
    Resident()
{

}


Patient::~Patient()
{
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
